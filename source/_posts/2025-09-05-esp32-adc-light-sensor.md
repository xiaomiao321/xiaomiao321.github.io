---
title: ESP32 光敏电阻 ADC 采集与 TFT 显示
date: 2025-09-02 23:09:00 +0800
categories: [Learning, Embedded, Platform, ESP32]
tags: [ESP32, embedded, adc, sensor, Arduino]
description: 基于 ESP32 构建智能光照监测系统，通过 ADC 采集光敏电阻数据并转换为 Lux 值显示在 TFT 屏幕上
toc: true
---

# ESP32 光敏电阻 ADC 采集

> 在现代物联网应用中，环境光照监测是一个常见且重要的功能。本文将详细介绍如何基于 ESP32 微控制器构建一个智能光照监测系统，通过 ADC 采集光敏电阻数据，并转换为直观的 Lux 值显示在 TFT 屏幕上。

## 零、准备工作

### 硬件准备

- 一块 ESP32 开发板，我使用的是 ESP32-C3 Super Mini 开发板，引脚定义如下

![ESP32C3 引脚图](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedESP32C3.png)
_ESP32-C3 SuperMini 引脚定义_

## 一、系统概述

本系统基于 ESP32 平台，结合光敏电阻和分压电路，实现了环境光照强度的精确测量。系统采用 TFT 显示屏提供直观的用户界面，包含模拟表盘和数字显示两种数据呈现方式，并通过进度条直观展示光照强度变化。

## 二、硬件设计

系统使用了一个简单的分压电路，其中光敏电阻作为可变电阻与固定电阻串联。当环境光照变化时，光敏电阻的阻值随之改变，从而导致分压点电压变化。ESP32 的 ADC 模块检测这一电压变化，并通过特定算法将其转换为光照强度值 (Lux)。

![光敏电阻原理](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%85%89%E6%95%8F%E7%94%B5%E9%98%BB%E5%8E%9F%E7%90%86.png)
_光敏电阻分压电路原理图_

硬件参数：
- 固定电阻值：20kΩ
- 光敏电阻参数：

![光敏电阻参数](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%85%89%E6%95%8F%E7%94%B5%E9%98%BB%E5%8F%82%E6%95%B0.png)
_光敏电阻特性参数_

- ADC 配置：12 位精度，12dB 衰减

## 三、软件架构解析

### 3.1 ADC 初始化与校准

系统首先对 ESP32 的 ADC 模块进行初始化和校准，这是确保测量精度的关键步骤：

```cpp
void setupADC() {
    adc1_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);
    cali_enable = adc_calibration_init();
}
```

校准函数检查 ESP32 的 eFuse 中存储的校准值，如果可用则使用这些值提高 ADC 测量精度：

```cpp
static bool adc_calibration_init() {
    esp_err_t ret = esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP);
    if (ret == ESP_ERR_NOT_SUPPORTED) return false;
    if (ret == ESP_ERR_INVALID_VERSION) return false;
    if (ret == ESP_OK) {
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH, 0, &adc1_chars);
        return true;
    }
    return false;
}
```

### 3.2 数据采集与处理

系统创建了一个独立任务负责 ADC 数据的采集和处理：

```cpp
xTaskCreatePinnedToCore(ADC_Task, "ADC_Task", 4096, NULL, 1, NULL, 0);
```

在 ADC 任务中，系统采用多次采样取平均的方法提高测量稳定性：

```cpp
uint32_t sum = 0;
const int samples = 50;
for (int i = 0; i < samples; i++) {
    sum += adc1_get_raw(ADC_CHANNEL);
    delay(1);
}
sum /= samples;
```

### 3.3 电压转换算法

根据 ADC 校准状态，系统采用不同的电压转换方法：

```cpp
float voltage_v = 0;
if (cali_enable) {
    uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(sum, &adc1_chars);
    voltage_v = voltage_mv / 1000.0f;
} else {
    voltage_v = (sum * 3.3) / 4095.0;
}
```

