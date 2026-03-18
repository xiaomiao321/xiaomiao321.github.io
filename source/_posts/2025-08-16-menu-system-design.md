---
title: 多功能时钟菜单系统设计
date: 2025-08-16 15:53:00 +0800
categories: [Learning, Embedded, Platform, ESP32]
tags: [ESP32, embedded, animation, Arduino]
description: 多功能时钟菜单系统设计，包含表驱动设计、双缓冲渲染、缓动动画等技术
media_subpath: /assets/blog/doc_done/img/
toc: true
comments: true
---

## 一、前言

菜单系统是多功能时钟的核心交互界面，它为用户提供了一个统一的入口来访问设备的所有功能，如时钟、倒计时、天气等。本模块的目标是实现一个响应快速、滚动平滑、易于扩展的横向菜单。用户通过旋转编码器在不同功能间切换，并通过旋转编码器的按键确认选择。

## 二、实现思路

### 2.1 表驱动设计

为了达成设计目标，我们首先解决了菜单项的数据结构问题。需求是需要一种统一的方式来管理每个菜单项的名称、图标和对应的执行逻辑，对此我们采用了 `struct` 数组结合函数指针的方案。这种"表驱动"的方法非常适合嵌入式项目，它将数据和行为绑定，同时保持了高度的模块化，可维护性很高。

```cpp
struct MenuItem {
    const char *name;              // 菜单项名称
    const uint16_t *image;         // 指向图标图像数据的指针
    void (*action)();              // 指向功能入口函数的指针
};

const MenuItem menuItems[] = {
    {"Clock", Weather, &weatherMenu},
    {"Countdown", Timer, &CountdownMenu},
    {"Alarm", alarm_img, &AlarmMenu},
    {"Pomodoro", tomato, &PomodoroMenu},
    {"Stopwatch", Timer, &StopwatchMenu},
    {"Music", Music, &BuzzerMenu},
    {"Music Lite", music_lite, &MusicMenuLite},
    {"Performance", Performance, &performanceMenu},
    {"Temperature",Temperature, &DS18B20Menu},
    {"Animation",LED, &AnimationMenu},
    {"Games", Games, &GamesMenu},
    {"LED", LED, &LEDMenu},
    {"ADC", ADC, &ADCMenu},
};
```

### 2.2 双缓冲渲染

为了在单片机有限的刷新率下保证画面无闪烁，我们使用了 `TFT_eSPI` 库提供的精灵（Sprite）功能。它本质上是一个内存中的画布，所有绘制操作都先在内存中完成，然后一次性将最终画面传送到物理屏幕，这种双缓冲机制能完全避免视觉闪烁问题。

```cpp
void drawMenuIcons(int16_t offset) {
    // 清除图标和三角形绘制的区域
    menuSprite.fillRect(0, ICON_Y_POS, SCREEN_WIDTH, SCREEN_HEIGHT - ICON_Y_POS, TFT_BLACK);
    menuSprite.fillRect(0, 0, SCREEN_WIDTH, 40, TFT_BLACK);

    // 绘制三角形指示器
    int16_t triangle_x = offset + (picture_flag * ICON_SPACING) + (ICON_SIZE / 2);
    menuSprite.fillTriangle(triangle_x, SCREEN_HEIGHT - 25, 
                           triangle_x - 12, SCREEN_HEIGHT - 5, 
                           triangle_x + 12, SCREEN_HEIGHT - 5, TFT_WHITE);

    // 绘制图标（带视口裁剪）
    for (int i = 0; i < MENU_ITEM_COUNT; i++) {
        int16_t x = offset + (i * ICON_SPACING);
        if (x >= -ICON_SIZE && x < SCREEN_WIDTH) {
            menuSprite.pushImage(x, ICON_Y_POS, ICON_SIZE, ICON_SIZE, menuItems[i].image);
        }
    }

    // 绘制文字
    menuSprite.setTextColor(TFT_WHITE, TFT_BLACK);
    menuSprite.setTextSize(2);
    menuSprite.setTextDatum(TC_DATUM);
    menuSprite.drawString(menuItems[picture_flag].name, SCREEN_WIDTH / 2, 10);

    menuSprite.pushSprite(0, 0); // 推送到屏幕
}
```

