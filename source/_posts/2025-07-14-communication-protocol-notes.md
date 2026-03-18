---
title: 通信协议学习笔记
date: 2025-07-14 20:39:00 +0800
categories: [Learning, Tools]
tags: [protocol]
description: 通信协议基础学习笔记，包含 TCP/IP 模型、HTTP、Protobuf 等内容
toc: true
comments: true
---

## HTTP

### TCP/IP 模型

| OSI 模型（国际标准化组织 ISO 提出） | 功能 |
| -------------------------------- | ---------------------- |
| 物理层 | 传输⽐特流 |
| 数据链路层 | 节点之间传输帧 |
| ⽹络层 | 报⽂分组、路由选择 |
| 传输层 | 端到端传输和流量控制 |
| 会话层 | 建⽴、管理和终⽌会话 |
| 表⽰层 | 负责数据格式转换和加密 |
| 应⽤层 | 提供⽹络服务 |

| TCP/IP 模型 | 功能 |
| ---------- | ------------------------------------------------------------ |
| 应⽤层 | 包含⾼层协议，如 HTTP、FTP、SMTP 等 |
| 传输层 | 提供端到端通信，包含传输控制协议（TCP）和⽤⼾数据报协议（UDP） |
| 互联⽹层 | 对应 OSI 模型的⽹络层，负责 IP 地址和路由选择，包含 IP 协议 |
| ⽹络接⼊层 | 相当于 OSI 模型的物理层和数据链路层 |

TCP/IP 模型是对 OSI 模型的简化

### IP 地址

互联⽹协议的⽬的是解决实现⼤规模、异构⽹络的互联问题。IP 地址是⽹络上的设备的地址标识。IP 地址分为 IPv4 和 IPv6

#### IPv4

IPv4 是 32 位（4 字节）地址，因此⼀共可以存储 $2^{32}=4294967296$ 个地址，但是实际使⽤中保留了很多特
殊⽤途的地址，如专⽤⽹络（约 1800 万个地址）和多播地址（约 2.7 亿个地址）。

为⽅便表⽰，IPv4 采⽤点分⼗进制形式表⽰，4 个字节分别⽤⼗进制写出，中间使⽤点分割。如 `192.168.43.14`

2011 年，IPv4 主要地址池⽤尽；2019 年，所有 IPv4 地址分配完毕

#### IPv6

IPv6 采⽤ 128bit 地址，每 16bit 为⼀组，中间使⽤冒号隔开：`ABCD:EF01:2345:6789:ABCD:EF01:2345:6789`

IPv6 可以存储 $2^{128}=3.4\times10^{38}$ 个地址，解决了 IPv4 资源不⾜的问题。

### 域名

IP 地址可以唯⼀的标记⽹络上的计算机，但是数字冗⻓，难以记忆；于是有了字符型的地址⽅案——域名地址

IP 地址和域名地址是⼀⼀对应的，`www.baidu.com` 就是域名地址

### 端口

计算机有多个进程并⾏执⾏，游览器需要双向传输信息，微信也需要双向传输信息，QQ 也需要双向传输信息。那么，当主机接收到数据包后，应该转发给哪个进程？

由此，引⼊端⼝的概念区分不同进程。⼀个 IP 地址允许有 65536 个端⼝（编号 0-65535）。0-1023 编号的端⼝称为周知端⼝，⼤多数固定分配给某个服务，例如 80 端⼝分配给 www 服务（包含 http）。

### HTTP：超⽂本传输协议

http 是万维⽹ www 数据通信的基础

http 是经典的 server-client 模式：

1. 客⼾与服务器建⽴连接
2. 客⼾向服务器发出请求（request）
3. 服务器接受请求，返回相应⽂件作为应答（response）
4. 客⼾和服务器关闭连接

http 连接是⼀次性连接，每次连接只能发送 1 个请求，服务器返回应答后连接⽴即关闭

#### HTTP 请求格式

请求⾏--请求头--空⾏--请求体

##### 请求⾏

包括 HTTP ⽅法、请求的 URI、HTTP 版本

```
GET /index.html HTTP/1.1
```

经典的 HTTP ⽅法有：

- **GET**：请求指定资源
- **POST**：向资源提交/上传数据
- **PUT**：向指定资源上传其最新内容
- **DELETE**：删除资源

##### 请求头

包括⼀系列的键值对，例如：

- **Host**：服务器域名
- **User-Agent**：客⼾端的软件信息
- **Content-Type**：请求体的媒体类型
- **Content-Length**：请求体的⻓度
- **Accept**：⽤⼾可以接受的内容类型

```
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
```

空⾏⽤于分隔头部和请求体

请求体⼀般在 POST、PUT 请求中，⼀般代表需要上传的数据。请求体可以是 JSON 或者 XML 格式：

