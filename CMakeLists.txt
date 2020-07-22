cmake_minimum_required(VERSION 3.0.0)
project(algos VERSION 0.1.0)

INCLUDE(invoke_conan.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS) # 

set(CMAKE_VERBOSE_MAKEFILE ON) #from command line $> export VERBOSE=1 cmake ...

#SET (Boost_ADDITIONAL_VERSIONS "1.67" "1.67.0" "1.71") 
#set(Boost_DEBUG 1)
find_package(Boost 1.73.0 COMPONENTS unit_test_framework system REQUIRED) # CONFIG  mode does not work 

include_directories(.)

FILE ( GLOB SOURCES  "${PROJECT_SOURCE_DIR}/src/*.cpp" )
 
#ADD_LIBRARY( algos_lib STATIC "${SOURCES}" )
add_executable(${PROJECT_NAME} "${SOURCES}")
#TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} PRIVATE Boost )
TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) # Not CONAN_PKG::boost <- all boost libs

### ### ### ### ### ### ### TESTS
#include(CTest)
enable_testing()
# ADD_SUBDIRECTORY( test ) # test would have to have own CMakeFiles.txt

#find_package(GTest REQUIRED) # COMPONENTS gtest gtest_main #Could NOT find GTest (missing: GTEST_LIBRARY GTEST_MAIN_LIBRARY)
add_executable(lower_bound_test test/lower_bound_test.cpp)
target_link_libraries(lower_bound_test PRIVATE CONAN_PKG::gtest) 
add_test(lower_bound_test bin/lower_bound_test)


add_executable(topo_sort_test test/topo_sort_test.cpp)
target_link_libraries(topo_sort_test PRIVATE Boost::unit_test_framework ) 
add_test(topo_sort bin/topo_sort_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
