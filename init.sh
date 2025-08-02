#!/bin/bash

set -e

# 检查是否已安装fmt库
check_fmt_installed() {
    # 检查是否已安装libfmt-dev包
    if dpkg -l | grep -q libfmt-dev; then
        return 0
    fi
    
    # 检查头文件是否存在
    if [[ -f "/usr/include/fmt/core.h" ]] || [[ -f "/usr/local/include/fmt/core.h" ]]; then
        return 0
    fi
    
    return 1
}

# 在Ubuntu上安装fmt库
install_fmt() {
    echo "Installing fmt library on Ubuntu..."
    sudo apt update
    sudo apt install -y libfmt-dev
}

# 主逻辑
main() {
    # 创建脚本目录
    mkdir -p script
    
    # 创建符号链接
    ln -sf $(pwd)/script/install.sh install.sh
    ln -sf $(pwd)/script/build.sh build.sh
    
    # 检查并安装fmt库
    if check_fmt_installed; then
        echo "fmt library already installed"
    else
        echo "fmt library not found, installing via apt..."
        install_fmt
        echo "fmt library installed successfully"
    fi
    
    echo "Initialization completed"
}

main "$@"