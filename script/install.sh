#!/bin/bash

echo "Loglight Installation Script"
echo "============================"

if [ ! -d "build" ]; then
    echo "Error: Build directory not found. Please run build.sh first."
    exit 1
fi

cd build

if [ "$1" = "--user" ]; then
    echo "Installing to user directory: $HOME/.local"
    cmake -DCMAKE_INSTALL_PREFIX="$HOME/.local" ..
    cmake --install .
    echo ""
    echo "NOTE: Add the following to your ~/.bashrc or ~/.zshrc:"
    echo "export LD_LIBRARY_PATH=\$HOME/.local/lib:\$LD_LIBRARY_PATH"
    echo "export PKG_CONFIG_PATH=\$HOME/.local/lib/pkgconfig:\$PKG_CONFIG_PATH"
elif [ "$1" = "--system" ]; then
    echo "Installing to system directories (requires sudo)"
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
    sudo cmake --install .
else
    echo "Usage:"
    echo "  ./install.sh --user    Install to $HOME/.local (no sudo required)"
    echo "  ./install.sh --system  Install to /usr/local (requires sudo)"
fi