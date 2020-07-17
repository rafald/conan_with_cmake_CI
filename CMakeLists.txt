cmake_minimum_required(VERSION 3.0.0)
project(algos VERSION 0.1.0)

#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR} FORCE)

#set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
#message(${CMAKE_MODULE_PATH})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS) # 

#export VERBOSE=1
set(CMAKE_VERBOSE_MAKEFILE ON)

#SET (Boost_ADDITIONAL_VERSIONS "1.67" "1.67.0" "1.71") 
#set(Boost_DEBUG 1)
find_package(Boost 1.72 COMPONENTS unit_test_framework system REQUIRED) # CONFIG  mode does not work | unit_test_framework
#!!! not required include_directories(${BOOST_INCLUDE_DIRS})
MESSAGE( "CONAN_LIBS=> ${CONAN_LIBS}" )
#MESSAGE( "CONAN_PKG::boost=> ${CONAN_PKG::boost}" )

include_directories(.)

FILE ( GLOB SOURCES  "${PROJECT_SOURCE_DIR}/src/*.cpp" )
 
#ADD_LIBRARY( algos_lib STATIC "${SOURCES}" )
add_executable(${PROJECT_NAME} "${SOURCES}")
#TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} PRIVATE Boost )
TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) # Not CONAN_PKG::boost <- all boost libs
MESSAGE("Boost_LIBRARIES=> ${Boost_LIBRARIES}")
MESSAGE("PROJECT_BINARY_DIR=> ${PROJECT_BINARY_DIR}")

### ### ### ### ### ### ### TESTS
include(CTest)
enable_testing()
MESSAGE("CMAKE_RUNTIME_OUTPUT_DIRECTORY=> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

find_package(GTest COMPONENTS REQUIRED) # gtest gtest_main 
#include_directories(${GTEST_INCLUDE_DIRS}) # GTEST uppercase !

MESSAGE("GTest_LIBRARIES=> ${GTest_LIBRARIES}")
MESSAGE("CONAN_LIBS_GTEST=> ${CONAN_LIBS_GTEST}")
add_executable(lower_bound_test test/lower_bound_test.cpp)
target_link_libraries(lower_bound_test PRIVATE CONAN_PKG::gtest) #${GTEST_LIBRARIES} ${CONAN_LIBS_GTEST} $GTEST_MAIN_LIBRARIES gtest gtest_main pthread
#target_link_libraries(lower_bound_test PRIVATE CONAN_LIB::gtest_gmock)
target_include_directories(lower_bound_test PRIVATE ${CONAN_INCLUDE_DIRS_GTEST_GMOCK})
add_test(lower_bound lower_bound_test WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(topo_sort_test test/topo_sort_test.cpp)
target_link_libraries(topo_sort_test PRIVATE Boost::unit_test_framework ) # CONAN_PKG::boost <- all boost libs, but also headers | ${Boost_LIBRARIES} <- only requested components
add_test(topo_sort topo_sort_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
