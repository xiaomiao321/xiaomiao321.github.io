---
title: 韦东山STM32HAL库笔记
date: 2025-10-08 21:55:00
categories: [Learning, Embedded, Platform, STM32]
tags: [HAL, embedded, STM32]
description: 韦东山STM32HAL库笔记，包括GPIO、UART、I2C、SPI、TIM等外设
---

## C语言补充

### 字节序

假设“int a = 0x12345678;”， 16 进制数中每位数值占据 4 bit；在内存中，是以 8个 bit 作为 1byte。因此 0x12345678 中每两位作为 1byte, 其中 0x78 是低 byte， 0x12 是高 byte。 

在内存中的存储方式有两种  

 ![字节序](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%AD%97%E8%8A%82%E5%BA%8F.png)

第一种，低位存在低地址，叫做小字节序(Little endian)；第二种，高位存在低地址，叫做大字节序(Big endian)

一般的 arm 芯片都是小字节序，有些处理器，可以置某个寄存器，让整个系统使用大字节序或小字节序  

用C语言判断字节序

```cpp
#include <stdint.h>
#include <stdio.h>

int main() {
  uint32_t a = 0x12345678;
  uint8_t *p = (uint8_t *)&a;
  printf("%x", *p);
  return 0;
}
```

### 位操作

- 移位
- 取反
- 按位与
- 按位或

```cpp
int a = 0x123;
/*把bit7,bit8设置为1*/
int b = (a | (1<<7)) | (1<<8)
```

```cpp
int a = 0x123;
/*把bit7,bit8设置为0*/
int b = (a & ~(1<<7)) & ~(1<<8)
```

## GPIO的工作模式

一组GPIO有0-15共16个引脚，组数取决于管脚数

对于某个GPIO

![GPIO框图](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO%E6%A1%86%E5%9B%BE.png)

### 输入模式

输入模式有四种：上拉输入、下拉输入、浮空输入、模拟输入  

![悬空输入](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E6%82%AC%E7%A9%BA%E8%BE%93%E5%85%A5.png)

上图的 2 个按键 K1、 K2，它不被按下时，电平是多少？
答案是：不知道！ PIN1、 PIN2 就像一个悬空的电线，它跟参考点“GND”没有电气连接，无法确定 PIN1、 PIN2 的电平是多少。
正确的电路如下（PIN1 增加下拉电阻、 PIN2 增加上拉电阻）：  

![上下拉](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%8A%E4%B8%8B%E6%8B%89.png)

上下拉电阻芯片内部有，可以被使能，也可以不用(浮空输入，用于ADC)

![触发器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E8%A7%A6%E5%8F%91%E5%99%A8.png)

TTL触发器：保证寄存器稳定，越过绿线/红线的时候才会变

### 输出模式

![输出框图](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E8%BE%93%E5%87%BA%E6%A1%86%E5%9B%BE.png)

输出模式有四种：
推挽输出、开漏输出、复用推挽输出、复用开漏输出。  

开漏：

![开漏](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%BC%80%E6%BC%8F.png)

如果两个芯片都是推挽输出，一个输出0，一个输出1，则$V_{DD}$和$V_{SS}$会短接，导致烧毁

而开漏的时候，芯片想输出高电平的时候，P-MOS不起作用，相当于在内部是悬空的

![推挽2](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E6%8E%A8%E6%8C%BD2.png)

对方如果接地就也接地，而如果对方也是开漏输出高电平，那么二者都悬空，可以外部上拉到高电平

![开漏2](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%BC%80%E6%BC%8F2.png)

可以实现双向通信

IC1想发数据，先输出1，表明该GPIO由外部决定，再读引脚，如果是0，表明IC2驱动了这个引脚，如果是1，表明IC2没驱动这个引脚，IC1就可以驱动这个引脚，可用于IIC

### 操作GPIO

1. 设置方向
2. 设置模式
    1. 输入：上、下拉
    2. 输出：推挽、开漏
3. 读值或者写值
4. 设置速率

![GPIO寄存器1](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO%E5%AF%84%E5%AD%98%E5%99%A81.png)

![GPIO寄存器2](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO%E5%AF%84%E5%AD%98%E5%99%A82.png)



分别设置每个引脚的CNF和MODE寄存器。速率高的时候对外界电磁干扰比较大

![GPIO寄存器3](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO%E5%AF%84%E5%AD%98%E5%99%A83.png)

每一位对应一个GPIO引脚

### GPIO HAL源码

![GPIO_HAL](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO_HAL.png)

`HAL_GPIO_Init`

![GPIO源码1](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO%E6%BA%90%E7%A0%811.png)

![GPIO源码2](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedGPIO%E6%BA%90%E7%A0%812.png)

### 示例

#### 使用CubeMX

```cpp
  while (1) {
    GPIO_PinState status = GPIO_PIN_SET;
    status = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);

    if (status == GPIO_PIN_RESET) /*按下了*/
    {
      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
```

#### 手动配置

```cpp
  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
```

## 光敏电阻&蜂鸣器

### 光敏电阻

![光敏电阻](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%85%89%E6%95%8F%E7%94%B5%E9%98%BB.png)

LM393 是比较器，它的“+”极接到光敏电阻，“-”极接到可调电阻。当“+”极的电压大于“-”极的电压， DO 输出高电平， LED 被熄灭；当“+”极的电压小于“-”极的电压，DO 输出低电平， LED 被点亮。
调整可调电阻，就是调整“+”极的电压，也就是调整光敏电阻分压电路的比较电压。
当光照比较强烈时，光敏电阻阻值下降，“+”极电压下降低于“-”极电压时， DO 输出低电平， LED 被点亮。
当光照比较强烈时，光敏电阻阻值上升，“+”极电压上升大于“-”极电压时， DO 输出高电平， LED 被熄灭。

### 代码

```  c
static int isDark(void) {
  return (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_SET);
}
static void Beep(int on) {
  if (on) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
  }
}
static void LEDControl(int on) {
  if (on) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  }
}
int main()
{
      while (1) {
    /* USER CODE END WHILE */
    if (isDark()) {
      Beep(1);
      LEDControl(1);
    } else {
      Beep(0);
      LEDControl(0);
    }
}
```

## GPIO中断

### 中断概念的引入

![中断](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD.png)

平时高电平，被按下低电平

```cpp
void main()
{
    pre_val = 1;
    val = 0;
    while(1)
    {
        val = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
        if(val!=pre_val)
        {
            if(val == 0)
            {
                printf("按下")
			}
            else
            {
                printf("松开")
            }
            pre_val = val;
        }
        /*...某些耗时操作...*/
	}
}
```

执行那些耗时操作的时候，无法读取按键状态，可能会丢失按键操作

### 中断示例

你在看书，门铃响了：这就是一个中断。你会插入书签（保存现场），开门取快递（处理中断），回来从书签位置处继续看书（恢复现场）。  

有中断函数`pin_isr()`，ISR=Interrupt Service Routine

```cpp
char buf[10]={0};
char cnt = 0;
void pin_isr()/*边沿触发*/
{
    buf[cnt++] = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
}
int main()
{
    while(1)
    {
        /*读buf*/
    }
}
```

![CPU异常](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedCPU%E5%BC%82%E5%B8%B8.png)

CPU 在运行的过程中，也会被各种“异常”打断。这些“异常”有：
① 指令未定义
② 指令、数据访问有问题
③ SWI(软中断)
④ 中断
中断也属于一种“异常”，导致中断发生的情况有很多，比如：
① 按键
② 定时器
③ ADC 转换完成
④ UART 发送完数据、收到数据等等
这些众多的“中断源”，汇集到“中断控制器”，由“中断控制器”选择优先级最高的中断并通知 CPU。

CPU收到中断/异常信号后会跳到某个地址去执行对应的指令(提供的函数)  

### 中断处理流程

arm 芯片对异常(中断)处理过程：
① 初始化：
设置中断源，让它可以产生中断
设置中断控制器(可以屏蔽某个中断，优先级)
设置 CPU 总开关(使能中断)
② 然后就可以执行其他程序了，比如 main 函数
③ 产生中断：比如按下按键--->中断控制器--->CPU
④ CPU 每执行完一条指令都会检查有无中断/异常产生
⑤ CPU 发现有中断/异常产生，开始处理。
⑥ 发生中断后， 对于不同的异常，跳去不同的地址执行程序。
这地址上，只是一条跳转指令，跳去执行某个函数(地址)，这个就是异常向量。 ③④⑤都是硬件做的。
这些函数做什么事情？
① 保存现场(保存被中断瞬间的各个寄存器的值)
② 处理异常(中断):分辨中断源， 再调用不同的处理函数
③ 恢复现场（就是从被中断的地方继续运行）  

![中断流程](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E6%B5%81%E7%A8%8B.png)

### STM32中断体系结构

![中断结构](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E7%BB%93%E6%9E%84.png)

EXIT： External interrupt/event controller，外部中断/事件控制器。
NVIC： Nested vectored interrupt controller， 嵌套向量中断控制器，识别ID并发给CPU，使用ID在NVIC的向量表里面找到对应函数  

![中断框图](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E6%A1%86%E5%9B%BE.png)

#### 配置GPIO来源



PA0~PG0 这多个 0 号引脚中，只能有一个连接到 EXTI0，即它们中同一时间只能有一个被用作中断引脚， 可以在 AFIO_EXTICR1 寄存器中选择某个引脚。  

![EXTI0](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedEXTI0.png)

![中断寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E5%AF%84%E5%AD%98%E5%99%A8.png)

