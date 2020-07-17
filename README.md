# conan integration with cmake

## preffered configuration

* generator: cmake
* CMakeLists: inject
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS) # 
* DRY, add only link dependencies like: 
    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) or 
    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
Include direcories wil be adjusted accordingly!
* plain Boost
    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost )
does not work,
    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )   
must be used


## debugging
{main dir with CMakeLists.txt}$ cmake --check-system-vars --build build
