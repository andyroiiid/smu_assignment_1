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
    void addDependency(const std::string &name, const std::string &dependency);

    void remove(const std::string &name);

    bool isUsable(const std::string &name);

    void print();

private:
    void setDeleted(const std::string &name, bool deleted);

    void walkDependencies(const std::string &name, const std::function<void(const std::string &)> &handler);

    std::unordered_map<std::string, Resource> resources;

    // TODO: cache isUSable status, dirty flag
};

#endif //SMU_ASSIGNMENT_1_RESOURCEMANAGER_H
