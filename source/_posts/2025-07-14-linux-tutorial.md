---
title: Linux 入门教程
date: 2025-07-14 15:19:00 +0800
categories: [Learning, Tools]
tags: [Linux]
description: Linux 入门教程，包含 Shell 介绍、系统目录结构、文件操作、用户管理等核心概念
toc: true
---

# Linux 入门教程

# Linux

## Shell的简要介绍

​	操作系统主要负责系统内存管理、软件程序管理、硬件设备管理和文件系统管理。在用户与操作系统之间需要应用程序作为桥梁，帮助用户与操作系统进行交互，实现各种功能。
  应用程序与用户的交互有两种表现形式，一种是我们常见的 GUI（Graphical User Interface），即图形用户界面，可以用鼠标点击操作；另一种是 CLI（Command Line Interface），即命令行界面。
  Terminal，终端，是人与计算机进行交互的接口。一台大型机可以连接很多终端机，用户在这些终端机上跟计算机进行交互，这些早期终端一般是电传打字机（TTY）。随着个人计算机的普及和进化，大型机时代的专门的终端硬件早已消失，我们只用自己的键盘、鼠标来控制计算机。但是终端的思想保留了下来，变成了操作系统中的软件——终端模拟器（如Win32控制台）。终端模拟器可以捕获你的键盘输入，发送至命令行程序，拿到输出结果后再调用图形接口，将输出渲染至屏幕上。由于人们除了在博物馆再也见不到TTY这样的终端硬件了，于是就直接称终端模拟器为终端。
  Shell，即“壳层”，是帮助用户与内核交互的一类程序。操作系统内核直接负责管理计算机硬件，处于操作系统最底层，由于其重要性是不能轻易由用户直接操作的，因此需要有Shell程序来作为用户操作系统的入口。Shell是一类程序，可以有CLI形式的（如sh、bash、zsh；cmd、powershell等），也可以有GUI形式的（如Windows资源管理器explorer.exe等）。
  用户所看见的界面通常是终端，在用户用键盘和鼠标输入后，终端（Terminal）将这些输入发送给你选用的壳层（Shell），Shell解析你的命令发送给操作系统内核去执行，并把执行结果返回给终端，终端调用图形接口将结果显示到屏幕上。  

## Linux系统目录结构  

### 系统文件

`/boot`存放着启动 Linux 时使用的内核文件，包括连接文件以及镜像文件。
`/etc`存放所有的系统需要的配置文件和子目录列表。
`/lib`存放基本代码库（比如 c++库），几乎所有的应用程序都需要用到这些共享库。
`/sys` 该目录下安装了 Linux2.6 内核中新出现的一个文件系统 sysfs ，当一个内核对象被创建的时候，对应的文件和目录也在内核对象子系统中。

### 指令/程序（文件）

`/bin`存放着最常用的程序和指令。
`/sbin`只有系统管理员能使用的程序和指令。

### 外部设备（文件）

`/dev`Device 的缩写，存放的是 Linux 的外部设备。

> [!NOTE]
在 Linux 中访问设备和访问文件的方式是相同

`/media`类 windows 的**其他设备，**例如 U 盘、光驱等等，识别后 linux 会把设备放到这个目录下。
`/mnt`用于临时挂载别的文件系统.

### 临时文件

`/run`是一个临时文件系统，存储系统启动以来的信息。
`/lost+found`一般情况下为空的，系统非法关机后，这里就存放一些文件。
`/tmp`这个目录是用来存放一些临时文件的。

### 账户文件

`/root`系统管理员的用户主目录。
`/home`用户的主目录，以用户的账号命名。
`/usr`用户的很多应用程序和文件都放在这个目录下，类似于 Windows 下的 program files 目录。
`/usr/bin`系统用户使用的应用程序与指令。
`/usr/sbin`超级用户使用的比较高级的管理程序和系统守护程序。
`/usr/src`内核源代码默认的放置目录。

### 程序运行中文件

`/var`存放经常修改的数据，比如程序运行的日志文件（/var/log 目录下）。
`/proc`管理内存空间虚拟的目录，是系统内存的映射，我们可以直接访问这个目录来获取系统信息。这个目录的内容不在硬盘上而是在内存里，我们也可以直接修改里面的某些文件来做修改。  

