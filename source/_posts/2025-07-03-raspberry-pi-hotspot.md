---
title: 树莓派热点设置教程
date: 2025-07-03 20:08:00 +0800
categories: [Learning, Embedded, Platform, RaspberryPi]
tags: [raspberry-pi, embedded, Linux]
description: 树莓派开启 Wi-Fi 热点的设置教程
toc: true
comments: true
---

## 开启热点

要先关闭 NetworkManager：

```bash
sudo systemctl stop NetworkManager
```

### 步骤

#### 1. 安装必要的软件包

```bash
sudo apt-get update
sudo apt-get install hostapd dnsmasq
```

#### 2. 配置网络接口

编辑 `/etc/dhcpcd.conf` 文件来设置静态 IP 地址给你的热点：

```bash
sudo nano /etc/dhcpcd.conf
```

添加以下内容：

```
interface wlan0
static ip_address=192.168.4.1/24
nohook wpa_supplicant
```

#### 3. 配置 DHCP 服务器

编辑 `/etc/dnsmasq.d/custom.conf` 文件：

```bash
sudo nano /etc/dnsmasq.d/custom.conf
```

增加以下内容：

```
interface=wlan0
dhcp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h
```

#### 4. 配置 hostapd

创建并编辑 `/etc/hostapd/hostapd.conf` 文件：

```bash
sudo nano /etc/hostapd/hostapd.conf
```

输入以下内容，并根据需要修改 SSID 和密码：

```
interface=wlan0
driver=nl80211
ssid=YourHotspotName
hw_mode=g
channel=7
wmm_enabled=0
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=YourHotspotPassword
wpa_key_mgmt=WPA-PSK
rsn_pairwise=CCMP
```

然后编辑 `/etc/default/hostapd` 来指定配置文件的位置：

```bash
sudo nano /etc/default/hostapd
```

找到 `#DAEMON_CONF=""` 并更改为：

```
DAEMON_CONF="/etc/hostapd/hostapd.conf"
```

#### 5. 重启服务

最后，重启 `dhcpcd`、`dnsmasq` 和 `hostapd` 服务来应用更改：

```bash
sudo systemctl restart dhcpcd
sudo systemctl restart dnsmasq
sudo systemctl start hostapd
```

## 设置开机自启

```bash
sudo systemctl enable hostapd
sudo systemctl enable dnsmasq
```