```
POST /submit-form HTTP/1.1
Host: www.example.com
Content-Type: application/x-www-form-urlencoded
Content-Length: 27
{
"name": "John Doe",
"age": 30
}
```

#### HTTP 响应格式

状态⾏--响应头部--空⾏--响应体

状态⾏包括 HTTP 版本、状态码和状态描述：

```
HTTP/1.1 200 OK
```

常见状态码：

- **200 OK** 请求成功（此时响应体是 GET 和 POST 请求的应答⽂档）
- **204 No Content** 请求成功，没有返回⽂档
- **400 Bad Request** 服务器未能理解请求
- **401 Unauthorized** 被请求的界⾯需要⽤⼾名和密码
- **403 Forbidden** 对⻚⾯的访问被禁⽌
- **404 Not Found** 服务器⽆法找到请求⻚⾯
- **408 Request Timeout** 请求超时

## Protobuf

### 序列化协议

通信传输过程中⾯临的问题：不同的编程语⾔使⽤不同的数据结构，传输不⽅便

序列化协议定义了数据的编码和解码⽅式，确保发送⽅和接收⽅都能正确理解和处理数据。通过将复杂的数据结构（如对象、数组等）转换成线性的字节流，序列化协议消除了潜在的兼容性问题。

常⻅的序列化协议有：JSON、XML、protobuf

例如，创建⼀个姓名是 John Doe，年龄 30 的⼈：

#### JSON

```json
{
"name": "John Doe",
"age": 30
}
```

优点：易读、易写、⼴泛⽀持；序列化、反序列化速度较慢

#### XML

```xml
<person>
<name>John Doe</name>
<age>30</age>
</person>
```

优点：可扩展、可⾃定义标签、⼴泛⽀持；序列化、反序列化速度较慢

#### Protobuf

protobuf 的优点：序列化后为⼆进制格式，⾼效，⽀持多种语⾔，向后兼容

向后兼容：新版本可以打开老的文件

protobuf 需要预先定义 proto ⽂件：

```protobuf
syntax = "proto3";
message Person {
    string name = 1; // 编号是 1
    int32 age = 2;   // 编号是 2
}
```

随后，使⽤ protoc 编译 proto ⽂件：

```bash
protoc person.proto --python_out=.
```

会生成 `person_pb2.py`，可以直接调用其中的东西

随后，创建⼀个新的 python ⽂件：

```python
from person_pb2 import Person
person = Person()
person.name = 'Alice'
person.age = 25
data = person.SerializeToString()
print(data)
print(" ".join(f"{byte:02x}" for byte in data))
print(person.age)
```

运行结果：

```
b'\n\x05Alice\x10\x19'
0a 05 41 6c 69 63 65 10 19
25
```

第⼀⾏的表⽰⽅法是 Python 中字节串的表⽰，第⼆⾏是 16 进制表⽰。1 字节（byte）= 8bit

16 进制 0a 化为 2 进制是 0000 1010，右 3 位 010 表⽰线类型是字符串，其他位 00001 代表字段是 1

protobuf 标记格式：`(字段号 << 3) | 线类型`

常⻅线类型：

- **0**：Varint（整数类型），长度可变
- **1**：64 位
- **2**：⻓度前缀的字符串或字节数组
- **3**：开始嵌套消息
- **4**：结束嵌套消息
- **5**：32 位

05 表⽰字符串的⻓度是 5 个字节，41 是 A 的 UTF-8 编码

### protobuf 其他⽤法

- `//`：添加注释
- **package**：包声明，防⽌不同项⽬之间命名冲突

**数据类型**

常⻅的数据类型：bool、int32、int64、float、double、string、enum（枚举）

message（消息）可以嵌套 message

"=1"、"=2"的数字表⽰该字段的唯⼀标签，1-15 ⽤于最频繁使⽤的字段（占⽤空间少）

**数据类型之前的修饰符有**：

- **optional**：该字段是可选的，可以设置它的值，也可以不设置它的值。如果不设置它的值，那么在访问字段的值时返回默认值
- **repeated**：这个字段可以重复多次（可以是 0 次），保存了重复的先后顺序，repeated 是⼀个动态数组

```protobuf
syntax = "proto3";
package tutorial;

message Person {
    optional string name = 1;
    optional int32 id = 2;
    optional string email = 3;

    enum PhoneType {
        PHONE_TYPE_UNSPECIFIED = 0;
        PHONE_TYPE_MOBILE = 1;
        PHONE_TYPE_HOME = 2;
        PHONE_TYPE_WORK = 3;
    }

    message PhoneNumber {
        optional string number = 1;
        optional PhoneType type = 2;
    }
    
    repeated PhoneNumber phones = 4;
}

message AddressBook {
    repeated Person people = 1;
}
```
