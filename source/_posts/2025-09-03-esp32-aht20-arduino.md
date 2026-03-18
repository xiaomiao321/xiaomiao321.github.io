---
title: ESP32 使用 Adafruit_AHTX0 库读取 AHT20 温湿度数据
date: 2025-09-03 11:30:00 +0800
categories: [Learning, Embedded, Platform, ESP32]
tags: [ESP32, embedded, Arduino, sensor]
description: 使用 ESP32-C3 SuperMini 开发板配合 Adafruit_AHTX0 库读取 AHT20 温湿度传感器的详细教程
toc: true
---

# ESP32 使用 Adafruit_AHTX0 库读取 AHT20 温湿度数据并通过串口输出

## 一、前言

### 1.1 AHT20

#### AHT20 简介

AHT20 是温湿度传感器，配有一个全新设计的 ASIC 专用芯片、一个经过改进的 MEMS 半导体电容式湿度传感元件和一个标准的片上温度传感元件，其性能已经大大提升甚至超出了前一代传感器的可靠性水平，新一代温湿度传感器，经过改进使其在恶劣环境下的性能更稳定。

![AHT20](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedAHT20.jpg)
_AHT20 传感器_

#### AHT20 外观

![AHT20外观](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedAHT20%E5%A4%96%E8%A7%82.png)


_AHT20 外观_

可以发现，AHT20 尺寸很小，而且焊盘在底下而没有伸出来，导致只能使用加热台进行焊接，而几乎不可能用烙铁，不过市面上有带排针的 AHT20 模块

![AHT20模块](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedAHT20%E6%A8%A1%E5%9D%97.jpg)
_带排针的 AHT20 模块_

#### AHT20 引脚定义

![AHT20引脚](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedAHT20%E5%BC%95%E8%84%9A.png)
_AHT20 引脚定义_

#### AHT20 电气特性

![AHT20电气](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedAHT20%E7%94%B5%E6%B0%94.png)
_AHT20 电气特性_

#### AHT20 通讯

有关 IIC 通讯的部分网上有详尽的教程，可参考

- [基础通信协议之 IIC (I2C) 详细讲解](https://blog.csdn.net/qq_39829913/article/details/104718185)
- [4 分钟看懂！I2C 通讯协议 最简单的总线通讯！](https://www.bilibili.com/video/BV1dg4y1H773/)

##### 启动传感器

第一步，将传感器上电，电压为所选择的 VDD 电源电压 (范围介于 2.2V 与 5.5V 之间)。上电后传感器需要不少于 100ms 时间（此时 SCL 为高电平) 以达到空闲状态即做好准备接收由主机 (MCU) 发送的命令

##### 启动/停止时序

每个传输序列都以 Start 状态作为开始并以 Stop 状态作为结束

![开始停止](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%BC%80%E5%A7%8B%E5%81%9C%E6%AD%A2.png)
_启动/停止时序_

##### 发送命令

在启动传输后，随后传输的 I2C 首字节包括 7 位的 I2C 设备地址 0x38 和一个 SDA 方向位 x(读 R：'1'，写 W: '0')。在第 8 个 SCL 时钟下降沿之后，通过拉低 SDA 引脚 (ACK 位)，指示传感器数接收正常。在发送测量命令 0xAC 之后，MCU 必须等到测量完成

##### 读取温湿度

具体细节可参考

- [ESP32 驱动 AHT20 温湿度传感器源代码](https://blog.csdn.net/gyui21g/article/details/138686408)
- [AHT20 中文资料_最新报价_数据手册下载](https://item.szlcsc.com/515997.html)

### 1.2 ESP32-C3 的 SuperMini 的 IIC

按照引脚图，

![ESP32C3](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedESP32C3.png)
_ESP32-C3 SuperMini 引脚图_

默认 SDA 是 GPIO8，SCL 是 GPIO9，实际可以更改为任意 GPIO 进行软件模拟 IIC 时序，我使用的是 GPIO20 为 SDA，GPIO21 为 SCL，只需在程序中加入

```c++
//Wire.begin(I2C_SDA, I2C_SCL);
Wire.begin(20, 21);
```

即可，ESP32-C3 的 IIC 资源详细介绍可参考

- [ESP32C3 学习&开发之路——最全的 IIC 协议](https://blog.csdn.net/RMDYBW/article/details/131761502)

## 二、Arduino 程序讲解

首先，到 Arduino IDE 的库管理——Adafruit_AHTX0，Arduino IDE 会自动安装相关依赖，我使用的是 2.0.5 版本

该库的使用十分简单

| **API/对象** | **参数** | **返回值** | **说明** |
| :------------------------ | :-------------------------------------------------- | :--------- | :----------------------------------------------------------- |
| `Adafruit_AHTX0` | 无 | 无 | 传感器对象构造函数。 |
| `bool begin()` | 无 | bool | 初始化传感器。成功返回 true，失败返回 false。通常需要检查返回值以确保传感器正常工作。 |
| `void getEvent()` | `sensors_event_t* humidity` `sensors_event_t* temp` | 无 | **核心方法**。获取最新的温湿度数据，数据填充到传入的 `humidity` 和 `temp` 对象中。 |
| `sensors_event_t` | 无 | | 用于存储传感器事件数据的结构体，包含测量值、时间戳等信息。 |
| `float temperature` | 无 | float | 从 `sensors_event_t` 结构体中提取温度值（单位：摄氏度）。 |
| `float relative_humidity` | 无 | float | 从 `sensors_event_t` 结构体中提取湿度值（单位：%RH）。 |

### 完整代码

```c++
#include <Adafruit_AHTX0.h>
#include <Wire.h>

Adafruit_AHTX0 aht;

void setup() {
  //Wire.begin(I2C_SDA, I2C_SCL);
  Wire.begin(20, 21);
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degrees C");
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity); Serial.println("% rH");

  delay(500);
}
```

## 三、效果展示

![效果展示](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E6%95%88%E6%9E%9C%E5%B1%95%E7%A4%BA.png)
_串口输出温湿度数据_
