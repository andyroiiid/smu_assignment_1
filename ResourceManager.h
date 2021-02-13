//
// Created by andyroiiid on 2/1/2021.
//

#ifndef SMU_ASSIGNMENT_1_RESOURCEMANAGER_H
#define SMU_ASSIGNMENT_1_RESOURCEMANAGER_H

#include <string>
#include <functional>
#include <unordered_map>

#include "Resource.h"

class ResourceManager {
public:
    void add(const std::string &name, const std::string &dependency);

    void remove(const std::string &name);

    [[nodiscard]] bool isUsable(const std::string &name) const;

    void print() const;

private:
    bool anyOfDependencies(const std::string &name, const std::function<bool(const std::string &)> &predicate) const;

    std::unordered_map<std::string, Resource> resources;

    // TODO: cache isUsable status, dirty flag
};

#endif //SMU_ASSIGNMENT_1_RESOURCEMANAGER_H