## Linux文件操作

### 文件绝对路径

在Windows中，会见到这样的文件路径：`C:\Windows\System32\drivers\etc\hosts`，它指向位于C盘中，Windows\System32\drivers\etc\文件夹下的hosts文件
 而在Linux中，文件系统为树状结构，文件路径中并没有驱动器盘符，而是以虚拟目录的形式，将计算机所有的存储设备中的文件路径纳入统一的单一目录下，该目录称之为根目录。 

### ls命令

```bash
ls [options] [directory name]
列出directory name下的文件和目录，按照字母排序
options:
-a 显示所有文件及目录(“.”开头的隐藏文件也会列出)
-l 除文件名称外，亦将文件型态、权限、拥有者、文件大小等资讯详细列出(详见[权限部分](#ls))
-r 将文件以相反次序显示(原定依英文字母次序)
-t 将文件依建立时间之先后次序列出
-A 同 -a ，但不列出 "." (目前目录) 及 ".." (父目录)
-F 在列出的文件名称后加一符号；例如可执行档则加 "*", 目录则加 "/"
-R 若目录下有文件，则以下之文件亦皆依序列出  
```

在控制台中输入ls /，可以看到根目录下有许多子目录.在虚拟目录支持下，Linux下文件路径如下: `/etc/apt/sources.list`，它指向`/etc/apt/`文件夹下的sources.list，这个文件是apt的更新源配置文件，通常情况下需要将该文件配置为国内源，以加快Ubuntu系统的更新速度  

例如，设置成清华镜像站

```
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-backports main restricted universe multiverse

# 以下安全更新软件源包含了官方源与镜像站配置，如有需要可自行修改注释切换
deb http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse
# deb-src http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-proposed main restricted universe multiverse
# # deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ noble-proposed main restricted universe multiverse
```

> [!NOTE]
>
> 设置之前注意备份

### 其他文件路径

上面讲到了文件的绝对路径，在实际使用中还常常用到相对路径，除目录分隔符不同外，相对路径语法全系统通用，`.`表示当前目录，`..`表示父目录。考虑当前目录为`/etc/apt/`，则`./sources.list=/etc/apt/sources.list`，`../hosts=/etc/hosts`。
除此之外，当前用户的个人文件夹(通常为/home/[username]/)可以用特殊字符`~`表示。

`cd [path]`指令修改当前目录到path指定的位置，无参数时path默认值为~。使用TAB键可以自动补全目录名称。
`pwd`指令可以打印当前目录的绝对路径。
`which [command]`指令可以打印命令对应可执行文件的路径 

### 目录与文件操作  

#### 创建操作

`mkdir [-p] [directory name]`: 创建目录，-p指令可以自动创建缺失的父文件夹。
`touch [file name]`: 创建空文件，如果已经存在，则更新文件修改时间为当前时间。

#### 复制与移动操作

```bash
cp [options] [source] [destination]
复制source到destination
options:
-f: 冲突时强制覆盖目标
-n: 冲突时不覆盖目标
-u: 冲突时覆盖修改时间较旧的目标
-i: 发生冲突时询问是否覆盖
-r: 递归复制(用于复制目录)
-s: 创建符号链接(可以理解为快捷方式)而非复制
```

-n比较安全  

`mv`指令用于移动，[options]与cp指令类似，当然除-s外，文件都移动走了创建符号链接也没什么意义。

#### 删除操作

```bash
rm [options] [target]: 删除target
options:
-f：不需要确认，直接删除
-i：系统会在删除每个文件之前提示用户确认是否真的要删除该文件
-r：用于删除文件夹
-v: 详细报告删除过程
--：表示参数结束，之后的所有参数都被视为文件名，即使它们以 - 开头。这对于删除名称以 - 开头的文件非常有用。
```

> [!TIP]
>
> 多个命令选项可以合写，如rm -rf=rm -r -f

> [!WARNING]
> shell中没有回收站，文件一旦删除将无法恢复！谨慎使用rm -rf！

#### 查找操作

