# libmoudbus-test


## 一、工程整体介绍

本工程用于上位机LibModBus-RTU通信，开发环境只限于Linux.


工程中包含三大内容：基础通信测试、数据API封装、基于NATS的数据发布，开发流程如下：


| <center> 完成度 | <center> 模块名称| <center> 描述 |
| ----  | ----             | ---- |
| <center> 已完成 | <center> 基础通信测试 | <center> 一次性收发数据测试+分频段收发数据测试 |
| <center> ING | <center> 数据API封装 | <center> 数据解析 |
| <center> 待定 | <center> 基于NATS的数据发布 | <center> NATS转发数据 |


## 二、工程编译运行

``
    本工程使用 xmake 编译运行代码，所需工具包有libmoudbus、fmt，接下来我们安装环境、编译和运行代码
``

### 2.0 克隆代码

`` git clone https://github.com/weixizhou/libmoudbus-test.git ``


### 2.1 安装依赖包

`` sudo apt install libfmt-dev xmake ``


### 2.2 编译工程

`` cd libmoudbus-test && xmake -v ``


### 2.3 运行工程

`` xmake run ``


## 三、工程使用

### 3.0 串口和波特率设置

| <center> 宏定义 | <center> 数据说明 |
| ----  | ---- |
| <center> MODBUS_BAUD | <center> 波特率[1500000] |
| <center> MODBUS_DEVICE | <center> 串口设备[/dev/ttyUSB0] |


