# conan integration with cmake

## preffered configuration

* generator to select: **cmake**

* code to inject into CMakeLists: 

     include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
     conan_basic_setup(TARGETS)
* DRY - in CMakeLists add only link dependencies like: 

    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) or 
    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
Include direcories wil be adjusted accordingly!

* do not try to use a plain _Boost_ in 

    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost )
does not work,

    TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )   
must be used in case of linking with all boost libraries


## debugging
*main dir with CMakeLists.txt*$ cmake --check-system-vars --build build
