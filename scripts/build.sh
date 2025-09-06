#!/bin/bash
PROJECT=$1
BUILD=$2
cmake -S . -B build/${PROJECT} -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=scripts/cmake-toolchain-mingw64-x86_64.cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_BUILD_TYPE=$BUILD \
    -DEXAMPLE_DIR=$PROJECT \

cmake --build build/${PROJECT} --parallel

chmod 777 build/${PROJECT}/bin/*