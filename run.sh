#!/bin/bash

BUILD_PATH="$PWD/bld"
BUILD_JOBS=$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)

if [[ ! -d $BUILD_PATH ]]; then
    echo "Create build path"
    mkdir bld
fi

echo "Configure build configuration"
pushd "$BUILD_PATH"
rm -rf *
cmake -DENABLE_TESTS=ON ..
make -j$BUILD_JOBS
popd

if [[ -f "$BUILD_PATH/Debug/bin/http-server" ]]; then
    echo "Run http server. Please open \"localhost:8888\" web page..."
    $BUILD_PATH/Debug/bin/http-server 0.0.0.0 8888 1 ./data
else
    echo "Can\`t run server, please check dependencies by configure build or connect to author."
fi