可以配置EXTI0-15的外部中断源对应的哪组GPIO，同一时刻同一个EXTI只能有一组GPIO发出中断

#### 配置EXTI

对外部中断进行更详细的配置  

EXTI一共19条线路，16个GPIO的，3个内部的

EXTI框图：

![EXTI](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedEXTI.png)

在 EXTI 内部，可以配置 EXTI0 的中断触发方式（上升沿触发、下
降沿触发）、使能（是否允许 EXTI0 传输到 NVIC）、读取它的当前状态（是否有待处理的中断）  

寄存器如下：  

![EXTI_Reg](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedEXTI_Reg.png)

##### 屏蔽/使能寄存器

![中断使能寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E4%BD%BF%E8%83%BD%E5%AF%84%E5%AD%98%E5%99%A8.png)

每一位对应一个外部中断，控制能否发给下一级的NVIC

##### 边沿触发寄存器

![边沿寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E8%BE%B9%E6%B2%BF%E5%AF%84%E5%AD%98%E5%99%A8.png)

每一位对应一个外部中断，控制能否上升/下降沿触发

##### 软件触发寄存器

![软件触发寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E8%BD%AF%E4%BB%B6%E8%A7%A6%E5%8F%91%E5%AF%84%E5%AD%98%E5%99%A8.png)

##### 中断待处理寄存器

![待处理寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E5%BE%85%E5%A4%84%E7%90%86%E5%AF%84%E5%AD%98%E5%99%A8.png)

#### 配置NVIC

管理多个中断源（使能、优先级），提供“异常向量表”在 NVIC 里，每一个异常、中断，都有一个编号：  

![中断向量表](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E5%90%91%E9%87%8F%E8%A1%A8.png)

对于这些中断，都可以单独设置：
① 使能/屏蔽：是否允许它传输到 CPU
② 优先级  

当各类中断进入 NVIC 后， NVIC 里还有开关：这些中断能否发给 CPU？
假设有些中断是同时发生的， 哪一个能优先传给 CPU？在 NVIC 里，可以设置中断优先级、 中断向量表（当发生中断时，去这个表里找到、调用对应的处理函数）。
NVIC 里使能中断的寄存器如下（优先级相关寄存器看后面）

![NVIC寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedNVIC%E5%AF%84%E5%AD%98%E5%99%A8.png)

#### 配置CPU

CPU： CPU内部也有一个开关，是否使能CPU处理中断。
CPU 内部，有一个“PRIMASK”寄存器，“Priority mask”， 往它写入 1 可以禁止所有中断；往它写入 0，可以使能中断。 代码如下：  

![CPU配置中断](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedCPU%E9%85%8D%E7%BD%AE%E4%B8%AD%E6%96%AD.png)

当各部件都设置、使能好了之后，某个中断发生了，比如 PA0 的电平从高变低了，就会触发中断。 CPU 接收到中断后，就会跳转到 NVIC 中设置的“异常向量表”，根据 EXTI0 的 ID 找到表里对应的函数，执行它。  

#### 异常向量表

在`startup_stm32f103xe.s`，可以看到如下代码  

```assembly
__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler            ; Window Watchdog
                DCD     PVD_IRQHandler             ; PVD through EXTI Line detect
                DCD     TAMPER_IRQHandler          ; Tamper
                DCD     RTC_IRQHandler             ; RTC
                DCD     FLASH_IRQHandler           ; Flash
                DCD     RCC_IRQHandler             ; RCC
                DCD     EXTI0_IRQHandler           ; EXTI Line 0
                DCD     EXTI1_IRQHandler           ; EXTI Line 1
                DCD     EXTI2_IRQHandler           ; EXTI Line 2
                DCD     EXTI3_IRQHandler           ; EXTI Line 3
                DCD     EXTI4_IRQHandler           ; EXTI Line 4
                DCD     DMA1_Channel1_IRQHandler   ; DMA1 Channel 1
                DCD     DMA1_Channel2_IRQHandler   ; DMA1 Channel 2
                DCD     DMA1_Channel3_IRQHandler   ; DMA1 Channel 3
                DCD     DMA1_Channel4_IRQHandler   ; DMA1 Channel 4
                DCD     DMA1_Channel5_IRQHandler   ; DMA1 Channel 5
                DCD     DMA1_Channel6_IRQHandler   ; DMA1 Channel 6
                DCD     DMA1_Channel7_IRQHandler   ; DMA1 Channel 7
                DCD     ADC1_2_IRQHandler          ; ADC1_2
                DCD     USB_HP_CAN1_TX_IRQHandler  ; USB High Priority or CAN1 TX
                DCD     USB_LP_CAN1_RX0_IRQHandler ; USB Low  Priority or CAN1 RX0
                DCD     CAN1_RX1_IRQHandler        ; CAN1 RX1
                DCD     CAN1_SCE_IRQHandler        ; CAN1 SCE
                DCD     EXTI9_5_IRQHandler         ; EXTI Line 9..5
                DCD     TIM1_BRK_IRQHandler        ; TIM1 Break
                DCD     TIM1_UP_IRQHandler         ; TIM1 Update
                DCD     TIM1_TRG_COM_IRQHandler    ; TIM1 Trigger and Commutation
                DCD     TIM1_CC_IRQHandler         ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler            ; TIM2
                DCD     TIM3_IRQHandler            ; TIM3
                DCD     TIM4_IRQHandler            ; TIM4
                DCD     I2C1_EV_IRQHandler         ; I2C1 Event
                DCD     I2C1_ER_IRQHandler         ; I2C1 Error
                DCD     I2C2_EV_IRQHandler         ; I2C2 Event
                DCD     I2C2_ER_IRQHandler         ; I2C2 Error
                DCD     SPI1_IRQHandler            ; SPI1
                DCD     SPI2_IRQHandler            ; SPI2
                DCD     USART1_IRQHandler          ; USART1
                DCD     USART2_IRQHandler          ; USART2
                DCD     USART3_IRQHandler          ; USART3
                DCD     EXTI15_10_IRQHandler       ; EXTI Line 15..10
                DCD     RTC_Alarm_IRQHandler        ; RTC Alarm through EXTI Line
                DCD     USBWakeUp_IRQHandler       ; USB Wakeup from suspend
__Vectors_End
```

#### 中断优先级

 在 NVIC 里，对于每一个中断， 都有一个 8 位的寄存器被用来表示它的优先级。这个 8位的寄存器，被分为 2 部分，分别表示： 分组优先级（也叫抢占优先级）、 子优先级  

![中断优先级寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E4%BC%98%E5%85%88%E7%BA%A7%E5%AF%84%E5%AD%98%E5%99%A8.png)

分组优先级被用来判断：当前正在处理的中断，能否被打断。比如当前正在处理 EXT0中断，它的分组优先级为 3；如果这时候发生了 EXT1 中断，它的分组优先级为 4（数值越高，优先级越低），那么 EXT1 的中断就无法打断 EXT0，等 EXT0 的中断处理完毕， EXT1 的中断才能被处理。 但是，如果 EXT1 的分组优先级为 2，那么当前的 EXT0 中断就被“抢占”，先执行 EXT1 的中断处理函数，再继续执行“被抢占的 EXT0”中断函数。

子优先级被用来判断：两个中断同时发生时，谁先被处理。还是以 EXT0、 EXT1 为例，如果它们同时发生了，那么分组优先级高的中断先被处理；如果分组优先级相同，那么子优先级高的先被处理；如果连子优先级也相同，那么编号小的 EXT0 先被处理。注意：如果 EXT0、 EXT1 的分组优先级相同，是不会发生“抢占”的。比如 EXT0 中断正在被处理， EXT1 紧接着被触发了，即使 EXT1 的子优先级高于 EXT0， EXT1 也不会抢占EXI0。当 EXT0 被处理完毕，才轮到 EXT1 被处理  

那么，在每个中断的 8 位优先级状态寄存器里，有 2 个问题：
① 这 8 位都实现了吗？
不一定，比如 STM32F103 系列芯片里只实现了 4 位。实现越多位数，硬件设计越复杂，
功耗越高。实现多少位，这是由芯片公司决定的。
② 这 8 位里，哪几位表示分组优先级（剩下的就表示子优先级）？
这是可配置的， NVIC 内部有一个“优先级分组的配置寄存器”，通过它可以设置所有
、中断的“8 位优先级寄存器里，哪几位表示分组优先级”。如下图所示：  

![中断优先级定义](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E4%BC%98%E5%85%88%E7%BA%A7%E5%AE%9A%E4%B9%89.png)



> [!NOTE]
>
> 抢占优先级相同的中断不会抢占对方

### GPIO中断编程

#### CubeMX配置

GPIO设成GPIO_EXTI14——GPIO Mode可以选中断触发方式，在NVIC勾选对应的中断的Enabled，然后可以在NVIC栏配置优先级

#### 代码

```cpp
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  /* EXTI line interrupt detected */
  if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != 0x00u)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    HAL_GPIO_EXTI_Callback(GPIO_Pin);
  }
}
__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}

```

重新定义回调函数即可

```cpp
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_14) {
    /*分辨是上升还是下降沿*/
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) {
      /*按下，点亮LED*/
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    } else {
      /*松开，熄灭LED*/
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    }
  }
}
```

#### 代码解读

##### 设置 GPIO 和 EXTI  

```cpp
  /*Configure GPIO pin : PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);/*同时涉及了GPIO模块和EXTI*/
```

