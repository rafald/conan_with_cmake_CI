![C/C++ CI](https://github.com/rafald/conan_with_cmake_CI/workflows/C/C++%20CI/badge.svg)

![C/C++ CI v2](https://github.com/rafald/conan_with_cmake_CI/workflows/C/C++%20CI%20v2/badge.svg)

# Github continuous integration (via github actions) of tiny C++ project using conan package manager with cmake builder

Prerequisites are installed CMake builder (conan package manager is installed by cmake configuration step).

Github action does install conan in one of the cmake's configuration steps

## How to convert your cmake project to use conan package manager

1. generator to select in conanfile.txt/conanfile.py : **cmake**
1. at the begining of CMakeLists.txt do:

       INCLUDE(invoke_conan.cmake)
   it will invoke `conan install .` automatically
1. right after previous include call inject: 

       include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
       conan_basic_setup(TARGETS)
1. in CMakeLists.txt add the only dependency: 

       TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) 
   or 
   
       TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
   for all boost libraries. Include directories will be adjusted accordingly!
1. do not try to use a plain _Boost_ in 

       TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost )
   it does not work, the following code is correct

       TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
 
