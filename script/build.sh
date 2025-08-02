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
# 使用 cd 替代 pushd/popd
cd build
cmake .. &&
make -j$(nproc)
cd ..

echo "Build completed successfully"

echo "Running example..."
./bin/loglight_example