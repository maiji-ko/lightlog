# loglight

## 一、什么是 loglight ?

LightLog 是一个基于 C++20 开发的轻量级日志库，提供了灵活的日志记录功能。

## 二、目前实现了哪些

- [ ] 简化接口及使用
- [x] 日志输出到控制台
    - [ ] 多线程支持
- [x] 日志输出到文件
    - [ ] 实现 daily log(设置日志文件保存周期)
    - [ ] 实现 rotating  log(设置日志文件保存大小及数量)


## 三、如何使用

1. 在 `linux` 终端中输入
``` bash
bash init.sh
```

2. 开始构建及用例运行
``` bash
bash build.sh
```

3. 将生成的动态库链接到工程
