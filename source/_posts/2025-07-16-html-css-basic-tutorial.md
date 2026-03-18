---
title: HTML 与 CSS 基础入门教程
date: 2025-07-16 16:56:00 +0800
categories: [Learning, Language]
tags: [html, css, web, frontend]
description: HTML 与 CSS 基础入门教程，包含常用标签、样式设置、页面布局等核心概念
toc: true
---

# HTML 与 CSS 基础入门教程

## 一、HTML 与 CSS 简介

HTML（HyperText Markup Language）是标记语言，决定了网页有哪些内容；CSS（Cascading Style Sheets）负责美化，决定了图片样式、文字排版等视觉效果。

网站首页一般为 `index.html`。

## 二、HTML 基本结构

HTML 使用成对出现的标签来决定内容，`<html>` 和 `</html>` 决定了整个网站的开始与结束。

### 2.1 基本文档结构

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>

</body>
</html>
```

- `<head>`：不会显示在网页中，主要用于设置文件的字符编码、关键字、程式脚本等元数据
- `<body>`：用户看到的内容都放在这里

> [!TIP]
> 在编辑器中输入 `!` 然后按 `Tab` 键，可以自动生成基本 HTML 结构

## 三、常用 HTML 标签

### 3.1 标题（Heading）

`<h1>` 到 `<h6>` 共六级标题：

```html
<h1>Hello, this is main title</h1>
<h2>this is 2nd heading</h2>
<h3>this is 3rd heading</h3>
<h4>this is 4th heading</h4>
<h5>this is 5th heading</h5>
<h6>this is 6th heading</h6>
```

### 3.2 段落

`<p>`：一般内容，每一个代表独立段落

```html
<p>这是一个段落</p>
<p>这是另一个段落</p>
```

> [!NOTE]
> `<h1>` 到 `<h6>` 和 `<p>` 不管内容和字数有多少，都会占一整行，称为**区块元素**

### 3.3 行内元素

**粗体**：`<strong>`

```html
<strong>who are you</strong>
```

**斜体**：`<em>`

```html
<em>are you who</em>
```

### 3.4 链接

`<a>`：建立网页的超链接

```html
<p><a href="page.html">查看更多</a></p>
```

如果还没有外部链接，可以在 `href` 后面写 `#`：

```html
<a href="#">临时链接</a>
```

### 3.5 列表

**有序列表**（Ordered List）：

以 `<ol>` 开头，清单内容使用 `<li>` 标签，每组 `<li>` 都会显示为清单中的一个项目

```html
<ol>
    <li>项目 1</li>
    <li>项目 2</li>
    <li>项目 3</li>
</ol>
```

显示效果：
1. 项目 1
2. 项目 2
3. 项目 3

**无序列表**（Unordered List）：

使用 `<ul>` 可以制作没有数字的列表

```html
<ul>
    <li><a href="#">项目 1</a></li>
    <li>项目 2</li>
    <li>项目 3</li>
</ul>
```

显示效果：
- 项目 1
- 项目 2
- 项目 3

> [!TIP]
> 列表主要用于导览列、主选单等场景

### 3.6 引用

`<blockquote>` 可以引用别人的话：

```html
<blockquote cite="www.baidu.com">"上等的食材。。。"</blockquote>
```

### 3.7 换行

`<br>` 可以换行：

```html
hello hello <br>
你好<br>我是
```

### 3.8 图片

`<img>` 可以插入图片：

```html
<img src="path/to/image" alt="图片未正常显示时显示的内容">
```

### 3.9 语义化标签

| 标签 | 用途 |
|------|------|
| `<header>` | logo 等页首信息 |
| `<nav>` | 网站导览列、主选单 |
| `<main>` | 主题内容区域 |
| `<footer>` | 页尾、版权信息 |
| `<section>` | 内容分块 |
| `<div>` | 通用容器，用于划分模块 |

### 3.10 表单

```html
<form>
    <input type="email" placeholder="输入您的 Email" required>
    <button type="submit">提交</button>
</form>
```

## 四、CSS 样式设置

### 4.1 内联样式（不推荐）

直接写在 HTML 标签里：

```html
<h1 style="color:red">你好</h1>
```

> [!WARNING]
> 缺点：多个标签使用时耗时费力，不利于维护

### 4.2 内部样式表

统一写到 `<head>` 标签内：

```html
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        h2 {
            color: aqua;
        }
        p {
            font-size: x-large;
        }
    </style>
</head>
```

> [!WARNING]
> 缺点：对多个网页不方便，样式无法复用

### 4.3 外部样式表（推荐）

把 CSS 单独分离出来成为样式表文件：

**style.css**

```css
h2 {
    color: aqua;
}

p {
    font-size: x-large;
}
```

在 HTML 中链接：

```html
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="style.css">
</head>
```

## 五、常用 CSS 属性

### 5.1 边框（border）

```css
border: 边框粗细 颜色 样式;

header, section, footer {
    background-color: aqua;
    border: 5px blue solid;
}
```

边框样式：
- `solid`：实线
- `dashed`：虚线
- `dotted`：点线

### 5.2 内边距（padding）

控制内容与边框之间的空隙大小，按**上、右、下、左**的顺序设置：

```css
padding: 10px;              /* 四周都是 10px */
padding: 10px 20px;         /* 上下 10px，左右 20px */
padding: 10px 20px 30px;    /* 上 10px，左右 20px，下 30px */
padding: 10px 20px 30px 40px; /* 上 10px，右 20px，下 30px，左 40px */
```

### 5.3 外边距（margin）

控制不同网页元素之间的距离，用法同 `padding`

### 5.4 分组与类（class）

在标签内加上 `class` 属性：

```html
<section class="news"></section>
```

```css
.news {
    color: white;
    height: 95vh;
}
```

## 六、Flexbox 布局

Flexbox 是一种强大的布局方式：

```css
.news {
    color: white;
    height: 95vh;
    display: flex;
    justify-content: center;  /* 水平居中 */
    align-items: center;      /* 垂直居中 */
}
```

## 七、模块划分

使用 `<div>` 标签划分 HTML 模块，减少模块个数：

```html
<div class="info">
    <h2>hello</h2>
    <p>dwsdskasdasl</p>
</div>
```

## 八、固定定位

让导览列等元素固定不动：

```css
nav {
    position: fixed;
    top: 0;
    width: 100%;
}
```

## 九、响应式设计

使用媒体查询（Media Query）实现响应式布局：

```css
@media screen and (max-width: 480px) {
    body {
        background-color: lightgreen;
    }
}
```

通用语法：

```css
@media not|only mediatype and (expressions) {
    CSS 代码...;
}
```

## 十、总结

| 概念 | 说明 |
|------|------|
| HTML | 决定网页内容和结构 |
| CSS | 负责样式和布局 |
| 区块元素 | 占一整行，如 `<h1>`、`<p>` |
| 行内元素 | 只占所需宽度，如 `<strong>`、`<em>` |
| 外部样式表 | 推荐的 CSS 编写方式 |
| Flexbox | 现代布局方案 |
| 响应式设计 | 适配不同屏幕尺寸 |
