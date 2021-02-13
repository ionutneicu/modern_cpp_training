# modern_cpp_training
My Personal Modern C++ Hands-On Training

In each subfolder there is a separate CMake project.
To create new project, use:

    ./make_new_project <project_name>
           

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

C++ 98 with "-fno-elide-constructors":

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