```cpp
#define  GPIO_MODE_IT_RISING                    0x10110000u   /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  GPIO_MODE_IT_FALLING                   0x10210000u   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  GPIO_MODE_IT_RISING_FALLING            0x10310000u   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */

#define  GPIO_MODE_EVT_RISING                   0x10120000u   /*!< External Event Mode with Rising edge trigger detection               */
#define  GPIO_MODE_EVT_FALLING                  0x10220000u   /*!< External Event Mode with Falling edge trigger detection              */
#define  GPIO_MODE_EVT_RISING_FALLING           0x10320000u   /*!< External Event Mode with Rising/Falling edge trigger detection       */
```

`HAL_GPIO_Init()`

```cpp
/*--------------------- EXTI Mode Configuration ------------------------*/
/* Configure the External Interrupt or event for the current IO */
if ((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
{
    /* Enable AFIO Clock */
    __HAL_RCC_AFIO_CLK_ENABLE();
    temp = AFIO->EXTICR[position >> 2u];
    CLEAR_BIT(temp, (0x0Fu) << (4u * (position & 0x03u)));
    SET_BIT(temp, (GPIO_GET_INDEX(GPIOx)) << (4u * (position & 0x03u)));
    AFIO->EXTICR[position >> 2u] = temp;


    /* Enable or disable the rising trigger */
    if ((GPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
    {
      SET_BIT(EXTI->RTSR, iocurrent);
    }
    else
    {
      CLEAR_BIT(EXTI->RTSR, iocurrent);
    }

    /* Enable or disable the falling trigger */
    if ((GPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
    {
      SET_BIT(EXTI->FTSR, iocurrent);
    }
    else
    {
      CLEAR_BIT(EXTI->FTSR, iocurrent);
    }

    /* Configure the event mask */
    if ((GPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
    {
      SET_BIT(EXTI->EMR, iocurrent);
    }
    else
    {
      CLEAR_BIT(EXTI->EMR, iocurrent);
    }

    /* Configure the interrupt mask */
    if ((GPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
    {
      SET_BIT(EXTI->IMR, iocurrent);
    }
    else
    {
      CLEAR_BIT(EXTI->IMR, iocurrent);
    }
}
```

至此，EXTI能把中断信号发给NVIC

##### 中断(IT)和事件(EVT)的区别

中断到达CPU，事件到达其他模块(如ADC)，可以用硬件模块通过事件驱动其他模块

##### 设置NVIC

要做3个事

1. 设置优先级
2. 使能中断
3. 把向量表告诉NVIC

```cpp
HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
```

这里没设置向量表，使用的默认的汇编文件的向量表

## OLED调试

### 初始化

`HAL_I2C_Init`会先调用`HAL_I2C_MspInit`

```cpp
void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}
```

### 添加驱动程序

去`D:\files\25-26Autumn\weidongshan\HAL\my_programme\OLED_Driver`复制，但是不能添加到项目的`\Drivers\OLED_Driver`

> [!WARNING]
>
> 使用CubeMX的时候一定要选中`Copy only the necessary files`，否则构建会出问题

### 函数

OLED 的分辨率是 128X64， 要显示 8X16 点阵字符时，每行最多可以显示 16 个字符，所以下面罗列的函数里， X 坐标的取值为 0~15。最多同时能显示 4 行字符，按理说 Y 坐标取值应该为 0~3，但是为了更细致地调整字符的 Y 坐标，我们把 Y 坐标的取值范围设定为 0~7。下图里，分别在坐标（0， 0）、（0,1）位置显示了字符“A”；在坐标（0,2）、（0,3）显示了字符“B”；在坐标（0,4）、（0,5）显示了字符“C”；在坐标（0,6）显示了字符“D”  

![OLED](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedOLED.png)

## 按键驱动程序改进

![抖动](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E6%8A%96%E5%8A%A8.png)

按下或松开一个按键，它的 GPIO 电平会反复变化，最后才稳定。一般是 5~10 毫秒才会稳定。
如果不处理抖动的话，用户只操作一次按键，中断程序可能会上报多个数据。怎么处理？  

① 在按键中断程序中，可以循环判断几十亳秒，发现电平稳定之后再上报
② 使用定时器
显然第 1 种方法太耗时，违背“中断要尽快处理”的原则，你的系统会很卡。怎么使
用定时器？看下图：  

![中断定时器](.\img\中断定时器.png)

在 GPIO 中断中并不立刻记录按键值，而是修改定时器超时时间， 10ms 后再处理。如果 10ms 内又发生了 GPIO 中断，那就认为是抖动，这时再次修改超时时间为10ms。
只有 10ms 之内再无 GPIO 中断发生，那么定时器的函数才会被调用。在定时器函数中
记录按键值。  

### 验证按键抖动:

```cpp
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_14) {
    g_key_cnt++;
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
  }
}

  OLED_Init();
  OLED_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */
    OLED_PrintString(0, 0, "KEY ISR cnt = ");
    OLED_PrintSignedVal(0, 2, g_key_cnt);
    /* USER CODE BEGIN 3 */
  }
```

### 定时器消除抖动

![中断定时器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E4%B8%AD%E6%96%AD%E5%AE%9A%E6%97%B6%E5%99%A8.png)

SysTick—系统定时器是属于CM4内核中的一个外设，内嵌在NVIC中。系统定时器是一个24bit的向下递减的计数器， 计数器每计数一次的时间为1/SYSCLK，一般我们设置系统时钟SYSCLK等于180M。当重装载数值寄存器的值递减到0的时候，系统定时器就产生一次中断，以此循环往复。

因为SysTick是属于CM4内核的外设，所以所有基于CM4内核的单片机都具有这个系统定时器，使得软件在CM4单片机中可以很容易的移植。 系统定时器一般用于操作系统，用于产生时基，维持操作系统的心跳。

`SysTick_Handler`是系统滴答定时器中断处理函数，默认1ms触发一次中断，这个中断处理函数会增加计数值，计数值可通过`HAL_GetTick`获得

可以自己实现一个定时器，在这个函数里面判断定时器是否超时`check_timer()`，然后在外部中断推迟定时器10ms`mod_timer(10)`

```cpp
typedef struct soft_timer {
  uint32_t timeout;
  void *arg; /*给函数的参数*/
  void (*func)(void *);
} myTimer;
myTimer key_timer = {
    ~0, /*超时时间初始化为一个很大的数*/
    NULL,
    key_timeout_func
};
void key_timeout_func(void *arg) {
  g_key_cnt++;
  key_timer.timeout = ~0;/*这里如果不设置每1毫秒都会增加*/
}
```

```cpp
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
  if (GPIO_Pin == GPIO_PIN_14) {
    g_key_cnt++;
    mod_timer(&key_timer, 10);
  }
}
void mod_timer(myTimer *pTimer, uint32_t time_offset) {
  pTimer->timeout = HAL_GetTick() + time_offset;
}
```

```cpp
void SysTick_Handler(void) {
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  extern void check_timer(void);
  check_timer();
  /* USER CODE END SysTick_IRQn 1 */
}
void check_timer(myTimer *pTimer) {
  if (pTimer->timeout <= HAL_GetTick()) {
    pTimer->func(pTimer->arg);
  }
}
```

### 环形缓冲区

即使使用中断函数或者定时器函数记录按键，如果只能记录一个键值的话，如果不能及时读走出来，再次发生中断时新值就会覆盖旧值。要解决数据被覆盖的问题，可以使用一个稍微大点的缓冲区，这就涉及数据的写入、读出，可以使用环形缓冲区。  



环形缓冲区特别适合这种场景：

一方写 buffer，另一方读 buffer。  环形缓冲区实际上还是一维数组，假设有 N 个数组项，从第 0 个数组项开始遍历，访问完第 N-1 个数组项后，再从 0 开始——这就是“环形”的含义，  

![环形](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E7%8E%AF%E5%BD%A2.png)

```cpp
int buf[8];
int r = 0;
int w = 0;/*r,w分别表示下次读、写的位置*/
```

`r == w`表明缓冲区空

`下一个w位置==r`表明缓冲区满

```cpp
int next_w = w + 1;
if(next_w == 8)
{
    next_w = 0;
}
```



写数据：

```cpp
if(未满)/*if(next_w != r)*/
{
    buf[w] = val;
    w++;
    if(w == 8) w = 0;
}
```

读数据：

```cpp
if(r != w)/*表明有数据*/
{
    val = buf[r];
    r++;
    if(r == 8)
    {
        r = 0;
	}
}
```

```cpp
#include <circle_buffer.h>
void circle_buf_init(circle_buf *pCircleBuf, uint32_t len, uint8_t *buf) {
  pCircleBuf->r = 0;
  pCircleBuf->w = 0;
  pCircleBuf->len = len;
  pCircleBuf->buf = buf;
}

int circle_buf_read(circle_buf *pCircleBuf, uint8_t *pVal) {
  if (pCircleBuf->r != pCircleBuf->w) /*缓冲区非空*/
  {
    *pVal = pCircleBuf->buf[pCircleBuf->r];
    pCircleBuf->r++;
    if (pCircleBuf->r == pCircleBuf->len) {
      pCircleBuf->r = 0;
    }
    return 0;
  } else {
    return -1;
  }
}

int circle_buf_write(circle_buf *pCircleBuf, uint8_t val) {
  uint32_t next_w;

  next_w = pCircleBuf->w + 1;
  if (next_w == pCircleBuf->len) {
    next_w = 0;
  }
  if (next_w != pCircleBuf->r) /*没满*/
  {
    pCircleBuf->buf[pCircleBuf->w] = val;
    pCircleBuf->w = next_w;
    return 0;
  } else {
    return -1;
  }
}
```

