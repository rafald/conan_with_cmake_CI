# conan integration with cmake

## preffered configuration

1. generator to select: **cmake**
1. code to inject at the beginning of CMakeLists.txt: 

      include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
      conan_basic_setup(TARGETS)
1. DRY - in CMakeLists add only link dependencies like: 

      TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) or 
      TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
   Include direcories wil be adjusted accordingly!
1. do not try to use a plain _Boost_ in 

      TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost )
   it does not work, the following code

     TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} CONAN_PKG::boost )
must be used in case of linking with all boost libraries
1. at the begining of CMakeLists.txt do:

       INCLUDE InvokeConan.txt
   it will invoke `conan install .` automatically

## debugging
*main dir with CMakeLists.txt*$ cmake --check-system-vars --build build
