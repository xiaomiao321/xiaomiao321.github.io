---
title: MATLAB 基础学习笔记
date: 2025-02-18 00:32:00 +0800
categories: [Learning, Language]
tags: [MATLAB]
description: MATLAB 基础语法和常用命令学习笔记
toc: true
comments: true
---

## 基本命令

- `clc` 清屏
- `clear + [变量名]` 清除变量
- `a:[b]:c` 从 a 开始，公差为 b，最多到 c
- `save 文件名 [变量名]` 保存变量
- `load 文件名 [变量名]` 导入变量
- `inf` 无穷大
- 语句后加 `;` 不显示结果
- `who` 列出变量
- `whos` 列出变量和类型

## 矩阵操作

- 矩阵用 `[]` 包围，`;` 分列，`,` 分行
- 数组索引：一个数字，两个数字均可如 `A(2),A(1,2)`
- 矩阵除法：`A\B = A^-1^*B`(左除) `A/B = A*B^-1^`
- 矩阵乘法：`A*B`
- `A.*B`:相对应位置的元素运算
- `A./B`,`A.^B`,`A.\B` 同理

## 注释

注释前加 `%`

## 绘图

- `plot(x,y)` x 当横轴，y 当纵轴
- `plot(x,y,'r--','linewidth',2)` 红色虚线，线宽为 2
- `hold on` 在现有的图窗中添加曲线
- `plot(x,y2,'b-')` 蓝色实线
- `legend('sin','cos')` 添加图例
- `xlabel('111')` 标记 x 轴
- `ylabel('222')` 标记 y 轴
- `title('TITLE')` 添加标题
- `set(gca,'fontsize',12)` 设定坐标区字体大小

画完图后复制为向量图（鼠标放在图像上方会显示)，记得写注释，注释要对齐
