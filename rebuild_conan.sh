#!/usr/bin/env sh

THIS_DIR=$(realpath $(dirname $0))
BUILD_DIR=build

export VERBOSE=1

rm -rf $THIS_DIR/$BUILD_DIR
mkdir -p $THIS_DIR/$BUILD_DIR
cd $THIS_DIR/$BUILD_DIR

conan install ..

#/usr/bin/cmake --no-warn-unused-cli -DCMAKE_PROJECT_INCLUDE_BEFORE:STRING=$THIS_DIR/SetupConan.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++ -DCMAKE_TOOLCHAIN_FILE=$THIS_DIR/$BUILD_DIR/conan_paths.cmake -H$THIS_DIR -B$THIS_DIR/$BUILD_DIR -G Ninja
/usr/bin/cmake --no-warn-unused-cli -DCMAKE_PROJECT_INCLUDE_BEFORE:STRING=$THIS_DIR/SetupConan.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/bin/g++ -H$THIS_DIR -B$THIS_DIR/$BUILD_DIR -G Ninja

/usr/bin/cmake --build $THIS_DIR/$BUILD_DIR --config Debug --target all -- -j 10

# the following option does not work with target test:  --build $THIS_DIR/build
#TODO binaried are in bin/ but cmtest expects in ./
echo /usr/bin/ctest --build $THIS_DIR/$BUILD_DIR/bin --config Debug --target test --output-on-failure -- -j 10
cd ..