```bash
find [directories] [options]
在指定目录下查找符合要求的文件
options:
-name [name]: 文件名查找，支持通配符，-iname会忽略大小写
-type [type]: 按文件类型查找，f(普通文件),d(目录)等
-path [p]: 路径符合p的文件
-amin [-n]: 在过去n分钟内被读取过的文件
-size [+nM]: 大小大于nM的文件  
-size [-nM]: 大小小于nM的文件  
```

### 文件显示与编辑

  在shell中，显示文件通常使用cat、more和less指令。`cat [filename]`会将文件内所有内容打印到控制台，在云服务器和管道处理场景下更加便捷。而more和less有着更优秀的互动机制，在日常本机使用中更加推荐使用less。
  vim有三种模式: 命令模式、输入模式和底线命令模式。使用vim指令打开文件时默认进入命令模式，在该模式下可以输入命令，如：输入i将切换到输入模式，对文件进行编辑；输入:将切换到底线命令模式，该模式下输入wq保存并退出，输入q!放弃修改并退出。在其他两种模式下输入Esc将回到命令模式。  

### vim的使用

`xdg-open` 找到合适的程序打开一个文件

在vim里面，在normal模式下，

按`i`进入插入模式

按`R`进入替换模式

按`V`进入查看模式

按`Shift`+`V`进入逐行查看模式

`F`+`字母`光标跳转到第一个出现这个字母的地方

`x`删除字母

`A`追加字母

`d`+`$`删除到行尾

`dd`删除整行

`w`下一个单词开始

`b`上一个单词

`3w`走三个单词

`e`这个单词结束

`0`回到开头

`Ctrl`+`R`重做

`u`撤销

`U`撤销整行

`p`粘贴刚刚删掉的行

`r`+`任意字符`将被光标选中的替换为`任意字符`

`ce`删除并替换单词

`c$`删除并替换到行末

`Ctrl`+`G`查看当前位置

`G`到文章结尾

`gg`到文章开头

`数字`+`G`到`数字`那行

`/+字符串`查找，`n`找到的下一个,`N`找到的上一个，`?+字符串`从末尾开始查找

