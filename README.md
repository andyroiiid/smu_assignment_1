# SMU Programming Assignment 1

Solution to [SMU Programming Assignment 1](https://www.smu.edu/Guildhall/Admissions/Portfolio-Requirements/Programming)

# My Name

An Huang

# Directory structure

```
.gitignore          git ignore file
CMakeLists.txt      CMake build system file
main.cpp            file reading & the main function
Resource.h          declaration for a resource node
resource.txt        my test input file
ResourceManager.cpp implementation for the resource manager class
ResourceManager.h   declaration for the resource manager class
```

# Some explanation

I know that this implementation is not very optimized, but this assignment is only a abstraction of a real world game
program.

For example, I will recursively query every dependency when checking if a resource is usable. This might be slow, but
removing a node is fast in this program, and it's easy to add a cache to make the query O(1) (trading memory for speed).
I usually go with the most straight forward implementation, and only make optimizations when they are actually needed.

There are no performance constraints for the assignment, so I decide to write simpler code.
