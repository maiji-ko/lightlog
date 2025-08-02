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
pushd build >> /dev/null
cmake .. &&
make -j$(nproc)
popd >> /dev/null

echo -e "\033[32mBuild completed successfully\033[0m"

echo "Running example..."
./bin/loglight_example
