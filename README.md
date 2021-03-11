# modern_cpp_training
My Personal Modern C++ Hands-On Training

This repo is my personal hands-on training around Scott Meyers' "Effective Modern C++".
Each project covers a topic that I found significant and I wanted to give it a try.
Most of the code is original, however, there are some copy-paste from other site examples, like cppreference.com

In each subfolder there is a separate CMake project.
To create new project in top of the existing ones, use:

    ./make_new_project <project_name>
           
To compile all projects in one shot, use the root CMakeFiles.txt or compile one by one by diving in each project's subdir.

## SubProjects:

### move-semantics

Demonstrates move-constructor performance call on a class, by printing all construction, destructor, copy and movement of an object
across different types of assignment.

Note: for catching value copy when returning by value, the compiler optimization is removed.

See CMakeLists.txt

    target_compile_options(move-statements PRIVATE -fno-elide-constructors)

Compile with and without it, also with and without C++11

    #set (CMAKE_CXX_STANDARD 98) 

#### Output:

C++ 98 with "-fno-elide-constructors" - makes extra copy on function return values, usually optimized out by modern compilers

    default constructor
    copy constructor
    default destructor
    copy constructor
    default destructor
    default destructor
    
C++ 11  with "-fno-elide-constructors":

    default constructor
    move constructor
    default destructor
    move constructor
    default destructor
    default destructor

C98 default:

    default constructor
    default destructor

C++ 11 default:

    default constructor
    default destructor


