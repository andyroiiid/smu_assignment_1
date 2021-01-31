//
// Created by andyroiiid on 2/1/2021.
//

#include "ResourceManager.h"

#include <algorithm>

void ResourceManager::addDependency(const std::string &name, const std::string &dependency) {
    bool cyclicDependency = false;
    walkDependencies(dependency, [&](const std::string &dep) {
        if (name == dep)
            cyclicDependency = true;
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
    setDeleted(name, true);
}

bool ResourceManager::isUsable(const std::string &name) {
    if (resources.find(name) == resources.end())
        return false;

    bool usable = true;
    walkDependencies(name, [&](const std::string &dep) {
        if (resources.at(dep).isDeleted)
            usable = false;
    });
    return usable;
}

void ResourceManager::print() {
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

void ResourceManager::setDeleted(const std::string &name, bool deleted) {
    if (resources.find(name) == resources.end())
        return;

    resources.at(name).isDeleted = deleted;
}

// TODO: early abort
void ResourceManager::walkDependencies(
        const std::string &name,
        const std::function<void(const std::string &)> &handler
) {
    if (resources.find(name) == resources.end())
        return;

    const auto &dependencies = resources.at(name).dependencies;
    for (const auto &dependency: dependencies) {
        handler(dependency);
        walkDependencies(dependency, handler);
    }
}
