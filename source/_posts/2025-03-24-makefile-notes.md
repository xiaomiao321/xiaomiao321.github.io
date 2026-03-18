---
title: Makefile 学习笔记
date: 2025-03-24 18:30:00 +0800
categories: [Learning, Tools]
tags: [Makefile]
description: Makefile 基础学习笔记
toc: true
comments: true
---

> [!NOTE]
>
> 本文档为原始笔记，内容待补充。建议参考 Makefile 官方文档获取更详细的内容。

## Makefile 基本结构

```makefile
target: prerequisites
	command
```

- `target`: 目标文件
- `prerequisites`: 依赖文件
- `command`: 构建命令（必须以 Tab 开头）

## 示例

```makefile
CC = gcc
CFLAGS = -Wall -g

target: main.o utils.o
	$(CC) $(CFLAGS) -o target main.o utils.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o target
```

## 常用变量

- `$@`: 目标文件名
- `$<`: 第一个依赖文件名
- `$^`: 所有依赖文件名
- `$?`: 比目标新的依赖文件

## 伪目标

```makefile
.PHONY: clean all

clean:
	rm -f *.o target

all: target
```
