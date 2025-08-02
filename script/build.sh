#!/bin/bash

set -e

echo "Script executed at: $(date)" 

need_clear="$1"
if [ "$need_clear" = "clear" ]; then
    echo "Clearing build directory..."
    rm -rf build
fi

if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

echo "Compiling project..."
pushd build
if ! cmake ..; then
    echo "CMake configuration failed"
    exit 1
fi

if ! make -j$(nproc); then
    echo "Make compilation failed"
    exit 1
fi
popd

echo "Build completed successfully"

echo "Running example..."
./bin/loglight_example