---
title: TikZ 绘图学习笔记
date: 2025-07-14 15:25:00 +0800
categories: [Learning, Tools]
tags: [TikZ, LaTex]
description: TikZ 绘图基础学习笔记
toc: true
comments: true
math: true
---

## 基本环境

插入图片快捷键 BFI，在图片环境下：

```latex
\begin{figure}[htp]
    \centering
    \begin{tikzpicture}[>=latex]
        % 绘图命令
    \end{tikzpicture}
    \caption{}
\end{figure}
```

`[>=latex]` 是箭头样式，对于 `\begin{tikzpicture}` 到 `\end{tikzpicture}` 之间的所有箭头生效，还有一种是 `[>=stealth]`

## 基本命令

### 画直线

```latex
\draw (0,0)--(5,0); % 直线不带箭头
\draw[->] (0,0)--(5,0); % 带箭头
\draw[<-] (0,0)--(5,0); % 带箭头
\draw[<->] (0,0)--(5,0); % 带箭头
\draw[|<->|] (0,0)--(5,0); % 带箭头
\draw[dashed] (0,0)--(5,0); % 虚线
\draw[dotted] (0,0)--(5,0); % 点线
\draw[dashdotted] (0,0)--(5,0); % 点划线
\draw[dashed,thick,->] (0,0)--(5,0); % 选项可以组合，还有 very thick, ultra thick, thin 等
```

### 添加标识

```latex
\draw [dashed] (0,0)--node[above=3mm]{5cm}(5,0); % 在直线上方添加标识
\draw [dashed] (0,0)node[above=3mm]{5cm}--(5,0); % node 位置可以更改
\draw [dashed] (0,0)--node[fill=white]{5cm}(5,0); % 这样标识不会被直线遮挡
\draw [dashed] (0,0)--node[fill=red!20!white]{5cm}(5,0); % 20% 的红色，80% 的白色
```

> [!NOTE]
>
> 写 node 的位置是要放的对象之后

### 给点加标签

```latex
\node at (-0.2,-0.2){$O$}; % 给原点加标签
```

### 给坐标轴加刻度

```latex
\draw (1,0)node[below]{$1$}--(1,0.1);
\draw (0,1)node[left]{$1$}--(0.1,1);

\foreach \x in {1,2,...,6}
{
    \draw (0,\x)node[left]{$\x$}--(.1,\x);
}

\foreach \x in {1,2,...,6}
{
    \draw (0,\x*0.5)node[left]{$\x$}--(.1,\x*0.5);
    \draw (\x*0.5,0)node[below]{$\x$}--(\x*0.5,.1);
} % 更精细的刻度
```

### 绘制几何图形

```latex
% 绘制菱形并填充
\draw[fill=magenta] (-4,0)node[above]{$C$}--(0,3)node[right]{$B$}--(4,0)node[above]{$A$}--(0,-3)node[right]{$D$}--(-4,0);
\draw[->](-5,0)--(5,0)node[right]{$x$};
\draw[->](0,-5)--(0,5)node[right]{$y$};
\node at (-0.3,-0.3){$O$}; % 先画图再画坐标轴来防止遮挡
```

### 画矩形

```latex
\draw (0,0) rectangle (4,3); % (0,0) 和 (4,3) 是对角线两点
\draw[fill=cyan](0,0) rectangle (4,3); % 这样会有黑色边框
\fill [cyan] (0,-5) rectangle (4,-2); % 这样没有边框
\fill [cyan,draw=black] (0,-5) rectangle (4,-2); % 可以设置边框颜色
```

### 使用极坐标

$(\theta:r)$，$\theta$ 是角度制下的角度，r 是与原点的距离

```latex
\draw (0,0)--(45:4);
```

### 画圆形和圆弧

```latex
\fill [cyan] (0,0) circle (1.5); % (0,0) 是圆心，1.5 是半径
\draw[->] (2,0) arc (0:45:2); % (2,0) 是起点，0 是起始角度，45 是终止角度，2 是半径
```

### 打阴影

```latex
% 引言部分
\usetikzlibrary{patterns}
\draw[pattern=north east lines](8,8) rectangle (10,10);
```

### 画函数图像

```latex
\draw [domain=-4:4, samples=1000, thick] % 定义域，取点的个数
    plot(\x, {0.5*\x*\x}); % y 要加大括号
    \node at (4.5,6){$y=\frac{1}{2}x^2$};
```

### 画三角函数图像

```latex
\draw[domain=-pi/6:13*pi/6,samples=1000,dashed]
plot(\x,{sin(\x r)}); % 加一个 r 是改成弧度制
```

### 画框图

```latex
\node (s1) at (0,0)[rectangle,draw=blue!50,fill=blue!20]{均方收敛};
% rectangle 可以改成 circle
\node (s2) at (4,0)[rectangle,draw=blue!50,fill=blue!20]{以概率 1 收敛};
\node (s3) at (2,-2)[rectangle,draw=blue!50,fill=blue!20]{依概率收敛};
\node (s4) at (2,-4)[rectangle,draw=blue!50,fill=blue!20]{依分布收敛};
\draw[->](s1)--(s3);
\draw[->](s2)--(s3);
\draw[->](s3)--(s4);
```

### 在循环中创建节点

```latex
\foreach \x/\xtext in {0/0,1/1,2/2,3/\cdots,4/s,5/\cdots}
{
    \node (s\x) at (\x,0) {$\xtext$};
}
```

### 画弯曲的箭头

```latex
\draw[->](s0)to [bend left=25] node[above]{$\lambda$}(s1); % 25 是角度，可正可负
```

## circuitikz 画电路图

与 tikz 一样，使用 circuitikz 也要先输入 bfi 来快捷创建图片环境，然后在图片环境中 `\begin{circuitikz}`

```latex
\begin{circuitikz}[european]
    \draw (0,4) to [battery2] (0,0)--(3,0) to [cute open switch] (3,2) to [R=$R$](3,4)--(0,4); % 起点 to [元件] 终点
    % t=mV 表示电表上的字；*-*表示给导线的连接点加黑点
    \draw (1.5,0) to [rmeter,t=mV,*-*](1.5,4);
\end{circuitikz}
```

## 缩放

```latex
\begin{tikzpicture}[>=latex,scale=0.5] % scale=0.5 可以缩小整个图，但是文字不会缩放
    % 绘图命令
\end{tikzpicture}
```
