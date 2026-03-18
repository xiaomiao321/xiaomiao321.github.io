---
title: ESP32-C3 读取芯片内部温度
date: 2025-09-03 22:44:00 +0800
categories: [Learning, Embedded, Platform, ESP32]
tags: [ESP32, embedded, sensor, Arduino]
description: 使用 ESP32-C3 内置温度传感器读取芯片内部温度的简单教程
toc: true
---

# 【Arduino】ESP32-C3 读取芯片内部温度

## 一、前言

根据文档，ESP32-C3 的温度传感器可产生随温度变化的电压。该电压通过内部 ADC 转换为数字值。

温度传感器的测量范围为–40°C 至 125°C。它主要用于检测芯片内部的温度变化。温度值取决于微控制器时钟频率或 I/O 负载等因素。通常，芯片的内部温度会高于其工作环境温度。

> [!NOTE]
> 这个温度传感器主要用于检测芯片内部的温度变化，而非精确测量环境温度。如需测量环境温度，建议使用外部温度传感器如 DS18B20、AHT20 等。

## 二、代码

```c++
#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("ESP32-C3 温度测试开始");
}

void loop() {
  float temp = temperatureRead();
  char buf[32];
  snprintf(buf, sizeof(buf), "ESP32C3_TEMP:%.1f\n", temp);
  Serial.print(buf);
  delay(1000);
}
```

### 代码说明

1. **`temperatureRead()` 函数**：这是 ESP32  Arduino 核心提供的内置函数，直接读取芯片内部温度传感器的值
2. **串口输出**：通过串口监视器可以实时查看温度数据
3. **采样间隔**：示例中设置为 1 秒，可根据实际需求调整

### 运行结果

打开 Arduino IDE 的串口监视器（波特率 115200），可以看到类似输出：

```
ESP32-C3 温度测试开始
ESP32C3_TEMP:45.2
ESP32C3_TEMP:45.3
ESP32C3_TEMP:45.1
...
```

## 三、注意事项

1. **温度偏差**：芯片内部温度通常比环境温度高 10-20°C
2. **影响因素**：
   - CPU 负载
   - WIFI 使用情况
   - 外设工作状态
3. **应用场景**：
   - 监测芯片过热情况
   - 温度补偿算法
   - 粗略的环境温度估计
