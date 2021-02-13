//
// Created by andyroiiid on 2/1/2021.
//

#include "ResourceManager.h"

#include <algorithm>

void ResourceManager::add(const std::string &name, const std::string &dependency) {
    bool cyclicDependency = anyOfDependencies(dependency, [&](const std::string &dep) {
        return name == dep;
    });

    if (cyclicDependency) {
        fprintf(stderr, "ignore cyclic dependency %s -> %s\n", name.c_str(), dependency.c_str());
        return;
    }

    resources[dependency];

    auto &dependencies = resources[name].dependencies;
    if (std::find(dependencies.begin(), dependencies.end(), dependency) != dependencies.end()) {
        fprintf(stderr, "ignore duplicate dependency %s -> %s\n", name.c_str(), dependency.c_str());
        return;
    }
    dependencies.push_back(dependency);
}

void ResourceManager::remove(const std::string &name) {
    if (resources.find(name) == resources.end())
        return;

    resources.at(name).isDeleted = true;
}

bool ResourceManager::isUsable(const std::string &name) const {
    if (resources.find(name) == resources.end())
        return false;

    return !anyOfDependencies(name, [&](const std::string &dep) {
        return resources.at(dep).isDeleted;
    });
}

void ResourceManager::print() const {
    for (const auto &[name, resource] : resources) {
        if (resource.isDeleted)
            continue;

        printf("%s, usable: %d, depends on:", name.c_str(), isUsable(name));
        for (const auto &dependency : resource.dependencies) {
            printf(" %s", dependency.c_str());
        }
        putchar('\n');
    }
}

bool ResourceManager::anyOfDependencies(const std::string &name,
                                        const std::function<bool(const std::string &)> &predicate) const {
    if (resources.find(name) == resources.end())
        return false;

    const auto &dependencies = resources.at(name).dependencies;
    return std::any_of(dependencies.begin(), dependencies.end(), [&](const std::string &dependency) {
        return predicate(dependency) || anyOfDependencies(dependency, predicate);
    });
}
