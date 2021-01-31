#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#include "ResourceManager.h"

void readTuplesFromFile(const std::string &filename,
                        const std::function<void(const std::string &, const std::string &)> &func) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
#define LOG_PARSE_ERROR(message) fprintf(stderr, "error when parsing line (" message "): %s\n", line.c_str())
        if (line.empty()) {
            LOG_PARSE_ERROR("empty line");
            continue;
        }
        size_t spacePos = line.find_first_of(' ');
        if (spacePos == std::string::npos) {
            LOG_PARSE_ERROR("no space found");
            continue;
        }
        std::string first = line.substr(0, spacePos);
        if (first.empty()) {
            LOG_PARSE_ERROR("empty first");
            continue;
        }
        std::string second = line.substr(spacePos + 1, std::string::npos);
        if (second.empty()) {
            LOG_PARSE_ERROR("empty second");
            continue;
        }
#undef LOG_PARSE_ERROR
        func(first, second);
    }
}

int main() {
    ResourceManager resourceManager;

    readTuplesFromFile("resource.txt", [&](const std::string &name, const std::string &dependency) {
        resourceManager.addDependency(name, dependency);
    });

    resourceManager.print();

    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "q")
            break;

        resourceManager.remove(command);

        resourceManager.print();
    }

    return 0;
}
