# invoke conan from cmake
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.0/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=65fc3508c91bf201f5472d28b21259e02b6f975a2917be457412ab7a87906c1e
                TLS_VERIFY ON)
                 
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check(VERSION 1.0.0 REQUIRED)
conan_cmake_run(CONANFILE conanfile.txt #REQUIRES boost/1.73.0 gtest/1.10.0
                BASIC_SETUP #CMAKE_TARGETS
                BUILD missing
                SETTINGS compiler.cppstd=17
                ENV env_var=value
                ENV Pkg:env_var2=value2
                OPTIONS Pkg:shared=True
                        OtherPkg:option=value) 
