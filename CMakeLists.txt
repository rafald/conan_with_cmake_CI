cmake_minimum_required(VERSION 3.0.0)
project(algos VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS) # 

set(CMAKE_VERBOSE_MAKEFILE ON)
#or while calling cmake:  export VERBOSE=1 cmake ...

#SET (Boost_ADDITIONAL_VERSIONS "1.67" "1.67.0" "1.71") 
#set(Boost_DEBUG 1)
find_package(Boost 1.72 COMPONENTS unit_test_framework system REQUIRED) # CONFIG  mode does not work 

include_directories(.)

FILE ( GLOB SOURCES  "${PROJECT_SOURCE_DIR}/src/*.cpp" )
 
#ADD_LIBRARY( algos_lib STATIC "${SOURCES}" )
add_executable(${PROJECT_NAME} "${SOURCES}")
#TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} PRIVATE Boost )
TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} Boost::system ) # Not CONAN_PKG::boost <- all boost libs

### ### ### ### ### ### ### TESTS
include(CTest)
enable_testing()

find_package(GTest REQUIRED) # COMPONENTS gtest gtest_main 
add_executable(lower_bound_test test/lower_bound_test.cpp)
target_link_libraries(lower_bound_test PRIVATE CONAN_PKG::gtest) #${GTEST_LIBRARIES} ${CONAN_LIBS_GTEST} $GTEST_MAIN_LIBRARIES gtest gtest_main pthread
#target_link_libraries(lower_bound_test PRIVATE CONAN_LIB::gtest_gmock)
add_test(lower_bound lower_bound_test WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(topo_sort_test test/topo_sort_test.cpp)
target_link_libraries(topo_sort_test PRIVATE Boost::unit_test_framework ) 
add_test(topo_sort topo_sort_test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
