---
title: ESP32 驱动无源蜂鸣器播放音乐
date: 2025-09-03 21:04:00 +0800
categories: [Learning, Embedded, Platform, ESP32]
tags: [ESP32, embedded, music, Arduino, midi]
description: 使用 ESP32 驱动无源蜂鸣器并播放音乐的完整教程，包含简谱和 MIDI 文件转换方法
toc: true
---

# 【Arduino】ESP32 驱动无源蜂鸣器并播放音乐

## 一、前言

### 1.1 无源蜂鸣器

有关蜂鸣器的介绍可参考

- [有源蜂鸣器与无源蜂鸣器的驱动方式详解](https://blog.csdn.net/chenhuanqiangqiangnihao/article/details/113384991)
- [电子电路学习笔记（17）——蜂鸣器](https://blog.csdn.net/qq_36347513/article/details/121474727)

市面上的无源蜂鸣器有很多种，有直插的，也有 SMD 贴片的，出于尺寸考虑，我选择了贴片的

![蜂鸣器](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E8%9C%82%E9%B8%A3%E5%99%A8.jpg)
_无源蜂鸣器 MLT-7525_

驱动电路如![蜂鸣器驱动](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E8%9C%82%E9%B8%A3%E5%99%A8%E9%A9%B1%E5%8A%A8.png)图，其中 BUZZER 接到了 ESP32-C3 的 GPIO5 上


_蜂鸣器驱动电路_

### 1.2 ESP32-C3 驱动蜂鸣器

Arduino IDE 中，驱动无源蜂鸣器十分简单，使用函数

```c++
tone(BUZZER_PIN, freq, time)
```

即可，第一个参数是 GPIO 编号，第二个是频率，第三个是持续时间，下面是测试程序

```c++
#define BUZZER_PIN 5  // GPIO5 作为蜂鸣器引脚

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);  // 设置引脚为输出模式
  Serial.begin(115200);         // 串口初始化，用于调试
  Serial.println("无源蜂鸣器测试程序启动");  // 输出中文提示
}

void loop() {
  // 测试简单音阶：Do-Re-Mi-Fa-So-La-Si-Do
  tone(BUZZER_PIN, 262, 500);  // Do (C4)，持续 500ms
  delay(500);
  tone(BUZZER_PIN, 294, 500);  // Re (D4)
  delay(500);
  tone(BUZZER_PIN, 330, 500);  // Mi (E4)
  delay(500);
  tone(BUZZER_PIN, 349, 500);  // Fa (F4)
  delay(500);
  tone(BUZZER_PIN, 392, 500);  // So (G4)
  delay(500);
  tone(BUZZER_PIN, 440, 500);  // La (A4)
  delay(500);
  tone(BUZZER_PIN, 494, 500);  // Si (B4)
  delay(500;
  tone(BUZZER_PIN, 523, 500);  // Do (C5)
  delay(500);

  noTone(BUZZER_PIN);  // 停止蜂鸣
  Serial.println("一轮音阶测试完成");  // 调试输出

  delay(2000);  // 每轮测试后暂停 2 秒
}
```

## 二、播放音乐

### 2.1 音乐数据获取

#### 根据简谱编写数组

简谱可以上网找，一般都可以找到，这里以《遇见》为例

![遇见](https://photos-1355819942.cos.ap-shanghai.myqcloud.com/undefined%E9%81%87%E8%A7%81.jpg)
_《遇见》简谱_

我的乐理知识很匮乏，所以只简单的说明如何根据简谱获取每个音的频率和时间

##### 频率

```c++
#define P0 	0	// 休止符频率

#define L1 262  // 低音频率
#define L2 294
#define L3 330
#define L4 349
#define L5 392
#define L6 440
#define L7 494

#define M1 523  // 中音频率
#define M2 587
#define M3 659
#define M4 698
#define M5 784
#define M6 880
#define M7 988

#define H1 1047 // 高音频率
#define H2 1175
#define H3 1319
#define H4 1397
#define H5 1568
#define H6 1760
#define H7 1976
```

一个音符的频率取决于数字的大小和上下点的情况

- 数字上下都没有点的，频率是 M1-M7，取决于具体数字，是几就是 M 几
- 数字上面有点的，频率是 H1-H7(H=High)，取决于具体数字，是几就是 H 几
- 数字下面有点的，频率是 L1-L7(L=Low)，取决于具体数字，是几就是 L 几

##### 时间

$\frac{4}{4}$ 表示 4 分音符为 1 拍，每小节 4 拍

由每分钟 92 拍，推算每拍的时长为

60*1000 / 92 = 652ms

- 全音符：X---，四拍
- 半音符：X-，两拍
- 四分音符：X，一拍
- 数字下面加上一个横线时长就减一半
- 浮点：中间的点，延长前面的一半

由此，可以推算每个音符的时长和频率，填入数组

```c++
const int melody_yu_jian[] PROGMEM={
    M5,M3,L1,L5,M5,M2,//......
}
const int durations_yu_jian[] PROGMEM={
    652/2,652/2,652/2,652/2,652/2,652/2
}
```

`PROGMEM`=**Program Memory**，为了节省 SRAM 来将数据存储到 FLASH 里面

可以参考视频 [零基础简谱入门教学](https://www.bilibili.com/video/BV1M1421k7gu/)，进行更深度的乐理知识学习

#### 把 MIDI 文件转换成数组

上面的方法实在是过于繁琐且枯燥，还容易出错，所以我了解到另外一种方法

##### MIDI 文件简介

MIDI 文件不包含真实的音频信息，而是记录了乐器演奏的指令，比如什么时候哪个键被按下，弹奏的是哪个音符，音量有多大等等。这就像是一个乐谱，告诉乐器应该如何表演，但没有实际的声音。这正好能满足使用蜂鸣器播放的需求

##### MIDI 文件获取

下面这个网站可以免费获取一首，然后支持五块钱可以在 5 天内免费下载 20 首，差不多够用了

- [MidiShow - 领先的 MIDI 音乐交流与下载网站](https://www.midishow.com/)

如果不够用的话，可以在油猴脚本里面找一找免费下载的脚本

https://greasyfork.org/zh-CN/scripts/544111-midishowdownload

##### 歌曲的选择

> [!TIP]
> 注意蜂鸣器播放声音和喇叭差别还是很大的，尽量选择旋律好听的歌曲

##### MIDI 文件编辑

有了 MIDI 文件之后，会发现大部分文件都有好几个音轨，而一个蜂鸣器在同一个时间只能播放一种声音，所以需要使用在线编辑工具 [Online Sequencer](https://onlinesequencer.net/)，来保证每一时间只有一个音符，否则会导致导出数组时本来应该在同一时间播放的多个音符变成了按顺序播放，造成蜂鸣器播放的混乱。

因为同一时间只有一个音符，所以需要找到主旋律，一般来讲最高的是主旋律，但也不一定，需要根据实际情况调整，这一步往往最为麻烦

右键删除音符，在选择模式下可以批量选中

##### MIDI 文件转换成 C 数组

Python 脚本 (由 DeepSeek 生成，实测可用)

{% raw %}
```python
import mido
import os
import re

def sanitize_c_identifier(name):
    """将字符串转换为合法的 C 标识符"""
    name = re.sub(r'[^a-zA-Z0-9_]', '_', name)
    if name and name[0].isdigit():
        name = '_' + name
    return name

def midi_to_c_array(filename):
    try:
        mid = mido.MidiFile(filename)
    except Exception as e:
        print(f"Error opening MIDI file {filename}: {e}")
        return

    melody = []      # 频率数组，0 表示停顿
    durations = []   # 持续时间（毫秒）

    ticks_per_beat = mid.ticks_per_beat if mid.ticks_per_beat else 480
    tempo = 500000  # 默认 120 BPM

    # 获取第一个 set_tempo 事件
    for track in mid.tracks:
        for msg in track:
            if msg.type == 'set_tempo' and msg.is_meta:
                tempo = msg.tempo
                break
        if tempo != 500000:
            break

    # 合并所有 track 的消息，并按时间排序
    events = []
    for track in mid.tracks:
        absolute_time = 0
        for msg in track:
            absolute_time += msg.time
            if msg.type in ('note_on', 'note_off') or (msg.type == 'note_on' and msg.velocity == 0):
                events.append({'time': absolute_time, 'message': msg})

    events.sort(key=lambda x: x['time'])  # 按时间排序

    active_notes = {}  # (note, channel) -> start_tick
    current_time = 0   # 当前时间（ticks）
    first_note_played = False  # 标志：是否已播放第一个音符

    for event in events:
        tick = event['time']
        msg = event['message']

        # === 计算当前时间和上一个事件之间的空白 ===
        gap_ticks = tick - current_time
        if gap_ticks > 0 and len(active_notes) == 0:
            gap_ms = int(mido.tick2second(gap_ticks, ticks_per_beat, tempo) * 1000)

            # 只有在第一个音符之后，且时长 ≤ 5000ms 才记录空白
            if first_note_played and gap_ms <= 5000:
                melody.append(0)
                durations.append(gap_ms)
            # 如果还没开始，且有空白，跳过（不记录开头空白）

        current_time = tick

        # === 处理 note_on ===
        if msg.type == 'note_on' and msg.velocity > 0:
            key = (msg.note, msg.channel)
            if key not in active_notes:
                active_notes[key] = tick

        # === 处理 note_off 或 note_on velocity=0 ===
        elif msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0):
            key = (msg.note, msg.channel)
            if key in active_notes:
                start_tick = active_notes.pop(key)
                note_duration_ticks = tick - start_tick
                note_duration_ms = int(mido.tick2second(note_duration_ticks, ticks_per_beat, tempo) * 1000)

                frequency = int(440 * (2 ** ((msg.note - 69) / 12)))
                melody.append(frequency)
                durations.append(note_duration_ms)

                # 标记已播放第一个音符
                if not first_note_played:
                    first_note_played = True

    if not melody:
        print(f"Warning: No notes or valid rests found in {filename}")
        return

    # === 生成唯一数组名 ===
    base_name = os.path.splitext(os.path.basename(filename))[0]
    safe_name = sanitize_c_identifier(base_name.lower())
    melody_array_name = f"melody_{safe_name}"
    durations_array_name = f"durations_{safe_name}"

    # === 写入头文件 ===
    output_filename = f"{base_name}.h"
    try:
        with open(output_filename, 'w') as f:
            f.write(f"// Generated from {filename}\n")
            f.write(f"// Song length: {len(melody)} events (notes + rests)\n")
            f.write(f"// Skipped leading rests and rests > 5000ms\n\n")

            # 旋律数组
            f.write(f"static const int {melody_array_name}[] PROGMEM = {{\n")
            for i, note in enumerate(melody):
                f.write(f"  {note},")
                if (i + 1) % 10 == 0:
                    f.write("\n")
                else:
                    f.write(" ")
            f.write("\n};\n\n")

            # 时长数组
            f.write(f"const int {durations_array_name}[] PROGMEM = {{\n")
            for i, duration in enumerate(durations):
                f.write(f"  {duration},")
                if (i + 1) % 10 == 0:
                    f.write("\n")
                else:
                    f.write(" ")
            f.write("\n};\n")

            # 长度宏
            f.write(f"\n#define MELODY_{safe_name.upper()}_LENGTH {len(melody)}\n")

        print(f"✅ Successfully wrote: {output_filename} ({len(melody)} events)")
        print(f"   Arrays: {melody_array_name}[], {durations_array_name}[]")
        if not any(melody):  # 全是 0？
            print("   ⚠️  Warning: melody contains only rests or low notes")
    except Exception as e:
        print(f"❌ Error writing {output_filename}: {e}")

# ========================
# Main Execution
# ========================
if __name__ == "__main__":
    current_dir = "."
    midi_files = [f for f in os.listdir(current_dir) if f.lower().endswith(('.mid', '.midi'))]

    if not midi_files:
        print("No MIDI files found in the current directory.")
    else:
        print(f"Found {len(midi_files)} MIDI file(s):")
        for f in midi_files:
            print(f"  → {f}")
        print("-" * 40)

        for midi_file in midi_files:
            midi_to_c_array(midi_file)
```
{% endraw %}

把 `.mid` 文件和这个脚本放入同一目录，把该脚本保存为 `midi_to_c_array.py`，按照教程安装 Python，打开 cmd，输入

```bash
pip install mido
python midi_to_c_array.py
```

即可在当前目录查看生成的 `.h` 文件，有两个数组，包含每个音符的频率和时间数据

### 2.2 播放音乐

每次都调用 `tone` 函数播放每个音符的频率和时间即可

```c++
#include "Music_processed/cai_bu_tou.h"
#include "Music_processed/cheng_du.h"
#include "Music_processed/hai_kuo_tian_kong.h"
#include "Music_processed/hong_dou.h"
#include "Music_processed/hou_lai.h"
#include "Music_processed/kai_shi_dong_le.h"
#include "Music_processed/lv_se.h"
#include "Music_processed/qing_hua_ci.h"
#include "Music_processed/xin_qiang.h"
#include "Music_processed/you_dian_tian.h"
#include "Music_processed/chun_jiao_yu_zhi_ming.h"
#include "Music_processed/Windows.h"
#include "Music_processed/mi_ren_de_wei_xian.h"

// 定义蜂鸣器连接的引脚
#define BUZZER_PIN 5 // 请根据您的硬件连接修改此引脚号

// 定义 Song 结构体
typedef struct {
  const char* name;
  const int* melody;
  const int* durations;
  int length;
} Song;


const Song songs[] PROGMEM= {
  { "Cai Bu Tou", melody_cai_bu_tou, durations_cai_bu_tou, sizeof(melody_cai_bu_tou) / sizeof(melody_cai_bu_tou[0]), 0 },
  {"Chun Jiao Yu Zhi Ming",melody_chun_jiao_yu_zhi_ming,durations_chun_jiao_yu_zhi_ming,sizeof(melody_chun_jiao_yu_zhi_ming)/sizeof(melody_chun_jiao_yu_zhi_ming[0]),1},
  { "Cheng Du", melody_cheng_du, durations_cheng_du, sizeof(melody_cheng_du)/sizeof(melody_cheng_du[0]), 2 },
  {"Hai Kuo Tian Kong",melody_hai_kuo_tian_kong,durations_hai_kuo_tian_kong, sizeof(melody_hai_kuo_tian_kong)/sizeof(melody_hai_kuo_tian_kong[0]), 3 },
  { "Hong Dou", melody_hong_dou, durations_hong_dou, sizeof(melody_hong_dou)/sizeof(melody_hong_dou[0]), 4 },
  { "Hou Lai", melody_hou_lai, durations_hou_lai, sizeof(melody_hou_lai)/sizeof(melody_hou_lai[0]), 0 },
  { "Kai Shi Dong Le", melody_kai_shi_dong_le, durations_kai_shi_dong_le, sizeof(melody_kai_shi_dong_le)/sizeof(melody_kai_shi_dong_le[0]), 1 },
  { "Lv Se", melody_lv_se, durations_lv_se, sizeof(melody_lv_se)/sizeof(melody_lv_se[0]), 2 },
  {"Mi Ren De Wei Xian",melody_mi_ren_de_wei_xian,durations_mi_ren_de_wei_xian,sizeof(melody_mi_ren_de_wei_xian)/sizeof(melody_mi_ren_de_wei_xian[0]),3},
  { "Qing Hua Ci", melody_qing_hua_ci, durations_qing_hua_ci, sizeof(melody_qing_hua_ci)/sizeof(melody_qing_hua_ci[0]), 3 },
  { "Xin Qiang", melody_xin_qiang, durations_xin_qiang,sizeof(melody_xin_qiang)/sizeof(melody_xin_qiang[0]), 4 },
  { "You Dian Tian", melody_you_dian_tian, durations_you_dian_tian, sizeof(melody_you_dian_tian)/sizeof(melody_you_dian_tian[0]), 0 },
  {"Windows XP",melody_windows,durations_windows,sizeof(melody_windows) / sizeof(melody_windows[0]),3},
};
const int numSongs = sizeof(songs) / sizeof(songs[0]);

// 播放音乐函数
void playSong(int songIndex) {
  // 检查索引是否有效
  if (songIndex < 0 || songIndex >= numSongs) {
    Serial.print("Invalid song index: ");
    Serial.println(songIndex);
    return;
  }

  Song song;
  memcpy_P(&song, &songs[songIndex], sizeof(Song));

  Serial.print("Playing song: ");
  Serial.println(song.name);

  // 播放旋律
  for (int i = 0; i < song.length; i++) {
    // 从 PROGMEM 读取音符和持续时间
    int note = pgm_read_word(&(song.melody[i]));
    int duration = pgm_read_word(&(song.durations[i]));

    Serial.print("Note: ");
    Serial.print(note);
    Serial.print(", Duration: ");
    Serial.println(duration);

    // 播放音符
    tone(BUZZER_PIN, note, duration);

    // 等待音符播放完成，并留一点间隔
    delay(duration * 1.1); // 增加 10% 间隔时间

    // 确保蜂鸣器在下一个音符前关闭
    noTone(BUZZER_PIN);
  }

  Serial.print("Finished playing song: ");
  Serial.println(song.name);
}

void setup() {
  // 初始化串口监视器
  Serial.begin(115200);
  Serial.println("Buzzer Music Player Started");

  // 设置蜂鸣器引脚为输出
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // 循环播放所有歌曲
  for (int i = 0; i < numSongs; i++) {
    playSong(i);
    delay(1000); // 每首歌之间暂停 1 秒
  }
  Serial.println("All songs played once. Restarting...");
  delay(2000); // 全部播放完后暂停 2 秒再重新开始
}
```