### 3.4 Lux 值计算原理

系统通过光电特性公式将电压值转换为光照强度值 (Lux)：

```cpp
float r_photo = (voltage_v * R_FIXED) / (3.3f - voltage_v);
float lux = pow((r_photo / R10), (1.0f / -GAMMA)) * 10.0f;
```

这一计算基于光敏电阻的非线性特性，使用 Gamma 系数进行校正，确保在不同光照条件下都能获得准确的测量结果。

## 四、UI 设计

系统采用双显示区域设计，上方为模拟表盘，下方为数字信息显示区域。

### 4.1 模拟表盘实现

使用 TFT_eWidget 库创建模拟电压表盘：

```cpp
MeterWidget volts = MeterWidget(&tft);
volts.analogMeter(0, 0, 3.3f, "V", "0", "0.8", "1.6", "2.4", "3.3");
```

实时更新表针位置反映当前电压值：

```cpp
volts.updateNeedle(voltage_v, 0);
```

### 4.2 数字信息显示

采用 Sprite 技术实现无闪烁更新：

```cpp
menuSprite.fillSprite(TFT_BLACK);
menuSprite.setTextSize(2);
menuSprite.setTextColor(TFT_WHITE, TFT_BLACK);

// 显示 Lux 值
menuSprite.setCursor(20, 10);
menuSprite.print("LUX: "); menuSprite.print(luxStr);

// 显示电压值
menuSprite.setCursor(20, 35);
menuSprite.print("VOL: "); menuSprite.print(voltStr);

// 显示 ADC 原始值
menuSprite.setCursor(20, 60);
menuSprite.print("ADC: "); menuSprite.print(sum);
```

### 4.3 进度条可视化

通过进度条直观展示光照强度：

```cpp
float constrainedLux = constrain(lux, 0.0f, 1000.0f);
int barWidth = map((long)constrainedLux, 0L, 100L, 0L, 200L);
menuSprite.drawRect(20, 85, 202, 22, TFT_WHITE);
menuSprite.fillRect(21, 86, 200, 20, TFT_BLACK);
menuSprite.fillRect(21, 86, barWidth, 20, TFT_GREEN);
```

## 五、完整代码

