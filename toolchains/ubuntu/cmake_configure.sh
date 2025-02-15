#!/bin/sh
TOOLCHAIN_FILE="./toolchains/ubuntu/linux-gnu-toolchain.cmake"
BUILD_DIR="build-ubuntu"
BUILD_TYPE=Release

cmake\
 -B $BUILD_DIR\
 -G Ninja\
 -DCMAKE_BUILD_TYPE=$BUILD_TYPE\
 -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE\
 -DCMAKE_TOOLCHAIN_FILE:STIRNG=$TOOLCHAIN_FILE
