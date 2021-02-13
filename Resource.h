//
// Created by andyroiiid on 2/1/2021.
//

#ifndef SMU_ASSIGNMENT_1_RESOURCE_H
#define SMU_ASSIGNMENT_1_RESOURCE_H

#include <list>
#include <string>

/*
 * the struct for a resource node
 */
struct Resource {
    /*
     * flag for deletion
     */
    bool isDeleted = false;

    /*
     * container for all dependencies
     */
    std::list<std::string> dependencies;
};

#endif //SMU_ASSIGNMENT_1_RESOURCE_H