修改`key_timeout_func`

```cpp
void key_timeout_func(void *arg) {
  uint8_t key_val = 0; /*按下是0x1，松开是0x81*/
  g_key_cnt++;
  key_timer.timeout = ~0;

  /*读GPIO*/
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) /*按下触发的中断*/
  {
    key_val = 0x01;
  } else {
    key_val = 0x81;
  }
  /*把按键值放入缓冲区*/
  circle_buf_write(&g_key_buf, key_val);
}
```

main函数

```cpp
  while (1) {
    /* USER CODE END WHILE */
    int len = 0;
    OLED_PrintString(0, 0, "KEY ISR cnt = ");
    len = OLED_PrintString(0, 2, "Keyval:");
    OLED_PrintSignedVal(0, 2, g_key_cnt);
    uint8_t key_val = 0;
    if (circle_buf_read(&g_key_buf, &key_val) == 0) /*成功读取*/
    {
      OLED_ClearLine(len, 2);
      OLED_PrintHex(len, 2, key_val, 1);
    }

    /* USER CODE BEGIN 3 */
  }
```



## UART硬件结构

![UART框图](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedUART%E6%A1%86%E5%9B%BE.png)

设置：波特率、数据位

发送：

```cpp
unsigned int *p = TDR的地址;/*TDR=Transmit Data Register*/
*p = 0x78;
```

0x78被写入TDR寄存器，会自动被移动到移位寄存器(Transmit Shift Register)，移位寄存器会自动一位一位地发送数据

什么时候能写下一个数据？等到0x78被移动到移位寄存器

有状态寄存器

![UART寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedUART%E5%AF%84%E5%AD%98%E5%99%A8.png)

TXE=1表明TDR寄存器空，数据被转到了移位寄存器，TC=1表明已经发送完毕。二者都由硬件设置

读数据

```cpp
unsigned int *p = RDR地址;
val = *p;
```

分辨状态：RXNE=1表明非空

上面的办法都是查询模式，还可以用中断

设置中断

![UART设置寄存器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedUART%E8%AE%BE%E7%BD%AE%E5%AF%84%E5%AD%98%E5%99%A8.png)

![UART设置寄存器2](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedUART%E8%AE%BE%E7%BD%AE%E5%AF%84%E5%AD%98%E5%99%A82.png)

一般用TXEIE(发送寄存器空中断)和RXNEIE(接收寄存器非空中断)

## UART 查询方式(polling mode)

要发送数据时，先把数据写入 TDR 寄存器，然后判断 TDR 为空再返回。当然也可以先判断 TDR 为空，再写入。
要读取数据时，先判断 RDR 非空，再读取 RDR 得到数据。  

### CubeMX配置

Connectivity-USART1——使能——异步，其他默认即可

### 代码

```cpp
  char *tx_buffer = "Hello,world!";
  char c;
  HAL_UART_Transmit(&huart1, tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    while (HAL_UART_Receive(&huart1, &c, 1, HAL_MAX_DELAY) != HAL_OK)
      ; /*等到收到数据*/
    c += 1;
    HAL_UART_Transmit(&huart1, &c, 1, HAL_MAX_DELAY);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

```

### `HAL_UART_Transmit()`

```cpp
    while (huart->TxXferCount > 0U)
    {
      if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_TXE, RESET, tickstart, Timeout) != HAL_OK)/*等待发送寄存器空标志位=1*/
      {
        huart->gState = HAL_UART_STATE_READY;

        return HAL_TIMEOUT;
      }
      if (pdata8bits == NULL)
      {
        huart->Instance->DR = (uint16_t)(*pdata16bits & 0x01FFU);
        pdata16bits++;
      }
      else
      {
        huart->Instance->DR = (uint8_t)(*pdata8bits & 0xFFU);
        pdata8bits++;
      }
      huart->TxXferCount--;
    }
```

### `HAL_UART_Receive`

```cpp
    while (huart->RxXferCount > 0U)
    {
      if (UART_WaitOnFlagUntilTimeout(huart, UART_FLAG_RXNE, RESET, tickstart, Timeout) != HAL_OK)
      {
        huart->RxState = HAL_UART_STATE_READY;

        return HAL_TIMEOUT;
      }
      if (pdata8bits == NULL)
      {
        *pdata16bits = (uint16_t)(huart->Instance->DR & 0x01FF);
        pdata16bits++;
      }
      else
      {
        if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
        {
          *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
        }
        else
        {
          *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);
        }
        pdata8bits++;
      }
      huart->RxXferCount--;
    }
```



缺点：数据容易丢失，因为`HAL_UART_Transmit`打印消耗时间，接收数据寄存器数据无法被及时读走，导致被之后的数据覆盖

## UART中断方式

使用中断方式，效率更高，并且可以在接收数据时避免数据丢失。
要发送数据时，使能“TXE”中断（发送寄存器空中断）。在 TXE 中断处理函数里，从程序的发送 buffer 里取出一个数据，写入 TDR。等再次发生 TXE 中断时，再从程序的发送buffer 里取出下一个数据写入 TDR。
对于接收数据，在一开始就使能“RXNE”中断（接收寄存器非空）。这样， UART 接收到一个数据就会触发中断，在中断程序里读取 RDR 得到数据，存入程序的接收 buffer。当程序向读取串口数据时，它直接读取接收 buffer 即可。
这里涉及的“发送 buffer”、“接收 buffer”，特别适合使用“环形 buffer”。  

在CubeMX使能串口中断

### 发送

发送数据先调用`HAL_UART_Transmit_IT`，这个函数只会使能TX完成中断

```cpp
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
  /* Check that a Tx process is not already ongoing */
  if (huart->gState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    /* Enable the UART Transmit data register empty Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_TXE);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
```

发送完一个字节，会触发一次TXE中断，调用`HAL_UART_IRQHandler`，进而调用`UART_Transmit_IT`

```cpp
static HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart)
{
  const uint16_t *tmp;

  /* Check that a Tx process is ongoing */
    /*不是最后一个数据*/
  if (huart->gState == HAL_UART_STATE_BUSY_TX)
  {
    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      tmp = (const uint16_t *) huart->pTxBuffPtr;
      huart->Instance->DR = (uint16_t)(*tmp & (uint16_t)0x01FF);
      huart->pTxBuffPtr += 2U;
    }
    else
    {
      huart->Instance->DR = (uint8_t)(*huart->pTxBuffPtr++ & (uint8_t)0x00FF);
    }
/*是最后一个数据*/
    if (--huart->TxXferCount == 0U)
    {
      /* Disable the UART Transmit Data Register Empty Interrupt */
      __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);

      /* Enable the UART Transmit Complete Interrupt */
      __HAL_UART_ENABLE_IT(huart, UART_IT_TC);
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
```

所以发送多少字节，就一共发生多少次TXE中断，用来把数据放到移位寄存器；发生一次TC中断，表明数据全都发出，会调用`void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)`回调函数

```cpp
  char *tx_buffer = "Hello,world!";
  char c;
  static volatile g_tx_cplt = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /*使能中断*/
    HAL_UART_Transmit_IT(&huart1, tx_buffer, strlen(tx_buffer));
    Wait_tx_cplt();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) { g_tx_cplt = 1; }

void Wait_tx_cplt(void) {
  while (g_tx_cplt == 0)
    ;            /*等待中断修改标志位*/
  g_tx_cplt = 0; /*重置标志位*/
}
```

### 接收

调用`HAL_UART_Receive_IT`，只是使能中断

```cpp
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  /* Check that a Rx process is not already ongoing */
  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Set Reception type to Standard reception */
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

    return (UART_Start_Receive_IT(huart, pData, Size));
  }
  else
  {
    return HAL_BUSY;
  }
}


HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  huart->pRxBuffPtr = pData;
  huart->RxXferSize = Size;
  huart->RxXferCount = Size;

  huart->ErrorCode = HAL_UART_ERROR_NONE;
  huart->RxState = HAL_UART_STATE_BUSY_RX;

  if (huart->Init.Parity != UART_PARITY_NONE)
  {
    /* Enable the UART Parity Error Interrupt */
    __HAL_UART_ENABLE_IT(huart, UART_IT_PE);
  }

  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_UART_ENABLE_IT(huart, UART_IT_ERR);

  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);

  return HAL_OK;
}
```

接收到一个字节，会触发RXNE中断，调用`HAL_UART_IRQHandler`，进而调用`UART_Receive_IT`

