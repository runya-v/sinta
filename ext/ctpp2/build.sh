#!/bin/bash

SRC_NAME="ctpp2-2.8.3"

if [[ ! -d $SRC_NAME ]]; then
    echo "Extract `$SRC_NAME.tar.gz.`"
    tar xzvf $SRC_NAME.tar.gz
else
    if [[ ! -f "$SRC_NAME/bld/libctpp2.so" ]]; then
        echo "Set patch `CTPP2FileSourceLoader.cpp.diff`"
        patch -p0 $SRC_NAME/src/CTPP2FileSourceLoader.cpp -i CTPP2FileSourceLoader.cpp.diff

        echo "Build CTPP2"
        pushd $SRC_NAME
        mkdir bld
        pushd bld
        cmake ..
        make -j$(($(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)+1))
        popd
        popd
    fi
fi

