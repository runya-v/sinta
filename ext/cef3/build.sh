#!/bin/bash
# $1 - build type

if [[ $# != 1 ]]; then
	echo "Need build type set."
	exit 1
fi

if [[ ! -f "cef_binary_3.1750.1738_linux64.7z" ]]; then
	echo "Archive for CEF3 is not find. Take library source from: \"http://www.magpcss.net/cef_downloads/index.php?file=cef_binary_3.1750.1738_linux64.7z\""
	exit 1
fi

SRC_NAME=cef_binary_3.1750.1738_linux64

if [[ ! -d $SRC_NAME ]]; then
	echo "Unzip $SRC_NAME.7z."
	7z x $SRC_NAME.7z
fi

pushd $SRC_NAME
echo "build $1 for $SRC_NAME."

if [[ ! -d "bld" ]]; then
	mkdir bld
fi
pushd bld
cmake -DCMAKE_BUILD_TYPE=$1 ..
make -j$(($(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)+1))
popd
popd

exit 0