```cpp
static HAL_StatusTypeDef UART_Receive_IT(UART_HandleTypeDef *huart)
{
  uint8_t  *pdata8bits;
  uint16_t *pdata16bits;

  /* Check that a Rx process is ongoing */
  if (huart->RxState == HAL_UART_STATE_BUSY_RX)
  {
    if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
    {
      pdata8bits  = NULL;
      pdata16bits = (uint16_t *) huart->pRxBuffPtr;
      *pdata16bits = (uint16_t)(huart->Instance->DR & (uint16_t)0x01FF);
      huart->pRxBuffPtr += 2U;
    }
    else
    {
      pdata8bits = (uint8_t *) huart->pRxBuffPtr;
      pdata16bits  = NULL;

      if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
      {
        *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
      }
      else
      {
        *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);
      }
      huart->pRxBuffPtr += 1U;
    }

    if (--huart->RxXferCount == 0U)/*收完了*/
    {
      /* Disable the UART Data Register not empty Interrupt */
      __HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);

      /* Disable the UART Parity Error Interrupt */
      __HAL_UART_DISABLE_IT(huart, UART_IT_PE);

      /* Disable the UART Error Interrupt: (Frame error, noise error, overrun error) */
      __HAL_UART_DISABLE_IT(huart, UART_IT_ERR);

      /* Rx process is completed, restore huart->RxState to Ready */
      huart->RxState = HAL_UART_STATE_READY;

      /* Initialize type of RxEvent to Transfer Complete */
      huart->RxEventType = HAL_UART_RXEVENT_TC;

      /* Check current reception Mode :
         If Reception till IDLE event has been selected : */
      if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
      {
        /* Set reception type to Standard */
        huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

        /* Disable IDLE interrupt */
        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

        /* Check if IDLE flag is set */
        if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
        {
          /* Clear IDLE flag in ISR */
          __HAL_UART_CLEAR_IDLEFLAG(huart);
        }

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx Event callback*/
        huart->RxEventCallback(huart, huart->RxXferSize);
#else
        /*Call legacy weak Rx Event callback*/
        HAL_UARTEx_RxEventCallback(huart, huart->RxXferSize);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
      }
      else
      {
        /* Standard reception API called */
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx complete callback*/
        huart->RxCpltCallback(huart);
#else
        /*Call legacy weak Rx complete callback*/
        HAL_UART_RxCpltCallback(huart);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
      }

      return HAL_OK;
    }
    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

```

调用回调函数

```cpp
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
```

如果有耗时操作，由于无法及时使能中断也会造成数据丢失，因为`UART_Receive_IT`会执行

```cpp
__HAL_UART_DISABLE_IT(huart, UART_IT_RXNE);
```

来关闭相应的中断，只有再次调用`HAL_UART_Receive_IT`执行

```cpp
  __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
```

才能再次打开

## UART中断模式改造

1. 一开始就使能接收中断

2. 在接收中断里把数据存入环形Buf，并且重新使能中断

    ```cpp
    void Start_UART_RX(void) {
      HAL_UART_Receive_IT(&huart1, &g_rx_data, 1);
      circle_buf_init(&g_rx_circle_buffer, 100, g_rx_buffer);
    }
    
    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
      circle_buf_write(&g_rx_circle_buffer, g_rx_data);
    
      HAL_UART_Receive_IT(&huart1, &g_rx_data, 1);
    }
    
    int UART_get_char(uint8_t *pVal) {
      return circle_buf_read(&g_rx_circle_buffer, *pVal);
    }
    ```

    

## UART DMA方式

![DMA框图](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedDMA%E6%A1%86%E5%9B%BE.png)

使用中断方式时，在传输、接收数据时，会发生中断，还需要 CPU 执行中断处理函数，从RAM的buf读数据写到串口模块，就会消耗CPU资源，影响main函数。  

DMA会从内存读数据，再写给TDR寄存器，串口发送完成会产生DMA请求，让DMA搬运下一个数据；从RDR寄存器读数据并存入内存。指定量的数据传输完成后，才会产生中断，让程序介入

设置好 DMA（源、目的、地址增减方向、每次读取数据的长度、读取次数）后， DMA 就会自动地在 SRAM 和 UART 之间传递数据：
① 发送时： DMA 从 SRAM 得到数据，写入 UART 的 TDR 寄存器
② 接收时： DMA 从 UART 的 RDR 寄存器得到数据，写到 SRAM 去
③ 指定的数据传输完毕后，触发 DMA 中断；在数据传输过程中，没有中断， CPU 无需处理。  

函数如下：

|      | 查询方式          | 中断方式                                     | DMA 方式                                                     |
| ---- | ----------------- | -------------------------------------------- | ------------------------------------------------------------ |
| 发送 | HAL_UART_Transmit | HAL_UART_Transmit_IT HAL_UART_TxCpltCallback | HAL_UART_Transmit_DMA HAL_UART_TxHalfCpltCallback HAL_UART_TxCpltCallback |
| 接收 | HAL_UART_Receive  | HAL_UART_Receive_IT HAL_UART_RxCpltCallback  | HAL_UART_Receive_DMA HAL_UART_RxHalfCpltCallback HAL_UART_RxCpltCallback |
| 错误 |                   | HAL_UART_ErrorCallback                       | HAL_UART_ErrorCallback                                       |

![DMA](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedDMA.png)

步骤：

1. 调用`HAL_UART_Transmit_DMA `开启传输

2. CPU做别的事

3. 中断调用`XferCpltCallback`，它已经被设置成`UART_DMATransmitCplt`

    ```cpp
    huart->hdmatx->XferCpltCallback = UART_DMATransmitCplt;
    ```

    而`UART_DMATransmitCplt`又被设置成`HAL_UART_TxCpltCallback(huart);`，和之前的IT方式使用方法一样，可以在其中设置某个变量表明传输完成

    ```cpp
    static void UART_DMATransmitCplt(DMA_HandleTypeDef *hdma)
    {
      UART_HandleTypeDef *huart = (UART_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;
      /* DMA Normal mode*/
      if ((hdma->Instance->CCR & DMA_CCR_CIRC) == 0U)
      {
        huart->TxXferCount = 0x00U;
    
        /* Disable the DMA transfer for transmit request by setting the DMAT bit
           in the UART CR3 register */
        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAT);
    
        /* Enable the UART Transmit Complete Interrupt */
        ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_TCIE);
    
      }
      /* DMA Circular mode */
      else
      {
    #if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Tx complete callback*/
        huart->TxCpltCallback(huart);
    #else
        /*Call legacy weak Tx complete callback*/
        HAL_UART_TxCpltCallback(huart);
    #endif /* USE_HAL_UART_REGISTER_CALLBACKS */
      }
    }
    ```

## UART DMA+IDLE

DMA读数据：不知道发来多少数据，没法指定Size参数

如果DMA发现一定时间内串口电平没变化，就会发送`IDLE空闲中断`    

例如，设置DMA接收1000字节，完成标志有三种

1. 收到了1000字节
2. 收到了IDLE中断
3. 错误

IDLE， 空闲的定义是： 总线上在一个字节的时间内没有再接收到数据。
UART 的 IDLE 中断何时发生？ RxD 引脚一开始就是空闲的啊，难道 IDLE 中断一直产生？
不是的。当我们使能 IDLE 中断后，它并不会立刻产生，而是：至少收到 1 个数据后，发现在一个字节的时间里，都没有接收到新数据，才会产生 IDLE 中断。
我们使用 DMA 接收数据时，确实可以提高 CPU 的效率，但是“无法预知要接收多少数据”，而我们想尽快处理接收到的数据。怎么办？比如我想读取 100 字节的数据，但是接收到 60 字节后对方就不再发送数据了，怎么办？我们怎么判断数据传输中止了？可以使用IDLE 中断。 在这种情况下， DMA 传输结束的条件有 3：
① 接收完指定数量的数据了，比如收到了 100 字节的数据了， HAL_UART_RxCpltCallback
被调用
② 总线空闲了： HAL_UARTEx_RxEventCallback 被调用
③ 发生了错误： HAL_UART_ErrorCallback 被调用  

使用 IDLE 状态来接收的函数有：

|          | 函数                         | 回调函数                                                     |
| -------- | ---------------------------- | ------------------------------------------------------------ |
| 查询方式 | HAL_UARTEx_ReceiveToIdle     | 根据返回参数 RxLen 判断是否接收完毕，还是因为空闲而返回      |
| 中断方式 | HAL_UARTEx_ReceiveToIdle_IT  | 完毕： HAL_UART_RxCpltCallback <br />因为空闲而中止： HAL_UARTEx_RxEventCallback |
| DMA 方式 | HAL_UARTEx_ReceiveToIdle_DMA | 传输一半： HAL_UART_RxHalfCpltCallback <br />完毕： HAL_UART_RxCpltCallback    <br />因为空闲而中止： HAL_UARTEx_RxEventCallback |
| 错误     |                              | HAL_UART_ErrorCallback                                       |

查询方式

```cpp
    while (huart->RxXferCount > 0U)
    {
      /* Check if IDLE flag is set */
      if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
      {
        /* Clear IDLE flag in ISR */
        __HAL_UART_CLEAR_IDLEFLAG(huart);

        /* If Set, but no data ever received, clear flag without exiting loop */
        /* If Set, and data has already been received, this means Idle Event is valid : End reception */
        if (*RxLen > 0U)
        {
          huart->RxEventType = HAL_UART_RXEVENT_IDLE;
          huart->RxState = HAL_UART_STATE_READY;

          return HAL_OK;
        }
      }

      /* Check if RXNE flag is set */
      if (__HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE))
      {
        if (pdata8bits == NULL)
        {
          *pdata16bits = (uint16_t)(huart->Instance->DR & (uint16_t)0x01FF);
          pdata16bits++;
        }
        else
        {
          if ((huart->Init.WordLength == UART_WORDLENGTH_9B) || ((huart->Init.WordLength == UART_WORDLENGTH_8B) && (huart->Init.Parity == UART_PARITY_NONE)))
          {
            *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x00FF);
          }
          else
          {
            *pdata8bits = (uint8_t)(huart->Instance->DR & (uint8_t)0x007F);
          }

          pdata8bits++;
        }
        /* Increment number of received elements */
        *RxLen += 1U;
        huart->RxXferCount--;
      }
```

中断方式

