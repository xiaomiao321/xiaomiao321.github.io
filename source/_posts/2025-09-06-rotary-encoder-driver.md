---
title: 旋转编码器驱动 - 状态机精准处理 EC11
date: 2025-09-06 00:00:00 +0800
categories: [Learning, Embedded, Platform, ESP32]
tags: [ESP32, embedded]
description: 使用状态机精准处理 EC11 旋转编码器与按键，实现旋转检测、单击、长按、双击功能
media_subpath: /assets/blog/doc_done/img/
toc: true
comments: true
---

## 一、引言

在嵌入式人机交互领域，旋转编码器因其无限的旋转范围、清晰的段落感以及集成按压功能，成为了许多项目的输入首选。

这里，我们将深入剖析一个用于多功能时钟项目的旋转编码器驱动模块。这段代码不仅稳定可靠地读取旋转方向，更实现了单击、带视觉反馈的长按、以及双击功能。

## 二、增量式编码器 EC11

### 2.1 概述

EC11 的旋转与按下不同，不能当作一个简单的按键来进行处理，它是一种增量式旋转编码器，在原理图中，可以看到 ABC 三个输出通道，其中 C 相接入 GND，AB 两相输出正交信号，相位差为 90°。

### 2.2 电路连接

可参考 [EC11 旋转编码器实验 | 嘉立创教育与开源文档中心](https://wiki.lceda.cn/zh-hans/course-projects/microcontroller/ch32-multimeter/ec11coder-test.html)

这里面加入了滤波电容，而我为了简单，把编码器的接口直接连到了单片机的 IO 口，也可正常使用

### 2.3 输出信号

旋转编码器内部相当于两个开关，其 CLK 和 DT 引脚会输出一种叫做格雷码的序列。格雷码的特点是任意两个相邻的数字其二进制表示只有一位不同，这使得它在旋转过程中不会产生严重的误码。

一次完整的旋转（一格）会产生 4 个状态。假设从静止开始：

**顺时针旋转（CW）一格的典型序列：**

1. 状态 `11` (CLK=1, DT=1) -> 起始状态
2. 状态 `10` (CLK=1, DT=0) -> CLK 保持高，DT 变为低
3. 状态 `00` (CLK=0, DT=0) -> CLK 变为低，DT 保持低
4. 状态 `01` (CLK=0, DT=1) -> CLK 保持低，DT 变为高
5. 状态 `11` (CLK=1, DT=1) -> 回到起始状态，完成一格

**逆时针旋转（CCW）一格的典型序列：**

1. 状态 `11` (CLK=1, DT=1) -> 起始状态
2. 状态 `01` (CLK=0, DT=1) -> CLK 变为低，DT 保持高
3. 状态 `00` (CLK=0, DT=0) -> CLK 保持低，DT 变为低
4. 状态 `10` (CLK=1, DT=0) -> CLK 变为高，DT 保持低
5. 状态 `11` (CLK=1, DT=1) -> 回到起始状态，完成一格

## 三、模块概述

本模块的核心功能是驱动一个标准的增量式旋转编码器，并读取其旋转方向和集成按键的状态。它实现了：

1. **旋转检测**：确识别顺时针/逆时针旋转，并处理抖动。
2. **单击检测**：识别用户的轻按操作。
3. **长按检测**：识别用户的长按操作（如 2 秒），并在屏幕上提供可视化进度条反馈，提升用户体验。
4. **双击检测**：识别用户在短时间内快速的连续两次单击操作，用于触发快捷功能。

## 四、实现思路

### 4.1 旋转检测

#### 法一：状态变化法

这个方法很简单，在 CLK 引脚的电平发生变化时（上升沿或下降沿），去检查 DT 引脚的电平状态。

当 CLK 从高变低（下降沿）时：

- 如果 **DT 为低电平**，则是**顺时针**旋转。
- 如果 **DT 为高电平**，则是**逆时针**旋转。

#### 法二：状态机查表法

**状态编码与存储**

```cpp
uint8_t currentEncoded = (clk << 1) | dt; // 组合新状态
```

这行代码将两个引脚的状态组合成一个 2 位的数字。

- 例如：`CLK=1, DT=1` -> `(1 << 1) | 1 = 3` (二进制 `0b11`)
- `CLK=1, DT=0` -> `(1 << 1) | 0 = 2` (二进制 `0b10`)

这样，`lastEncoded` 和 `currentEncoded` 就可以各表示 4 种状态（0, 1, 2, 3）。

**查找表**

```cpp
static const int8_t transitionTable[] = {0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0};
```

这个数组包含了所有 16 种可能的状态转换结果。**索引的计算方式是：`(lastEncoded << 2) | currentEncoded`**。

- `lastEncoded` 是旧状态（0-3），左移 2 位后变成高 2 位（0, 4, 8, 12）。
- `currentEncoded` 是新状态（0-3），作为低 2 位。
- 这样组合出的索引范围是 0 到 15，正好对应数组的 16 个元素。

**这个表是如何工作的？**

让我们用顺时针序列来验证：

1. 从 `11` (3) 转到 `10` (2)：索引 = `(3 << 2) | 2 = 14` -> `transitionTable[14] = 1` (顺时针)
2. 从 `10` (2) 转到 `00` (0)：索引 = `(2 << 2) | 0 = 8` -> `transitionTable[8] = 1` (顺时针)
3. 从 `00` (0) 转到 `01` (1)：索引 = `(0 << 2) | 1 = 1` -> `transitionTable[1] = 1` (顺时针)
4. 从 `01` (1) 转到 `11` (3)：索引 = `(1 << 2) | 3 = 7` -> `transitionTable[7] = 1` (顺时针)

逆时针序列也会产生连续的 `-1`。而无效的跳变（如由抖动引起）在表中对应的值大多是 `0`。

**累加器与滤波**

```cpp
deltaSum += deltaValue; // 来自查表的值 (-1, 0, 1)

if (deltaSum >= 2) {
    ... // 触发顺时针
    deltaSum = 0; // 重置
} else if (deltaSum <= -2) {
    ... // 触发逆时针
    deltaSum = 0; // 重置
}
```

### 4.2 按键检测：状态机与时间戳

按键处理是一个复杂的状态机问题。我们需要通过记录按下时刻的时间戳和状态转换来清晰区分**单击**、**长按**和**双击**。

**关键难点在于如何无歧义地区分三者？**

我们的策略是使用一个四状态的状态机 (`ButtonState`)：

- **IDLE (空闲)**：等待第一次按下。
- **PRESSED (第一次按下)**：记录按下时间，等待释放。在此状态下，`readButtonLongPress()` 函数会检查是否达到长按阈值。
- **RELEASED (第一次释放)**：此时启动一个定时器（`doubleClickTimeout`），在此窗口内：
  - 如果用户再次按下，则进入 `DOUBLE_PRESSED` 状态。
  - 如果定时器超时，则判定这是一次**单击**，并触发单击事件。
- **DOUBLE_PRESSED (第二次按下)**：等待第二次释放，一旦释放，立即标记**双击**事件。

**状态机工作流程：**

```
      [BTN_IDLE]
          | (按下)
          v
      [BTN_PRESSED] <---[长按发生]---> (触发长按)
          | (释放)
          v
      [BTN_RELEASED] ---(超时)---> [BTN_IDLE] & 触发单击
          | (再次按下)
          v
      [BTN_DOUBLE_PRESSED]
          | (释放)
          v
      [BTN_IDLE] & 标记双击
```

这种设计确保了长按优先于双击（因为长按在第一次按下期间就已判定），并且单击是双击的超时后备，逻辑清晰，无歧义。

为消除长按时的焦虑，代码在按住 1 秒后（`progressBarStartTime`）开始在 TFT 屏幕上绘制一个逐渐增长的进度条，直观地提示还需按住多久才能触发长按功能。

## 五、核心代码

### 旋转编码器初始化

```cpp
void initRotaryEncoder() {
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  lastEncoded = (digitalRead(ENCODER_CLK) << 1) | digitalRead(ENCODER_DT);
  Serial.println("Rotary Encoder Initialized.");
}
```

### 读取旋转方向（状态变化法）

```cpp
int readEncoder() {
  static int lastCLK_State = HIGH;
  int currentCLK_State = digitalRead(ENCODER_CLK);
  int delta = 0;

  if (currentCLK_State != lastCLK_State) {
    delayMicroseconds(500); // 消抖
    currentCLK_State = digitalRead(ENCODER_CLK);
    int currentDT_State = digitalRead(ENCODER_DT);

    if (currentCLK_State == LOW) {
      if (currentDT_State == LOW) {
        delta = 1;  // 顺时针
        encoderPos++;
      } else {
        delta = -1; // 逆时针
        encoderPos--;
      }
    }
    lastCLK_State = currentCLK_State;
  }

  return delta;
}
```

### 按键状态机核心

```cpp
int readButton() {
  int currentButtonState = digitalRead(ENCODER_SW);
  bool singleClickTriggered = false;
  unsigned long currentTime = millis();

  switch (buttonFSM) {
    case BTN_IDLE:
      if (currentButtonState == LOW) {
        buttonFSM = BTN_PRESSED;
        buttonPressStartTime = currentTime;
        longPressHandled = false;
        clickHandled = false;
        doubleClickDetected = false;
      }
      break;

    case BTN_PRESSED:
      if (currentButtonState == HIGH) {
        firstReleaseTime = currentTime;
        buttonFSM = BTN_RELEASED;
      }
      break;

    case BTN_RELEASED:
      if (currentTime - firstReleaseTime > doubleClickTimeout) {
        if (!clickHandled) {
          singleClickTriggered = true;
          clickHandled = true;
        }
        buttonFSM = BTN_IDLE;
      }
      if (currentButtonState == LOW) {
        buttonFSM = BTN_DOUBLE_PRESSED;
      }
      break;

    case BTN_DOUBLE_PRESSED:
      if (currentButtonState == HIGH) {
        doubleClickDetected = true;
        buttonFSM = BTN_IDLE;
      }
      break;
  }
  return singleClickTriggered;
}
```

### 长按检测

```cpp
bool readButtonLongPress() {
  bool triggered = false;

  if (buttonFSM == BTN_PRESSED && !longPressHandled) {
    unsigned long currentHoldTime = millis() - buttonPressStartTime;

    // 显示进度条
    if (currentHoldTime >= progressBarStartTime) {
        float progress = (float)(currentHoldTime - progressBarStartTime) / 
                         (longPressThreshold - progressBarStartTime);
        progress = (progress > 1.0) ? 1.0 : progress;
        menuSprite.drawRect(BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT, TFT_WHITE);
        menuSprite.fillRect(BAR_X + 2, BAR_Y + 2, 
                           (int)((BAR_WIDTH - 4) * progress), 
                           BAR_HEIGHT - 4, TFT_BLUE);
        menuSprite.pushSprite(0,0);
    }

    // 长按触发
    if (currentHoldTime >= longPressThreshold) {
        triggered = true;
        longPressHandled = true;
        clickHandled = true;
    }
  }

  // 清理进度条
  if (digitalRead(ENCODER_SW) == HIGH) {
      if (buttonPressStartTime != 0 && 
          (millis() - buttonPressStartTime) > progressBarStartTime) {
          menuSprite.fillRect(BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT, TFT_BLACK);
          menuSprite.pushSprite(0,0);
      }
  }

  return triggered;
}
```

### 双击检测

```cpp
bool readDoubleClick() {
  if (doubleClickDetected) {
    doubleClickDetected = false;
    return true;
  }
  return false;
}
```

## 六、使用示例

```cpp
#include "RotaryEncoder.h"

void setup() {
  initRotaryEncoder();
}

void loop() {
  int clickEvent = readButton();
  int rotation = readEncoder();
  
  if (rotation != 0) {
    Serial.println(rotation == 1 ? "CW" : "CCW");
  }

  if (clickEvent) {
    Serial.println("Single Click");
  }

  if (readButtonLongPress()) {
    Serial.println("Long Press");
  }

  if (readDoubleClick()) {
    Serial.println("Double Click!");
  }

  delay(1);
}
```

## 七、改进方向

1. **中断方式**：当前是轮询方式。对于主循环任务繁重的系统，可以将 CLK/DT 引脚接入外部中断，在中断服务程序中快速处理状态变化，进一步提高响应速度。
2. **回调函数机制**：使用回调函数来替代轮询检测，可以进一步简化主循环逻辑。
