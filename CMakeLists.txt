cmake_minimum_required(VERSION 3.17)
project(smu_assignment_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(smu_assignment_1
        main.cpp
        ResourceManager.cpp ResourceManager.h
        Resource.h)