```cpp
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  HAL_StatusTypeDef status;

  /* Check that a Rx process is not already ongoing */
  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Set Reception type to reception till IDLE Event*/
    huart->ReceptionType = HAL_UART_RECEPTION_TOIDLE;
    huart->RxEventType = HAL_UART_RXEVENT_TC;

    status =  UART_Start_Receive_IT(huart, pData, Size);

    /* Check Rx process has been successfully started */
    if (status == HAL_OK)
    {
      if (huart->ReceptionType == HAL_UART_RECEPTION_TOIDLE)
      {
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        ATOMIC_SET_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);
      }
      else
      {
        /* In case of errors already pending when reception is started,
           Interrupts may have already been raised and lead to reception abortion.
           (Overrun error for instance).
           In such case Reception Type has been reset to HAL_UART_RECEPTION_STANDARD. */
        status = HAL_ERROR;
      }
    }

    return status;
  }
  else
  {
    return HAL_BUSY;
  }
}
```

↑使能IDLE中断

IDLE中断发生后，如果使用DMA，就取消DMA；如果使用中断，就禁止接收中断，最后调用回调函数`HAL_UARTEx_RxEventCallback`

```cpp
    /* Check if DMA mode is enabled in UART */
    if (HAL_IS_BIT_SET(huart->Instance->CR3, USART_CR3_DMAR))
    {
      /* DMA mode enabled */
      /* Check received length : If all expected data are received, do nothing,
         (DMA cplt callback will be called).
         Otherwise, if at least one data has already been received, IDLE event is to be notified to user */
      uint16_t nb_remaining_rx_data = (uint16_t) __HAL_DMA_GET_COUNTER(huart->hdmarx);
      if ((nb_remaining_rx_data > 0U)
          && (nb_remaining_rx_data < huart->RxXferSize))
      {
        /* Reception is not complete */
        huart->RxXferCount = nb_remaining_rx_data;

        /* In Normal mode, end DMA xfer and HAL UART Rx process*/
        if (huart->hdmarx->Init.Mode != DMA_CIRCULAR)
        {
          /* Disable PE and ERR (Frame error, noise error, overrun error) interrupts */
          ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_PEIE);
          ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

          /* Disable the DMA transfer for the receiver request by resetting the DMAR bit
             in the UART CR3 register */
          ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_DMAR);

          /* At end of Rx process, restore huart->RxState to Ready */
          huart->RxState = HAL_UART_STATE_READY;
          huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

          ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

          /* Last bytes received, so no need as the abort is immediate */
          (void)HAL_DMA_Abort(huart->hdmarx);
        }

        /* Initialize type of RxEvent that correspond to RxEvent callback execution;
        In this case, Rx Event type is Idle Event */
        huart->RxEventType = HAL_UART_RXEVENT_IDLE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx Event callback*/
        huart->RxEventCallback(huart, (huart->RxXferSize - huart->RxXferCount));
#else
        /*Call legacy weak Rx Event callback*/
        HAL_UARTEx_RxEventCallback(huart, (huart->RxXferSize - huart->RxXferCount));
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
      }
      return;
    }
    else
    {
      /* DMA mode not enabled */
      /* Check received length : If all expected data are received, do nothing.
         Otherwise, if at least one data has already been received, IDLE event is to be notified to user */
      uint16_t nb_rx_data = huart->RxXferSize - huart->RxXferCount;
      if ((huart->RxXferCount > 0U)
          && (nb_rx_data > 0U))
      {
        /* Disable the UART Parity Error Interrupt and RXNE interrupts */
        ATOMIC_CLEAR_BIT(huart->Instance->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE));

        /* Disable the UART Error Interrupt: (Frame error, noise error, overrun error) */
        ATOMIC_CLEAR_BIT(huart->Instance->CR3, USART_CR3_EIE);

        /* Rx process is completed, restore huart->RxState to Ready */
        huart->RxState = HAL_UART_STATE_READY;
        huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

        ATOMIC_CLEAR_BIT(huart->Instance->CR1, USART_CR1_IDLEIE);

        /* Initialize type of RxEvent that correspond to RxEvent callback execution;
           In this case, Rx Event type is Idle Event */
        huart->RxEventType = HAL_UART_RXEVENT_IDLE;

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
        /*Call registered Rx complete callback*/
        huart->RxEventCallback(huart, nb_rx_data);
#else
        /*Call legacy weak Rx Event callback*/
        HAL_UARTEx_RxEventCallback(huart, nb_rx_data);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */
      }
      return;
    }
  }
```

### 接收

```cpp
void Start_UART_RX(void) {
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, &g_rx_temp_buf, 10);
  circle_buf_init(&g_rx_circle_buffer, 100, g_rx_buffer);
}
/* 数据暂时发完了，存入环形缓冲区，收到了Size个数据 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
  for (int i = 0; i < Size; i++) {
    circle_buf_write(&g_rx_circle_buffer, g_rx_temp_buf[i]);
  }
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, &g_rx_temp_buf, 10);
}
/*接收完毕还是调用这个回调函数*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  for (int i = 0; i < 10; i++) {
    circle_buf_write(&g_rx_circle_buffer, g_rx_temp_buf[i]);
  }

  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, &g_rx_temp_buf, 10);
}


int main()
{
  while (1)
	{
    /* use dma to tx */
    HAL_UART_Transmit_DMA(&huart1, str2, strlen(str2));

    /* wait for tc */
    Wait_Tx_Complete();

    //while (HAL_OK != HAL_UART_Receive(&huart1, &c, 1, 100));

    while (0 != UART1GetChar(&c));

    c = c+1;

    HAL_UART_Transmit(&huart1, &c, 1, 1000);
    HAL_UART_Transmit(&huart1, "\r\n", 2, 1000);
  }
}
```

## printf重定向

勾选`use micro lib`

```cpp
int fputc(int ch, FILE* stream)
{
    HAL_UART_Transmit(&huart1, (const uint8_t *)&ch, 1, 10);
    return ch;
}
static int g_last_char;
static int g_backspace = 0;
int fgetc(FILE *f)
{
    int ch;
    if (g_backspace)
    {
    g_backspace = 0;
    return g_last_char;
	}
    while (0 != UART1GetChar((uint8_t *)&ch));
    g_last_char = ch;
    return ch;
}
int __backspace(FILE *stream)
{
    g_backspace = 1;
    return 0;
}
```

## I2C

### I2C程序层次

半双工，因为只有一跟数据线，发送的同时不能接收

一主多从

#### 硬件原理图

![image-20260210171955849](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210171955849.png)

#### 硬件框图

![image-20260210172106323](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210172106323.png)

编写程序，通过I2C初始化SSD1306，然后把数据写到芯片里面的显存，芯片会把显存的数据刷到屏幕上

#### 软件层次

要在 OLED 上显示字符串，涉及这几个层次的程序： 

① 应用程序：我来决定“在哪个位置、显示什么字符” 

② 库函数(字符/图片显示)：我收集了字符点阵，知道发送点阵数据才能显示字符 

`OLED_PrintString`

③ OLED(SSD1306)取出程序：我知道发送什么 I2C 数据（先设置地址、再发送数据），才能 把点阵数据写入显存 

④ I2C 控制器驱动(HAL)：我可以发送 I2C 数据

![image-20260210172348161](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210172348161.png)

### I2C协议

I2C(Inter-Integrated Circuit，又称 IIC)总线是一种由 PHILIPS 公司开发的串行总 线，用于连接微控制器及其外围设备，它具有如下特点： 

- 只有两条总线线路：一条串行数据线(SDA)，一条串行时钟线(SCL)。 
- 每个连接到总线的器件都可以使用软件根据它的惟一的地址来识别。
- 传输数据的设备间是简单的主/从关系。
- 主机可以用作主机发送器或主机接收器。
- 它是一个真正的多主机总线，两个或多个主机同时发起数据传输时，可以通过冲 突检测和仲裁来防止数据被破坏。
- 串行的 8 位双向数据传输，位速率在标准模式下可达 100kbit/s，在快速模式下 可达 400kbit/s，在高速模式下可达 3.4Mbit/s。
- 片上的滤波器可以增加抗干扰功能，保证数据的完整。
- 连接到同一总线上的 IC 数量只受到总线的最大电容 400pF 的限制。

![image-20260210172803542](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210172803542.png)

先说明一些术语，

- 发送器：发送数据到总线的器件
- 接收器：从总线接收数据的器件
- 主机：发起/停止数据传输、提供时钟信号的器件
- 从机：被主机寻址的器件
- 多主机：可以有多个主机试图去控制总线，但是不会破坏数据
- 仲裁：当多个主机试图去控制总线时，通过仲裁可以使得只有一个主机获得总线 控制权，并且它传输的信息不被破坏
- 同步：多个器件同步时钟信号的过程

#### 传输数据类比

![image-20260210173202435](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210173202435.png)

体育老师：可以把球发给学生，也可以把球从学生中接过来。 ⚫  

![image-20260210173332101](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210173332101.png)

都是老师主动发起，学生被动接受

依照这个简单的例子，可以引入 IIC 的传输协议： 

1. 老师说开始了，表示开始信号(start)
2. 老师提醒某个学生要发球，表示发送地址和方向(address/read/write)
3. 老师发球/接球，表示数据的传输
4. 到球要回应：回应信号(ACK)
5. 老师说结束，表示 IIC 传输结束(P)

#### 数据格式

##### 写操作

