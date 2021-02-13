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
    /*
     * add a link between two nodes (and implicitly create them)
     */
    void add(const std::string &name, const std::string &dependency);

    /*
     * make a node unusable
     *
     * nodes might be resurrected, and they will need the previous dependency information
     * so this function only mark nodes as deleted, not actually deleting them
     */
    void remove(const std::string &name);

    /*
     * query if a node is usable, calling this will recursively check every dependencies
     *
     * the results can be cached if this function is performance critical
     * there isn't any performance constraint in the assignment, so I decide to keep it simple here
     */
    [[nodiscard]] bool isUsable(const std::string &name) const;

    /*
     * print all nodes
     */
    void print() const;

private:
    /*
     * helper function for checking every dependencies with a predicate
     */
    bool anyOfDependencies(const std::string &name, const std::function<bool(const std::string &)> &predicate) const;

    /*
     * container for all nodes
     */
    std::unordered_map<std::string, Resource> resources;
};

#endif //SMU_ASSIGNMENT_1_RESOURCEMANAGER_H
