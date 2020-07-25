# conan integration with cmake plus github actions to perform C/C++ CI

Prerequisites are installed CMake builder and conan package manager

Regarding github action, it does install conan in one of the cmake's configuration steps

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
   it does not work, the following code

       TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
 