```c++
#include <Arduino.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include <TFT_eSPI.h>
#include <TFT_eWidget.h>

// TFT 显示屏配置
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite menuSprite = TFT_eSprite(&tft);

// 模拟表盘
MeterWidget volts = MeterWidget(&tft);

// ADC 配置
#define ADC_PIN 34
#define ADC_CHANNEL ADC1_CHANNEL_6  // GPIO34 对应 ADC1_CHANNEL_6
#define ADC_ATTEN ADC_ATTEN_DB_12
#define ADC_WIDTH ADC_WIDTH_BIT_12

// 光敏电阻参数
const float R_FIXED = 20000.0f;    // 固定电阻 20kΩ
const float R10 = 8000.0f;         // 参考电阻 8kΩ
const float GAMMA = 0.6f;          // Gamma 系数

// ADC 校准
static esp_adc_cal_characteristics_t adc1_chars;
bool cali_enable = false;

// 函数声明
static bool adc_calibration_init();
void setupADC();
float readADCVoltage();
float calculateLux(float voltage_v);
void updateDisplay(float voltage_v, uint32_t adc_value, float lux);

void setup() {
  Serial.begin(115200);

  // 初始化 TFT 显示屏
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);

  // 创建菜单精灵
  menuSprite.createSprite(240, 100);

  // 初始化 ADC
  setupADC();

  // 绘制模拟表盘
  volts.analogMeter(0, 0, 3.3f, "V", "0", "0.8", "1.6", "2.4", "3.3");

  Serial.println("ESP32 光敏电阻监测系统启动完成");
  Serial.println("==================================");
}

void loop() {
  // 读取 ADC 电压值
  float voltage_v = readADCVoltage();

  // 读取原始 ADC 值（用于显示）
  uint32_t adc_value = adc1_get_raw(ADC_CHANNEL);

  // 计算 Lux 值
  float lux = calculateLux(voltage_v);

  // 更新表盘显示
  volts.updateNeedle(voltage_v, 0);

  // 更新数字信息显示
  updateDisplay(voltage_v, adc_value, lux);

  // 串口输出调试信息
  Serial.printf("ADC: %4d, Voltage: %.3fV, Lux: %.1f\n",
                adc_value, voltage_v, lux);

  // 延时 100ms
  delay(100);
}

// ADC 校准初始化
static bool adc_calibration_init() {
    esp_err_t ret = esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        Serial.println("ADC 校准：eFuse 不支持");
        return false;
    }
    if (ret == ESP_ERR_INVALID_VERSION) {
        Serial.println("ADC 校准：eFuse 版本无效");
        return false;
    }
    if (ret == ESP_OK) {
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH, 0, &adc1_chars);
        Serial.println("ADC 校准：使用 eFuse 校准值");
        return true;
    }
    return false;
}

// 设置 ADC
void setupADC() {
    Serial.println("初始化 ADC...");

    // 配置 ADC
    adc1_config_width(ADC_WIDTH);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

    // 尝试初始化校准
    cali_enable = adc_calibration_init();

    if (!cali_enable) {
        Serial.println("ADC 校准：使用软件校准");
    }

    pinMode(ADC_PIN, INPUT); // 设置 ADC 引脚为输入模式
}

// 读取 ADC 电压值
float readADCVoltage() {
    uint32_t sum = 0;
    const int samples = 50;

    // 多次采样取平均
    for (int i = 0; i < samples; i++) {
        sum += adc1_get_raw(ADC_CHANNEL);
        delay(1);
    }
    sum /= samples;

    float voltage_v = 0;

    if (cali_enable) {
        // 使用硬件校准
        uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(sum, &adc1_chars);
        voltage_v = voltage_mv / 1000.0f;
    } else {
        // 使用软件计算
        voltage_v = (sum * 3.3) / 4095.0;
    }

    return voltage_v;
}

// 计算 Lux 值
float calculateLux(float voltage_v) {
    // 避免除零错误
    if (voltage_v >= 3.3f) {
        return 0.0f;
    }

    // 计算光敏电阻阻值
    float r_photo = (voltage_v * R_FIXED) / (3.3f - voltage_v);

    // 计算 Lux 值（使用光电特性公式）
    float lux = pow((r_photo / R10), (1.0f / -GAMMA)) * 10.0f;

    return lux;
}

// 更新显示
void updateDisplay(float voltage_v, uint32_t adc_value, float lux) {
    // 清空精灵
    menuSprite.fillSprite(TFT_BLACK);
    menuSprite.setTextSize(2);
    menuSprite.setTextColor(TFT_WHITE, TFT_BLACK);

    // 显示 Lux 值
    char luxStr[10];
    dtostrf(lux, 4, 1, luxStr);
    menuSprite.setCursor(20, 10);
    menuSprite.print("LUX: ");
    menuSprite.print(luxStr);

    // 显示电压值
    char voltStr[10];
    dtostrf(voltage_v, 4, 2, voltStr);
    menuSprite.setCursor(20, 35);
    menuSprite.print("VOL: ");
    menuSprite.print(voltStr);

    // 显示 ADC 原始值
    menuSprite.setCursor(20, 60);
    menuSprite.print("ADC: ");
    menuSprite.print(adc_value);

    // 绘制进度条
    float constrainedLux = constrain(lux, 0.0f, 1000.0f);
    int barWidth = map((long)constrainedLux, 0L, 1000L, 0L, 200L);
    menuSprite.drawRect(20, 85, 202, 22, TFT_WHITE);
    menuSprite.fillRect(21, 86, 200, 20, TFT_BLACK);
    menuSprite.fillRect(21, 86, barWidth, 20, TFT_GREEN);

    // 更新显示
    menuSprite.pushSprite(0, 130);
}
```
