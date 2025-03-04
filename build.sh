#!/bin/bash

BUILD_DIR="build"

if [[ "$1" == "-c" ]]; then
    echo "build.sh: cleaning build directory"
    rm -rf $BUILD_DIR
fi

if [[ ! -d "$BUILD_DIR" ]]; then
    mkdir "$BUILD_DIR"
    cd "$BUILD_DIR" || exit 1
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .. || exit 1
    cd ..
fi

cmake --build "$BUILD_DIR" || echo "build.sh: build failed"; exit 1