### 2.3 缓动动画

为了实现平滑的滚动动画，我们应用了缓动函数（Easing Function），具体为 `easeOutBack`。相比于速度恒定的线性动画，缓动函数通过非线性的方式计算动画进程，可以模拟出带有弹性的物理效果，使交互体验更佳。

```cpp
float easeOutBack(float t) {
    const float c1 = 1.70158f;
    const float c3 = c1 + 1.0f;
    float t_minus_1 = t - 1.0f;
    return 1.0f + c3 * t_minus_1 * t_minus_1 * t_minus_1 + c1 * t_minus_1 * t_minus_1;
}

// 动画循环
for (uint8_t i = 0; i <= ANIMATION_STEPS; i++) {
    float t = (float)i / ANIMATION_STEPS;
    float eased_t = easeOutBack(t);
    display = start_display + (target_display - start_display) * eased_t;
    drawMenuIcons(display);
    vTaskDelay(pdMS_TO_TICKS(20));
}
```

## 三、核心代码

### 菜单项定义

```cpp
struct MenuItem {
    const char *name;
    const uint16_t *image;
    void (*action)();
};

const MenuItem menuItems[] = {
    {"Clock", Weather, &weatherMenu},
    {"Countdown", Countdown, &CountdownMenu},
    // ... 更多菜单项
};
```

### UI 渲染与视口裁剪

```cpp
void drawMenuIcons(int16_t offset) {
    // 清理 Sprite 画布
    menuSprite.fillRect(0, ICON_Y_POS, SCREEN_WIDTH, SCREEN_HEIGHT - ICON_Y_POS, TFT_BLACK);
    menuSprite.fillRect(0, 0, SCREEN_WIDTH, 40, TFT_BLACK);

    // 遍历所有菜单项
    for (int i = 0; i < MENU_ITEM_COUNT; i++) {
        int16_t x = offset + (i * ICON_SPACING);
        // 视口裁剪：只绘制在屏幕可视范围内的图标
        if (x >= -ICON_SIZE && x < SCREEN_WIDTH) {
            menuSprite.pushImage(x, ICON_Y_POS, ICON_SIZE, ICON_SIZE, menuItems[i].image);
        }
    }

    // 绘制标题和指示器
    menuSprite.pushSprite(0, 0);
}
```

### 动画循环与插值

```cpp
if (direction != 0) {
    current_state = ANIMATING;

    if (direction == 1) {
        picture_flag = (picture_flag + 1) % MENU_ITEM_COUNT;
    } else {
        picture_flag = (picture_flag == 0) ? MENU_ITEM_COUNT - 1 : picture_flag - 1;
    }

    int16_t start_display = display;
    int16_t target_display = INITIAL_X_OFFSET - (picture_flag * ICON_SPACING);

    for (uint8_t i = 0; i <= ANIMATION_STEPS; i++) {
        float t = (float)i / ANIMATION_STEPS;
        float eased_t = easeOutBack(t);
        display = start_display + (target_display - start_display) * eased_t;
        drawMenuIcons(display);
        vTaskDelay(pdMS_TO_TICKS(20));
    }

    display = target_display;
    drawMenuIcons(display);
    current_state = MAIN_MENU;
}
```

## 四、总结与展望

该菜单系统通过表驱动设计、双缓冲渲染和缓动动画三大核心技术，成功构建了一个用户体验良好且易于维护的 UI 框架。

**未来的可扩展方向：**

1. 为设置等复杂模块构建层级更深的二级菜单
2. 根据系统状态（如是否联网）动态显示或隐藏某些菜单项
3. 将颜色、字体等 UI 元素配置化，以支持一键换肤
