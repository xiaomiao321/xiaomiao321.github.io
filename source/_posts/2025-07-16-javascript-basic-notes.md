---
title: JavaScript 基础学习笔记
date: 2025-07-16 18:39:00 +0800
categories: [Learning, Language, JavaScript]
tags: [javascript, web, frontend]
description: JavaScript 基础语法学习笔记
toc: true
comments: true
---

JavaScript 用于做交互式网页，用 JavaScript 引擎运行。

把 `<script>` 标签放在 `<body>` 标签的末尾，在 `<body>` 中所有其他标签之后，因为浏览器解析是自顶向下的。

## 基本示例

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>hello</h1>
    <script>
        console.log('hello world')
    </script>
</body>
</html>
```

分成不同文件：

**index.js**

```javascript
console.log('hello world')
```

**index.html**

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <h1>hello</h1>
    <script src="index.js"></script>
</body>
</html>
```

## 变量

1. `var`：全局作用域，一般不用
2. `let`：值可以被修改
3. `const`：值无法被修改

## 输出

### 显示数据

- 使用 `window.alert()` 弹出警告框。
- 使用 `document.write()` 方法将内容写到 HTML 文档中。
- 使用 `innerHTML` 写入到 HTML 元素。
- 使用 `console.log()` 写入到浏览器的控制台

#### 使用 window.alert()

```javascript
window.alert("Hello World!");
```

#### 操作 HTML 元素

如需从 JavaScript 访问某个 HTML 元素，您可以使用 `document.getElementById(id)` 方法。

请使用 "id" 属性来标识 HTML 元素，并 `innerHTML` 来获取或插入元素内容：

```javascript
<!DOCTYPE html>
<html>
<body>
    <h1>我的第一个 Web 页面</h1>
    <p id="demo">我的第一个段落</p>
    <script>
        document.getElementById("demo").innerHTML = "段落已修改。";
    </script>
</body>
</html>
```
