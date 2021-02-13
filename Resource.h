//
// Created by andyroiiid on 2/1/2021.
//

#ifndef SMU_ASSIGNMENT_1_RESOURCE_H
#define SMU_ASSIGNMENT_1_RESOURCE_H

#include <list>
#include <string>

struct Resource {
    bool isDeleted = false;
    std::list<std::string> dependencies; // TODO: use pointers
};

#endif //SMU_ASSIGNMENT_1_RESOURCE_H