1. 主芯片发出start信号
2. 发出设备地址，方向(0表示写；1表示读)
3. 从设备回应(用来确定这个设备是否存在)，然后就能传输数据
4. 主设备发送8bit数据给从设备，并等待回应
5. 每传输一字节数据，接收方要有一个回应信号(确认数据是否接受完成)，然后再传输下一个数据
6. 数据发送完成后，主芯片会发送一个停止信号

白色背景是主->从，灰色背景是从->主

![image-20260210173604130](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210173604130.png)

##### 读操作

1. 主芯片发出start信号
2. 发出设备地址，方向(0表示写；1表示读)
3. 从设备回应(用来确定这个设备是否存在)，然后就能传输数据
4. 从设备发送8bit数据给主设备，并等待回应
5. 每传输一字节数据，接收方要有一个回应信号(确认数据是否接受完成)，然后再传输下一个数据
6. 数据发送完成后，主芯片会发送一个停止信号

白色背景是主->从，灰色背景是从->主

![image-20260210174332886](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210174332886.png)



无论读写，都要先发设备地址和方向

#### I2C信号

I2C 总线在传送数据过程中共有三种类型信号：开始信号、结束信号和响应信号。

1. 开始信号(S)：SCL 为高电平时，SDA 由高电平向低电平跳变，开始传送数据。

2. 结束信号(P)：SCL 为低电平时，SDA 由低电平向高电平跳变，结束传送数据。

3. 响应信号(ACK)：接收器在接收到 8 位数据后，在第 9 个时钟周期，拉低 SDA 电平。 

    它们的波形如图所示

![image-20260210174702250](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210174702250.png)

> [!NOTE]
>
> SDA 上传输的数据必须在 SCL 为高电平期间保持稳定，SDA 上的数据只能在 SCL 为低电 平期间变化

![image-20260210174754053](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210174754053.png)

![image-20260210175328251](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210175328251.png)



例如，写：0b1010100

SCL低电平，SDA可以改变；SCL高电平，SDA保持稳定

第一个字节前7位是地址，第八位表示方向。第八位发完，主设备释放SDA，从设备驱动SDA，拉低进行回应

![image-20260210180549842](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210180549842.png)

SDA线、SCL线都是开漏接法

![image-20260210180646793](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210180646793.png)

二者的漏极都连接到总线，默认高电平，这样的话如果一方拉低，不会造成短路

SCL线也可以由双方拉低，双方任意一方觉得自己没准备好，要等一下就可以拉低SCL

协议并没有规定数据表示什么

例如，读写存储器，可以先发写入数据的地址，然后再发很多要写入的数据

### STM32I2C硬件结构

GPIO模拟IIC：根据波形图编写函数，如发出Start信号、Stop信号、发送给一个字节等函数

#### 硬件框图

![image-20260210181455100](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210181455100.png)

发数据：数据写入右上角的数据寄存器

读数据：读取寄存器即可

配置：

1. CR1,CR2设置基准时钟T
2. CCR设置高低电平时间，多少个T
3. 状态寄存器是只读的

![image-20260210182046587](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210182046587.png)

根据手册，设置控制寄存器1(CR1)的第八位START信号为1，即可产生start信号。读取SR1的第0位表示结束了。然后把设备地址写入data register寄存器

如何判断得到回应了吗：SR1的某一位表明

### I2C HAL 编程

#### 概述

读B：

1. A把地址发给B
2. B把数据发给A

读数据的时候，发送和接受放在一个函数里面实现：mem模式(只是一个软件上的概念)

#### CubeMX 配置

![image-20260210183149203](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260210183149203.png)

#### 查询方式

##### Master模式

```c
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout); 

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout); 
```

参数说明： 

1. I2C_HandleTypeDef *hi2c 使用哪个 I2C 控制器
2. uint16_t DevAddress 设备地址，需要把 7 位地址左移 1 位
3. uint8_t *pData 数据 buffer 
4. uint16_t Size 数据个数 
5. uint32_t Timeout 超时时间，单位是 Tick，一般是 1ms 
6. 返回值 HAL_OK：成功 HAL_ERROR：错误 HAL_BUSY：总线忙 HAL_TIMEOUT：超时

##### 读写MPU6050

1. 写

![image-20260215234041812](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260215234041812.png)

2. 读

![image-20260215234142030](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260215234142030.png)

3. 地址

![image-20260215234215164](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260215234215164.png)

4. 寄存器

![image-20260215234242553](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260215234242553.png)

```c
uint8_t reg = 0x75;
uint8_t val = 0;
HAL_I2C_Master_Transmit(&hi2c1,(0x68 << 1),&reg,1,10000);
HAL_I2C_Master_Transmit(&hi2c1,(0x68 << 1),&val,1,10000);
```

##### MEM模式

MEM 模式只是软件上的概念，仍然是作为 Master 读写数据。 上述函数只能发起单向的数据传输，但是在实际编程中，比如要“读存储地址 addr 上 的数值”，涉及 2 个方向的数据传输：要向 I2C 设备发起写操作把“存储地址 addr”发给 他，然后向 I2C 设备发起读操作得到数值。 还 有 一 种 情 况 ，“ 把 数 值 val 写 到 存 储 地 址 addr ” 上 ， 使 用“HAL_I2C_Master_Transmit”函数时，需要在数据 buffer 里填入 addr 和 val，不太直观。 这时可以使用下面的函数：

``` c
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout); HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
```



 参数说明： 

1. I2C_HandleTypeDef *hi2c 使用哪个 I2C 控制器 
2. uint16_t DevAddress 设备地址，需要把 7 位地址左移 1 位 
3. uint16_t MemAddress 存储地址，即 I2C 设备上的寄存器地址或 存储地址 
4. uint16_t MemAddSize 存储地址的大小，有 2 种取值： 
    1. I2C_MEMADD_SIZE_8BIT：存储地址为 1 字 节，就是 MemAddress 的低字节
    2. I2C_MEMADD_SIZE_16BIT：存储地址为 2 字 节，先发送 MemAddress 的高字节，再发送 低字节
5. uint8_t *pData 数据 buffer
6. uint16_t Size 数据个数 
7. uint32_t Timeout 超时时间，单位是 Tick，一般是 1ms 
8. 返回值 HAL_OK：成功 HAL_ERROR：错误 HAL_BUSY：总线忙 HAL_TIMEOUT：超时

```c
val = 0x55;
HAL_I2C_Mem_Write(&hi2c1, (0x68<<1), 0x31, I2C_MEMADD_SIZE_8BIT, &val, 1, 1000);
val = 0;
HAL_I2C_Mem_Read(&hi2c1, (0x68<<1), 0x31, I2C_MEMADD_SIZE_8BIT, &val, 1, 1000);
```

#### 中断模式

##### Master模式

使用中断方式写 I2C 设备、读 I2C 设备函数原型如下： 

```c
HAL_StatusTypeDef HAL_I2C_Master_Transmit_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size); HAL_StatusTypeDef HAL_I2C_Master_Receive_IT(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
```



 参数说明：

1. I2C_HandleTypeDef *hi2c 使用哪个 I2C 控制器

2. uint16_t DevAddress 设备地址，需要把 7 位地址左移 1 位 

3. uint8_t *pData 数据 buffer *

4. *uint16_t Size 数据个数 

5. 返回值 HAL_OK：成功 HAL_BUSY：总线忙 

    

> [!NOTE]
>
> 这两个函数只是发出 Start 信号，后续完全由中断程序来传输后续数据。这两个函数 返回后，并不表示传输已经完成，需要在中断回调函数里判断。

要使用中断方式，还需要使用 STM32CubeMX 配置 I2C 中断，如下：

![image-20260215235800555](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260215235800555.png)

 如果传输完成或出错，如下回调函数会被调用： 

```c
/* 主设备发送完成回调函数 */ void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c); /* 主设备接收完成回调函数 */ void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c); /* 出错回调函数 */ void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) 
```



可以在这些回调函数里设置变量，表示传输已经完成。

```c
static volatile int g_i2c1_tx_complete = 0;
static volatile int g_i2c1_rx_complete = 0;

/* 主设备发送完成回调函数 */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == &hi2c1)
	{
		g_i2c1_tx_complete = 1;
	}
}

void Wait_I2C1Tx_Complete(void)
{
	while (g_i2c1_tx_complete == 0);
	g_i2c1_tx_complete = 0;
}

/* 主设备接收完成回调函数 */
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c == &hi2c1)
	{
		g_i2c1_rx_complete = 1;
	}
}

void Wait_I2C1Rx_Complete(void)
{
	while (g_i2c1_rx_complete == 0);
	g_i2c1_rx_complete = 0;
}

```

## SPI

### SPI程序层次

#### 硬件原理图

![image-20260216000254948](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216000254948.png)

#### 硬件框图

![image-20260216000316653](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216000316653.png)

#### 软件层次

要操作 Flash，涉及这几个层次的程序：

1. 应用程序：我来决定“在哪个位置、读写什么数据”
2. Flash 驱动：我知道发送什么格式的 SPI 数据才能读、写、擦除 Flash
3. SPI 控制器驱动(HAL)：我可以发送 SPI 数据

### SPI协议

#### 概念

SPI（Serial Peripheral Interface，串行外设接口）是由摩托罗拉（Motorola）在 1980 前后提出的一种**全双工同步串行**通信接口，它用于 MCU 与各种外围设备以串行方式进 行通信以交换信息，通信速度最高可达 25MHz 以上。 

SPI 接口主要应用在 EEPROM、FLASH、实时时钟、网络控制器、OLED 显示驱动器、AD 转换器，数字信号处理器、数字信号解码器等设备之间。 

