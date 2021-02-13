#include <iostream>
#include <fstream>

#include "ResourceManager.h"

/*
 * read line of string tuples from file and process them with func()
 */
void readTuplesFromFile(const std::string &filename,
                        const std::function<void(const std::string &, const std::string &)> &func) {
    // open file
    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line)) {
#define LOG_PARSE_ERROR(message) fprintf(stderr, "error when parsing line (" message "): %s\n", line.c_str())
        if (line.empty()) {
            LOG_PARSE_ERROR("empty line");
            continue;
        }

        // split the string
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

        // successfully parsed a line into two strings
#undef LOG_PARSE_ERROR
        func(first, second);
    }
}

int main() {
    ResourceManager resourceManager;

    // read tuples from file and add links
    readTuplesFromFile("resource.txt", [&](const std::string &name, const std::string &dependency) {
        resourceManager.add(name, dependency);
    });

    // print all nodes
    resourceManager.print();

    std::string input;
    while (std::getline(std::cin, input)) {
        // input should be "q" for quit
        if (input == "q")
            break;

        // or the name of a node to delete it
        resourceManager.remove(input);

        // print all nodes
        resourceManager.print();
    }

    // this program doesn't use any explicit dynamic memory allocation
    // so there won't be any memory leak unless the stl implementation is broken

    return 0;
}