光标在(,[,{上时按`%`跳转到和它配对的那个

替换：`:s/thee/the`把光标之后的第一个`thee`变成`the`

`:s/thee/the/g`把光标那一行的`thee`变成`the`

`1,3s/thee/the/g`1-33行的替换

`%s/thee/the/g`全文的都替换

`%s/thee/the/gc`全文每一个都询问是否替换

vim中运行命令:`:!+命令`

`:w TEST`把当前文件存入TEST

`v`进入选择模式，选中后按`:`，`w`+`文件名`把选中部分写入文件

`:r +文件名或者！指令`可以把内容读进来

`R`进入替换模式

`y`复制选中的

`p`粘贴

```markdown
  1. 输入小写的 o 可以在光标下方打开新的一行并进入插入模式。输入大写的 O 可以在光标上方打开新的一行。

  2. 输入小写的 a 可以在光标所在位置之后插入文本。
     输入大写的 A 可以在光标所在行的行末之后插入文本。

  3. e 命令可以使光标移动到单词末尾。

  4. 操作符 y 复制文本，p 粘贴先前复制的文本。

  5. 输入大写的 R 将进入替换模式，直至按 <ESC> 键回到正常模式。

  6. 输入 :set xxx 可以设置 xxx 选项。一些有用的选项如下：

  'ic' 'ignorecase'	查找时忽略字母大小写

  'is' 'incsearch'	查找短语时显示部分匹配

  'hls' 'hlsearch'	高亮显示所有的匹配短语

  选项名可以用完整版本，也可以用缩略版本。

  7. 在选项前加上 no 可以关闭选项：:set noic

```

补全功能：

```markdown
  1. 请确保 Vim 不是在以兼容模式运行： :set nocp

  2. 查看一下当前目录下已经存在哪些文件，输入： :!ls   或者  :!dir

  3. 现在输入一个目录的起始部分，例如输入： :e

  4. 接着按 CTRL-D 键，Vim 会显示以 e 开始的命令的列表。

  5. 然后按 <TAB> 键，Vim 会补全命令为 :edit 。

  6. 现在添加一个空格，以及一个已有文件的文件名的起始部分，例如： :edit FIL

  7. 接着按 <TAB> 键，Vim 会补全文件名(如果它是惟一匹配的)。

  提示：补全对于许多命令都有效。只需尝试按 CTRL-D 和 <TAB>。它对于 :help 命令非常有用。
```

## Linux用户管理

​	Linux是一个多用户系统，在多用户同时使用服务器时这一点体现尤为明显。每个用户账号都拥有一个唯一的用户名和密码。用户在登录时键入正确的用户名和密码后，会进入自己的主目录。
  每个用户都有独立的文件访问权限。为了方便管理，可以将共享部分权限的用户分为一组，用户未特别指定的权限继承所在用户组权限。每个用户的UID和用户组的GID都是唯一的。一般情况下，Linux中有一个超级用户root，该用户拥有最高权限。

### 用root权限执行命令

  对用户和用户组的操作都是敏感操作，本小节用到的所有指令都无法在用户正常权限下执行，需要保证当前用户在sudoer组内(一般情况下均满足)并使用root权限执行命令。命令格式为：sudo [command]。输入该命令后需要输入用户密码以进一步操作。如果觉得sudo过于繁琐，也可以直接登录root进行操作，不过请谨慎使用root权限以避免系统的损坏。
  应当注意的是，用户需要至少在sudo组(或admin组)中才可以使用sudo命令。

### 用户操作

#### su

```bash
su [username]: 切换用户
```

#### useradd

```bash
(sudo) useradd [options] [username]: 创建用户
options:
-m: 创建用户主目录(配合-k [path]指定创建模板)
-d [dir]: 指定用户主目录位置
-e [YYYY-MM-DD]: 指定到期时间
-g [GID/groupname]: 指定用户登录组
-G [GIDs/groupnames]: 指定用户所在的附加组
-p [password]: 指定默认密码
-s [shell]: 指定用户登录的shell
-c [comment]: 指定用户备注
-D: 查看默认设置(单独使用)
```



#### passwd

```bash
passwd [options]: 修改自己密码，需要旧密码
(sudo) passwd [options] [username]: 修改别人密码
options:
-l/-u: 锁定/解锁密码；-d: 删除密码
-f: 下次登录时强制修改密码
```

#### usermod

```bash
(sudo) usermod [options] username
修改用户属性，options和useradd类似
如果需要让用户进入新的组，请使用-aG [GIDs/groupnames]
```

#### userdel

```bash
(sudo) userdel [options] username
删除用户，-r以删除用户主目录
```

在/etc/passwd文件中可以查看当前系统中的全部用户和属性，每行用户信息以:为分隔符，具体格式如下：

```bash
username:password(hidden):user id(UID):group id(GID):comment:home path:default shell
```

使用(sudo) visudo以编辑/etc/sudoer，可以配置哪些用户(组)可以使用sudo指令。权限配置格式如下：

```  
[用户名] [允许登录的主机]=([可使用的用户身份]:[可使用的组]) [可使用的命令]
例如%sudo ALL=(ALL:ALL) ALL
```


在这里还可以配置一些有趣的东西，比如添加Defaults pwfeedback可以让sudo密码输入时显示为星号。

### 用户组操作

  一个组中可以有多个用户，一个用户也可以在多个组中。 一个用户同时是多个组的成员时，用户主组(登录组)在/etc/passwd中记录，而其他组(附加组)在/etc/group中记录。后者数据格式如下：

```  
groupname:password(通常为空):GID:UIDs(仅显示附加组成员)
```

有关用户组的操作，常用的有groupadd、groupmod、groupdel。  newgrp [group]可以切换当前活动用户的主组，加上-选项后切换将引起shell重加载。 
groups [username]查看用户所在的所有组(主组第一个)

```
gpasswd [options] group: 管理附加组
options:
-a/-d [username]: 添加/删除用户到/从指定附加组
-M [usernames]: 为该附加组成员赋值
```

### 文件与用户/用户组权限

  在上面提到ls命令时，我们提了一嘴ls -l命令，现在我们来仔细查看ls -l返回的数据。

```bash  
drwxr-xr-x 2 dream admin 4096 Jul 19 21:05 test
```

第一段drwxr-xr-x表示文件类型和权限，d表示该文件为目录文件(l链接，-普通文件)，
r(read)/m(modify)/x(execute)每三位一组，分别代表属主权限/属组权限/其他用户权限。
第二段2表示有两个硬链接(参见第一条注释)指向该文件对应的节点。第三、四段分别表示文件属主和属组，剩余部分为

`[file size]` 

`[modify time]`

`[file name]`

#### chmod

```bash
chmod [-R] [u/g/o/a] [+/-/=] [r/w/x] [filename]
修改指定文件的权限。
-R用于目录文件，递归修改每个子文件。
u(user)/g(group)/o(others)/a(all)指定修改权限的对象。
+/-/=分别对应增加/减小/赋值权限。
如果把rwx看作3位2进制数，则可以通过以下方式快速赋值：
chmod 775 file，修改后权限变为rwxrwxr-x
(sudo) chown [-R] [owner][:group] [file]: 修改文件属主(及属组)
(sudo) chgrp [-R] [group] [file]: 仅修改属组
```

### 应用实例

新建一个用户并赋予超级用户权限，指定/home/sub/[用户名]/为home目录，设置默认shell为bash，并设置在输入密码时显示星号  

首先执行

```bash
sudo useradd -d /home/sub/user -s /usr/bin/bash user1
```

然后执行命令

```bash
sudo visudo
```

加入

```
%user1  ALL=(ALL:ALL) ALL
Defaults        pwfeedback
```



## Linux系统和磁盘管理

### 软件管理

在Debian和Ubuntu发行版当中，apt是一个软件包管理工具。我们可以通过它方便地实现软件包的安装、更新、删除等操作。运行apt需要超级用户权限。

```bash
(sudo) apt install: 安装软件包
(sudo) apt update: 列出可更新的软件清单
(sudo) apt upgrade: 升级可升级的软件包(缺省则为全部)
(sudo) apt list --installed/--all-versions: 列出所有已安装软件包(及版本信息)
(sudo) apt show: 显示指定软件包具体信息
(sudo) apt search: 搜索软件包
(sudo) apt remove: 移除指定软件包
(sudo) apt autoremove: 清除不再使用的依赖和库文件
```

### 系统管理

```bash
top [-d secs] [-n max] [-u user]: 指定刷新率工作的进程CPU与内存占用显示界面
ps [-a] [-u] [-x]: 列出(全部用户)的进程(及详细信息)(即使进程没有控制终端)
kill [-s signal] [-u username]/PID: 向指定进程/指定用户所有进程发送信号(默认为15-
SIGTERM，也可为9-SIGKILL，可通过kill -l查看)
```

### 磁盘管理

```bash
df [options] [path]: 列出path所在文件系统的整体磁盘使用量
options:
-h: 以GB/MB/KB等格式呈现，更易阅读
-a: 列出所有的文件系统
-T: 显示文件系统格式
```

```bash
du [options] [path]: 列出path的磁盘空间使用量
options: -h/-a同df，-s对目录仅显示总大小而非递归显示
```

```bash
(sudo) fdisk [-l] [device name]: 磁盘分区工具(根据引导即可)，-l列出所有分区
```

```bash
(sudo) mkfs [-t filesystem] [device name]: 格式化为指定文件系统格式
```

```bash
mount [device name] [directory]: 将文件系统挂载在指定目录下
unmount [device name or directory]: 卸载已挂载的文件系统
```

## Shell常用操作

### 输入输出重定向

```bash
command < file: 将文件内容作为命令输入
command [1/2/&][>/>>] file: 将标准输出流/错误流/两者输出到文件，>会覆盖已有文件，>>会追
加已有文件。如果不需要相关数据，file可以设为/dev/null
command 2>&1: 将标准错误流重定向到标准输出流
```

### 管道

```bash
command1 | command2
将command1的输出作为command2的输入
```

### 一些常用指令

#### grep

```bash
grep [options] 'patterns': 从标准输入流过滤行
options:
-A/-B/-C [n]: 除匹配行外额外向后(after)/向前(before)/前后(contest)显示n行
-c: 计算匹配行数
-r: 递归查找目录
-l: 列出匹配成功的文件名
-E: 使用拓展的正则表达式
-i: 忽略大小写
-n: 标出行号
-v: 反向选择
```

#### tr

```bash
tr [options] SET1 SET2: 将匹配SET1的字符修改为SET2
options:
-c: 反选字符集
-d: 删除匹配字符而非修改
-s: 缩减连续重复的字符成指定的单个字符
-t: 削减SET1范围使SET1和SET2长度相等
SET特殊值:
CHAR1-CHAR2 ：字符范围从 CHAR1 到 CHAR2 的指定，范围的指定以 ASCII 码的次序为基础，只能
由小到大，不能由大到小。
[CHAR*] ：这是 SET2 专用的设定，功能是重复指定的字符到与 SET1 相同长度为止
[CHAR*REPEAT] ：这也是 SET2 专用的设定，功能是重复指定的字符到设定的 REPEAT 次数为止
(REPEAT 的数字采 8 进位制计算，以 0 为开始)
[:alnum:] ：所有字母字符与数字
[:alpha:] ：所有字母字符
[:blank:] ：所有水平空格
[:cntrl:] ：所有控制字符
[:digit:] ：所有数字
[:graph:] ：所有可打印的字符(不包含空格符)
[:lower:] ：所有小写字母
[:print:] ：所有可打印的字符(包含空格符)
[:punct:] ：所有标点字符
[:space:] ：所有水平与垂直空格符
[:upper:] ：所有大写字母
[:xdigit:] ：所有 16 进位制的数字
例如: cat tfile | tr a-z A-Z > tout，将tfile中小写字符替换为大写字符并输出到tout
```

#### bc

```bash
bc: 任意精度计算器，对标准输入的数学表达式进行计算。
数学表达式中可以包含以下内容：
"scale=2;": 指定小数位为2位
"ibase=2;obase=16;": 指定输入为2进制数，输出为16进制数
```

#### ssh

```bash
ssh user@hostname -p port: 登录到SSH远程服务器
```

SSH = Secure Shell，即安全外壳协议，是为远程登录会话提供安全性的协议，一般用作远程登录到服务器  

## Shell脚本

Shell脚本是一种在Shell中运行的脚本程序，由Shell作为脚本解释器，Shell脚本的一行就相当于一个命令，
也可以用分号分隔一行之中的不同命令。 脚本后缀名通常为*.sh，在脚本第一行，通常需要注明脚本解释器的路径，如#!/bin/bash。下面是一个小示例  

```bash
#!/bin/bash
# 我是注释
a=1 # 定义变量，名称和值之间不能有空格
echo $a # $用于引用变量，也可用于引用环境变量
unset a # 删除变量
array=(0 1 2 3 4) # 定义数组
echo ${array[0]} # 读取数组元素
echo ${array[@]} # 读取数组所有元素
if condition1 then
command1
elif condition2 then
command2
else
commandN
fi
for var in array
do
command
done
# 仿C风格
for (( i = 1; i <= 10; i++ ))
do
command
done
while condition
do
command # 可以使用break, continue
done
function f1(){
echo "参数1: ${1}" # 通过${n}获取传入的第n个参量
return $(( ${1}+${10} ))
}
test 1 2 3
echo $? # $?指代函数的返回值或上条指令的输出结果
./sub1.sh # 直接调用sub1.sh
bash ./sub2.sh # 用bash作为解释器调用sub1.sh
```

### if else语句用法

#### if [];then fi语句

```bash
#!/bin/bash
a=$1
b=$2
if [ $a == $b ];then
   echo "a and b is equal"
fi
if [ $a != $b ];then
   echo "a and b is not equal"
fi
```

执行命令`sh test.sh 2 3`给参数$1和$2赋值2和3，输出结果`a and b is not equal`
不加else的if语句表达式成立执行then后面的语句，表达式不成立则不执行任何命令。

#### if [];then else fi语句

```bash
if [ expression ];then
    executed Statement_expression_true
    else
    executed Statement_expression_false
fi
```

> [!NOTE]
>
> expression表达式 和方括号`[ ]`之间必须有**空格**，否则会有语法错误

如果表达式成立，then后面的语句将会被执行；如果表达式不成立则执行else后面的语句。

#### if [];then elif []; then else fi语句

```bash
#!/bin/bash
a=$1
b=$2
if [ $a == $b ];then
   echo "a and b is equal"
elif [ $a -lt $b ];then
   echo "a less than b"
else
   echo "a bigger than b"  
fi
```

哪个expression表达式成立则执行哪个then后面的语句，否则执行else后面的语句。

if … else 语句也经常与 test 命令结合使用，test 命令用于检查某个条件是否成立，与方括号`[ ]`功能类似

```bash
#!/bin/bash
a=$1
b=$2
if test $a == $b;then
   echo "a and b is equal"
else
   echo "a and b is not equal"  
fi
```

例如上述脚本，其中`if test $a == $b;`与`if [ $a == $b ];`效果一样。

### if语句常用命令选项

`==` or `=`： 等于
`-eq` ： 等于
`-ne` ：不等于
`-gt` ：大于
`-ge` ：大于等于
`-lt` ：小于
`-le` ：小于等于

| 命令选项            | 描述                                   |
| ------------------- | -------------------------------------- |
| if [ a = b ]        | a与b是否相等 （a、b是数值）            |
| if [ a -ge b ]      | a 是否大于等于 b                       |
| if [ a -gt b ]      | a 是否大于 b                           |
| if [ a -le b ]      | a 是否小于等于 b                       |
| if [ a -lt b ]      | a 是否小于 b                           |
| if [ a -ne b ]      | a 是否不等于 b                         |
| if [ str1 = str2 ]  | str1是否与str2相同(str1、str2是字符串) |
| if [ str1 != str2 ] | str1是否与str2不同                     |
| if [ str1 < str2 ]  | str1是否小于str2                       |
| if [ str1 > str2 ]  | str1是否大于str2                       |
| if [ -n str ]       | 判断str长度是否非零                    |
| if [ -z str ]       | str长度是否为0                         |
| if [ -d file ]      | 判断file是否为一个目录                 |
| if [ -e file ]      | 判断file是否存在                       |
| if [ -f file ]      | 检查file文件是否存在                   |
| if [ -r file ]      | 判断file是否存在并可读                 |
| if [ -s file ]      | 判断file是否存在并非空                 |
| if [ -w file ]      | 判断file是否存在并可写                 |
| if [ -x file ]      | 判断file是否存在并可执行               |

例如下面脚本判断压缩包文件是否存在

```bash
  #!/bin/bash 
    Day=`date -d yesterday +%Y%m%d` 
    FILE=access_${Day}.log.tgz
    WORK_DIR= /data/nginx/logs
    if [ -f ${WORK_DIR}/${FILE} ];then 
     echo "OK" 
    else 
     echo "${FILE} backup fail" > error.log 
    fi
```

编写shell脚本，求出1到100的奇数和，并将结果重定向到result.txt  

```bash
#!/bin/bash
result=0
for ((i=1; i<=100; i++))
do
    if ((i % 2 != 0)); then
        result=$((result + i))
    fi
done
echo "$result" >> result.txt
```



## Shell环境变量

环境变量是存储有关 shell 的工作环境的数据，以便程序或 shell 中运行的脚本能够访问到它们。系统会创建好一些环境变量，我们在安装新程序等操作时也要留意是否需要设置环境变量，否则会出现"command not found"的错误。  

### 查看环境变量

```bash
env # 查看全部全局变量
printenv HOME # 查看个别全局变量（HOME）
echo $HOME # 查看个别全局变量（HOME
```

常用环境变量：

- HOME: 当前用户主目录
- PATH：shell查找命令的目录列表，由:分隔；
- PWD：当前工作目录  

### 设置环境变量

```bash
a=1
export a # 将子进程中变量公开给父进程(此处为shell)
```

然而，这种设置是临时的，一旦父进程退出，变量就会消失。为了设置持久的环境变量，我们就需要修改系统启动时用于加载环境变量的文件。这些文件有不同功能  

```bash
/etc/profile # 系统级，登录shell当中加载
/etc/bashrc # 系统级，可认为都会被加载
~/.profile # 用户级，登录shell当中加载
~/.bashrc # 用户级，可认为都会被加载
```

一般情况下只需要修改~/.bashrc即可。修改PATH时一般采用追加导出的方式，即在文件最后一行加上export PATH=[path to add]:$PATH。设置完成后，可以重启shell使设置生效，也可以使用source [file modified]重置当前shell全部环境变量  