SPI 通常由四条线组成，一条主设备输出与从设备输入（Master Output Slave Input， MOSI），一条主设备输入与从设备输出（Master Input Slave Output，MISO），一条时钟信 号（Serial Clock，SCLK），一条从设备使能选择（Chip Select，CS）。 

SPI 可以一个主机连接单个或多个从机，每个从机都使用一个引脚进行片选，物理连 接示意图如图所示：

![image-20260216000649280](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216000649280.png)

在 SCK 时钟周期的驱动下，主机把数据驱动到 MOSI 上传给从机，从机把数据驱动到 MISO 上传给主机，主机发送 N 字节给从机时，必定能接收到 N 字节，至于接收到的 N 字节是否有意义由 从机决定。如果主机只想对从机进行写操作，主机只需忽略接收的从机数据即可。如果主 机只想读取从机数据，它也要发送数据给从机（发送的数据可以是空数据）。

时钟线和数据线是共用的，主控芯片通过片选引脚选择与谁通信，同一时间只能选择一个

![image-20260216000958789](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216000958789.png)

问题

1. SCK初始电平(CPOL——极性)
2. SCK的第1/2个边沿传输数据(CPHA——相位)

SPI 有四种传输模式，如下表所示，主要差别在于 CPOL 和 CPHA 的不同。 

1. CPOL（Clock Polarity，时钟极性）表示 SCK 在空闲时为高电平还是低电平。当 CPOL=0，SCK 空闲时为低电平，当 CPOL=1，SCK 空闲时为高电平。 
2. CPHA（Clock Phase，时钟相位）表示 SCK 在第几个时钟边缘采样数据。当 CPHA=0， 在 SCK 第一个边沿采样数据，当 CPHA=1，在 SCK 第二个边沿采样数据。

| 模式 | CPOL | CPHA | 时钟空闲状态 | 数据采样边沿       | 数据变化边沿       | 典型应用场景                     |
|------|------|------|----------------|--------------------|--------------------|----------------------------------|
| 0    | 0    | 0    | 低电平         | 第一个边沿（上升沿） | 下降沿             | 大多数传感器（如BME280）、Flash（如W25Q64）、SD卡  |
| 1    | 0    | 1    | 低电平         | 第二个边沿（下降沿） | 上升沿             | 部分ADC芯片（如MCP3008）     |
| 2    | 1    | 0    | 高电平         | 第一个边沿（下降沿） | 上升沿             | 较少见，某些射频模块         |
| 3    | 1    | 1    | 高电平         | 第二个边沿（上升沿） | 下降沿             | EEPROM（如AT25系列）、部分RF模块、MPU6050  |

![image-20260216001337738](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216001337738.png)

### STM32 SPI 硬件结构

#### 硬件框图

![image-20260216001623773](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216001623773.png)

在 SPI 传输里，有 2 个角色：Master、Slave。我们常用 Master，它主动发起传输、 产生时钟信号。 对于 STM32，如何使用 SPI Master？ 

先初始化：

① 配置 SPI_CR1 寄存器（Control Register）：配置波特率 

② 配置 SPI_CR1 寄存器（Control Register）：配置 CPOL、CPHA 

③ 配置 SPI_CR1 寄存器（Control Register）：配置 LSBFIRT 以决定先传输最高位还是最 低位 

④ 配置 SPI_CR1 寄存器（Control Register）：配置 NSS 使用软件控制，一般使用 GPIO 来 选择其他 Slave 设备，不是 NSS。 

⑤ 配置 SPI_CR1 寄存器（Control Register）：选择 Master 模式、使能 SPI。 

如何发送数据呢？把数据写入“SPI_DR”即可，这个数据会被放入放入“Tx Buffer”， 进而放入“shift register”，它就会一位一位地出现在 MOSI 信号线上，发送给 Slave 设 备。当发送完毕后，TXE 标记位被设置。可以使用查询方式或中断方式监测到 TXE 被置位。 

如何接收数据呢？即使我们只想接收数据，也要把一个数组写入“SPI_DR”，在发送数 据的同时就会接收到数据：MISO 信号线上的数据被一位一位地移入“shift register”， 然后被放入“Rx Buffer”并且 RXNE 标记位被置一。可以使用查询方式或中断方式监测到 RXNE 被置位，然后读取“SPI_DR”得到数据。

### SPL HAL库编程

#### CubeMX配置

![image-20260216160721212](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216160721212.png)

#### 查询方式

```c
/* 发送同时接收数据 */
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t
*pRxData, uint16_t Size, uint32_t Timeout);
/* 发送数据 */
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size,
uint32_t Timeout);
/* 接收数据 */
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size,
uint32_t Timeout);
```

参数说明 

1. SPI_HandleTypeDef *hspi 使用哪个 SPI 控制器 
2. uint8_t *pTxData 或 uint8_t *pData 要发送的数据的 buffer
3. uint8_t *pRxData 或 uint8_t *pData 存储接收到数据的 buffer
4. uint16_t Size 数据个数 
5. uint32_t Timeout 超时时间，单位是 Tick，一般是 1ms 
6. 返回值 HAL_OK：成功 HAL_ERROR：错误 HAL_BUSY：总线忙 HAL_TIMEOUT：超时

#### 中断方式

```c
/* 发送同时接收数据 */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData,
uint8_t *pRxData, uint16_t Size);
/* 发送数据 */
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t
Size);
/* 接收数据 */
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);

```

参数说明 

1. SPI_HandleTypeDef *hspi 使用哪个 SPI 控制器
2. uint8_t *pTxData 或 uint8_t *pData 要发送的数据的 buffer 
3. uint8_t *pRxData 或 uint8_t *pData 存储接收的数据的 buffer
4. uint16_t Size 数据个数 
5. uint32_t Timeout 超时时间，单位是 Tick，一般是 1ms 
6. 返回值 HAL_OK：成功 HAL_ERROR：错误 HAL_BUSY：总线忙 HAL_TIMEOUT：超时 

> [!NOTE]
>
> 这几个函数只是启动 SPI 传输，后面完全由中断程序来传输后续数据。这两个函数返回后，并不表示传输已经完成，需要在中断回调函数里判断。

 要使用中断方式，还需要使用 STM32CubeMX 配置 SPI 中断，如下：

![image-20260216160938567](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216160938567.png)

如果传输完成或出错，如下回调函数会被调用：

```c
/* 发送、接收完成回调函数 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
/* 发送完成回调函数 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
/* 接收完成回调函数 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
/* 出错回调函数 */
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
```

可以在这些回调函数里设置变量，表示传输已经完成。

#### DMA模式

```c
/* 发送同时接收数据 */
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData,
uint8_t *pRxData, uint16_t Size);
/* 发送数据 */
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t
Size);
/* 接收数据 */
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t
Size);

```

> [!NOTE]
>
> 这几个函数只是启动 SPI 传输，以后完全由 DMA 来传输后续数据。这两个函数返回后， 并不表示传输已经完成，需要在回调函数里判断。 

要使用 DMA 方式，还需要使用 STM32CubeMX 配置 DMA，如下：

![image-20260216165619929](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216165619929.png)

如果传输完成或出错，如下回调函数会被调用： 

```c
/* 发送、接收完成回调函数 */ 
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi); 
/* 发送完成回调函数 */ 
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi); 
/* 接收完成回调函数 */ 
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) 
/* 出错回调函数 */ 
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi); 
```



可以在这些回调函数里设置变量，表示传输已经完成。

## TIM

STM32 系列单片机有系统定时器（SysTick）、还有 2 个高级定时器 TIM1 和 TIM8，4 个 通用定时器 TIM2/3/4/5，2 个基本定时器 TIM6 和 TIM7。就功能方面，高级定时器>通用定 时器>基本定时器。理解了高级定时器，就能理解其他两种定时器。

定时器最基础的功能，就是“计数”，以下框图来自“高级定时器”：

![image-20260216171820473](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216171820473.png)

暂且不理会其它电路，只看红框里面的①②。先看②，它是一个 16 位的计数器：每进 来一个时钟（CK_CNT），里面的计数值“CNT counter”就累加，可以从 0 一直累加到 0xFFFF。如果时钟频率是 72MHz，那么从 0 累加到 0xFFFF 的时间是 65535/72=910us。 

如果想让计数器②的计时时间更长点，就要把时钟频率降下来，这需要使用到分频器 （图中①）。分频器也是一个计数器，假设输入的时钟“CK_PSC”是 72MHz，分频器的分频 系数设置为 2，它就会计数——每进来 2 个时钟，只输出 1 个时钟。这样，后面的计数器 ②从 0 累加到 0xFFFF 的时间就增加了一倍。 

对于计数器②，可以设置让它从 0 累加到某个数值——“Auto-reload register”的 数值（这被称为重载值）时发出中断，然后再从 0 再次累加。根据“CK_PSC”的频率、计 数器①的分频系数，就可以设置恰当的重载值，让定时器②周期性地产生中断，这就是系 统时钟，比如 HAL 库里使用的“HAL_Delay”就是基于系统时钟实现的



对于计数器①，它的时钟来源有多种选择，如下图所示： 

① 内部时钟：用作普通的定时器，比如系统定时器 

② ETR（External Trigger Input），外部触发的输入信号：可以统计外部触发信号 

③ ITR0~ITR3（Internal Trigger0~3），内部触发信号：内部触发信号来自其他定时器的 “TRGO”信号，用于定时器的级联 

④ TIMx_CH1/2/3/4：也可以作为外部输入信号

![image-20260216172100094](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefinedimage-20260216172100094.png)
