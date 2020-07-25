#!/usr/bin/env sh
set -ex

THIS_DIR=$(realpath $(dirname $0))
BUILD_DIR=$THIS_DIR/build

export VERBOSE=1


rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR
cd $BUILD_DIR

#NOW INVOKED FROM CMAKE $> conan install ..

#cmake --no-warn-unused-cli -DCMAKE_PROJECT_INCLUDE_BEFORE:STRING=$THIS_DIR/SetupConan.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++ -DCMAKE_TOOLCHAIN_FILE=$BUILD_DIR/conan_paths.cmake -H$THIS_DIR -B$BUILD_DIR -G Ninja
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++ -H$THIS_DIR -B$BUILD_DIR -G Ninja # -DCMAKE_PROJECT_INCLUDE_BEFORE:STRING=$THIS_DIR/InvokeConan.cmake

cmake --build $BUILD_DIR --config Debug --target all -- -j 10

# the following option does not work with target test:  --build $THIS_DIR/build
#TODO binaried are in bin/ but cmtest expects in ./
pwd
ctest --build $BUILD_DIR/bin --config Debug --target test --output-on-failure -- -j 10
cd ..
