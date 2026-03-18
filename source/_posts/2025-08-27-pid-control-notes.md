---
title: PID 控制算法学习笔记
date: 2025-08-27 17:41:00 +0800
categories: [Learning, Algorithm]
tags: [pid, control-theory]
description: PID 控制算法基础学习笔记
toc: true
comments: true
---

## 基础

### 引入

保持水龙头流量稳定，还能改变流量

### 适用系统

PID 控制是一种经典的反馈控制算法，广泛应用于工业控制系统中。

> [!NOTE]
>
> 本文档内容较少，建议参考其他 PID 控制相关资料获取更详细的内容。

## PID 控制器组成

PID 控制器由三个部分组成：

- **P（比例）**：与当前误差成正比
- **I（积分）**：与误差的积分（累积）成正比
- **D（微分）**：与误差的变化率成正比

公式：

$$
u(t) = K_p e(t) + K_i \int_0^t e(\tau)d\tau + K_d \frac{de(t)}{dt}
$$

其中：
- $e(t)$ 为误差信号
- $K_p$、$K_i$、$K_d$ 分别为比例、积分、微分系数
