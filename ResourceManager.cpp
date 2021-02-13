//
// Created by andyroiiid on 2/1/2021.
//

#include "ResourceManager.h"

#include <algorithm>

void ResourceManager::add(const std::string &name, const std::string &dependency) {
    // avoid cyclic dependency
    bool cyclicDependency = anyOfDependencies(dependency, [&](const std::string &dep) {
        return name == dep;
    });
    if (cyclicDependency) {
        fprintf(stderr, "ignore cyclic dependency %s -> %s\n", name.c_str(), dependency.c_str());
        return;
    }

    // ensure the dependency node exists
    resources[dependency];

    // check for duplicate dependency
    auto &dependencies = resources[name].dependencies; // this line also implicitly creates the <name> node
    if (std::find(dependencies.begin(), dependencies.end(), dependency) != dependencies.end()) {
        fprintf(stderr, "ignore duplicate dependency %s -> %s\n", name.c_str(), dependency.c_str());
        return;
    }

    // add dependency for <name> node
    dependencies.push_back(dependency);
}

void ResourceManager::remove(const std::string &name) {
    // ignore non-existent nodes
    if (resources.find(name) == resources.end())
        return;

    // mark node as deleted
    resources.at(name).isDeleted = true;
}

bool ResourceManager::isUsable(const std::string &name) const {
    // ignore non-existent nodes
    if (resources.find(name) == resources.end())
        return false;

    // check if any dependency is not usable
    return !anyOfDependencies(name, [&](const std::string &dep) {
        return resources.at(dep).isDeleted;
    });
}

void ResourceManager::print() const {
    for (const auto &[name, resource] : resources) {
        // skip deleted nodes
        if (resource.isDeleted)
            continue;

        // print the node
        printf("%s, usable: %s, depends on:", name.c_str(), isUsable(name) ? "true" : "false");

        // print all dependencies
        for (const auto &dependency : resource.dependencies) {
            printf(" %s", dependency.c_str());
        }

        putchar('\n');
    }
}

bool ResourceManager::anyOfDependencies(const std::string &name,
                                        const std::function<bool(const std::string &)> &predicate) const {
    // ignore non-existent nodes
    if (resources.find(name) == resources.end())
        return false;

    // recursive check the <name> node and all its dependencies
    const auto &dependencies = resources.at(name).dependencies;
    return std::any_of(dependencies.begin(), dependencies.end(), [&](const std::string &dependency) {
        return predicate(dependency) || anyOfDependencies(dependency, predicate);
    });
}
