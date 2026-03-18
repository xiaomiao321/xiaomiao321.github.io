---
title: CMake 学习笔记
date: 2025-04-06 17:05:00 +0800
categories: [Learning, Tools]
tags: [CMake]
description: CMake 自动生成 Makefile 工具学习笔记
toc: true
comments: true
---

## CMake 基本命令

### cmake_minimum_required

指定使用的 cmake 的最低版本

可选，非必须，如果不加可能会有警告

### project

定义工程名称，并可指定工程的版本、工程描述、web 主页地址、支持的语言（默认情况支持所有语言），如果不需要这些都是可以忽略的，只需要指定出工程名字即可

```cmake
# PROJECT 指令的语法是：
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME>
       [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
       [DESCRIPTION <project-description-string>]
       [HOMEPAGE_URL <url-string>]
       [LANGUAGES <language-name>...])
```

### add_executable

定义工程会生成一个可执行程序

```cmake
add_executable(可执行程序名 源文件名称)
```

这里的可执行程序名和 project 中的项目名没有任何关系

源文件名可以是一个也可以是多个，如有多个可用空格或 `;` 间隔

### 完整的 CMakeLists.txt 示例

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
add_executable(app add.c div.c main.c mult.c sub.c)
```

编写好后，执行：

```bash
cmake <CMakeLists.txt 所在路径>
make
```

但是这样的话中间文件太多了，可以新建一个 `build` 目录，在里面运行：

```bash
cmake ..
```

## 源文件列表管理

要是文件名太多，可以合成一个：

```cmake
# 方式 1: 各个源文件之间使用空格间隔
# set(SRC_LIST add.c  div.c   main.c  mult.c  sub.c)

# 方式 2: 各个源文件之间使用分号 ; 间隔
set(SRC_LIST add.c;div.c;main.c;mult.c;sub.c)
add_executable(app  ${SRC_LIST})
```

## 指定输出路径

在 CMake 中指定可执行程序输出的路径，也对应一个宏，叫做 `EXECUTABLE_OUTPUT_PATH`，它的值还是通过 set 命令进行设置：

```cmake
set(HOME /home/robin/Linux/Sort)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
```

第一行：定义一个变量用于存储一个绝对路径
第二行：将拼接好的路径值设置给 `EXECUTABLE_OUTPUT_PATH` 宏。如果这个路径中的子目录不存在，会自动生成，无需自己手动创建

由于可执行程序是基于 cmake 命令生成的 makefile 文件然后再执行 make 命令得到的，所以如果此处指定可执行程序生成路径的时候使用的是相对路径 `./xxx/xxx`，那么这个路径中的 `./` 对应的就是 makefile 文件所在的那个目录。

## 搜索文件

如果一个项目里边的源文件很多，在编写 CMakeLists.txt 文件的时候不可能将项目目录的各个文件一一罗列出来，这样太麻烦也不现实。所以，在 CMake 中为我们提供了搜索文件的命令，可以使用 `aux_source_directory` 命令或者 `file` 命令。

### 方式 1：aux_source_directory

在 CMake 中使用 `aux_source_directory` 命令可以查找某个路径下的所有源文件，命令格式为：

```cmake
aux_source_directory(<dir> <variable>)
```

- `dir`：要搜索的目录
- `variable`：将从 dir 目录下搜索到的源文件列表存储到该变量中

例如：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
# 搜索 src 目录下的源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
add_executable(app  ${SRC_LIST})
```

### 方式 2：file

```cmake
file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型)
```

- **GLOB**: 将指定目录下搜索到的满足条件的所有文件名生成一个列表，并将其存储到变量中。
- **GLOB_RECURSE**：递归搜索指定目录，将搜索到的满足条件的文件名生成一个列表，并将其存储到变量中。

例如，搜索当前目录的 src 目录下所有的源文件，并存储到变量中：

```cmake
file(GLOB MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
```

**注意**：`CMAKE_CURRENT_SOURCE_DIR` 宏表示当前访问的 CMakeLists.txt 文件所在的路径。

## 指定头文件路径

```cmake
include_directories(headpath)
```

例如：

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
set(CMAKE_CXX_STANDARD 11)
set(HOME /home/robin/Linux/calc)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin/)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(app  ${SRC_LIST})
```

`PROJECT_SOURCE_DIR` 宏对应的值就是我们在使用 cmake 命令时，后面紧跟的目录，一般是工程的根目录。

## CMake 基本结构

```cmake
cmake_minimum_required(VERSION 3.0)
project(ProjectName)
add_executable(target source1.cpp source2.cpp)
```

## 常用命令

- `cmake_minimum_required`: 指定最低版本
- `project`: 定义项目名称
- `add_executable`: 添加可执行文件
- `add_library`: 添加库文件
- `target_link_libraries`: 链接库
- `include_directories`: 包含头文件目录
- `add_subdirectory`: 添加子目录

## 变量和缓存

```cmake
set(VAR_NAME value)
set(VAR_NAME value CACHE TYPE "description")
```

## 条件判断

```cmake
if(CONDITION)
    # ...
elseif(ANOTHER_CONDITION)
    # ...
else()
    # ...
endif()
```

## 循环

```cmake
foreach(item ${ITEM_LIST})
    # ...
endforeach()

while(CONDITION)
    # ...
endwhile()
```
