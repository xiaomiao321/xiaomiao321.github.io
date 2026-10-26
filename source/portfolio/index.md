---
title: Portfolio
date: 2026-10-25 22:00:00
comments: false
aside: false
top_img: false
---

<style>
.pf { --pf-line: rgba(127,127,127,.28); --pf-soft: rgba(127,127,127,.08); --pf-mute: #8a8f98; font-size: 16px; line-height: 1.7; }
.pf p { margin: 0 0 .6em; }
.pf a { text-decoration: none; }
.pf-hero { padding: 6px 0 18px; border-bottom: 1px solid var(--pf-line); margin-bottom: 22px; }
.pf-hero h1 { font-size: 2.2em; margin: 0 0 2px; border: 0; padding: 0; }
.pf-hero .pf-role { font-size: 1.2em; color: var(--pf-mute); margin-bottom: 12px; }
.pf-links { display: flex; flex-wrap: wrap; gap: 8px; margin-top: 12px; }
.pf-links a { display: inline-flex; align-items: center; gap: 7px; border: 1px solid var(--pf-line); border-radius: 999px; padding: 6px 16px; font-size: .95em; }
.pf-links a.pf-gh-main { background: #24292f; border-color: #24292f; color: #fff !important; font-weight: 600; }
[data-theme="dark"] .pf-links a.pf-gh-main { background: #f0f3f6; border-color: #f0f3f6; color: #1f2328 !important; }
.pf-ico { width: 1.1em; height: 1.1em; flex: none; }
a.pf-gh { display: inline-flex; align-items: center; gap: 5px; border: 1px solid var(--pf-line); border-radius: 999px; padding: 1px 10px; font-size: .95em; vertical-align: middle; }
a.pf-gh:hover, .pf-links a:hover { border-color: currentColor; }
.pf-chips { display: flex; flex-wrap: wrap; gap: 6px; margin: 6px 0; }
.pf-chip { background: var(--pf-soft); border: 1px solid var(--pf-line); border-radius: 4px; padding: 2px 10px; font-size: .85em; white-space: nowrap; }
.pf-badge { display: inline-block; border-radius: 4px; padding: 1px 9px; font-size: .82em; font-weight: 600; vertical-align: middle; }
.pf-ok { background: rgba(46,160,67,.16); color: #2ea043; }
.pf-wip { background: rgba(210,153,34,.18); color: #c38a12; }
.pf-design { background: rgba(56,139,253,.16); color: #388bfd; }
#page .page-title { display: none; }
.pf-grid { display: grid; grid-template-columns: repeat(5, 1fr); gap: 10px; margin: 10px 0 26px; }
@media (max-width: 900px) { .pf-grid { grid-template-columns: repeat(2, 1fr); } }
.pf-card { display: block; border: 1px solid var(--pf-line); border-radius: 8px; overflow: hidden; color: inherit !important; transition: transform .15s; }
.pf-card:hover { transform: translateY(-2px); }
.pf-card img { width: 100%; aspect-ratio: 4 / 3; object-fit: cover; margin: 0 !important; display: block; }
.pf-card div { padding: 8px 10px 10px; font-size: .95em; line-height: 1.4; }
.pf-card b { font-weight: 600; display: block; margin-bottom: 4px; }
.pf-proj { border: 1px solid var(--pf-line); border-radius: 10px; padding: 18px 20px 12px; margin: 0 0 22px; }
.pf-proj h2 { margin: 0 0 4px !important; padding: 0 !important; border: 0 !important; font-size: 1.55em; }
.pf-proj h2::before { display: none !important; }
.pf-meta { color: var(--pf-mute); font-size: .95em; margin-bottom: 8px; }
.pf-gal { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 10px; margin: 12px 0; }
.pf-gal4 { grid-template-columns: repeat(4, 1fr); }
.pf-gal3 { grid-template-columns: repeat(3, 1fr); }
@media (max-width: 760px) { .pf-gal4, .pf-gal3 { grid-template-columns: repeat(2, 1fr); } }
.pf-gal figure { margin: 0; }
.pf-gal img { width: 100%; border-radius: 6px; margin: 0 !important; }
.pf-gal figcaption { font-size: .86em; color: var(--pf-mute); text-align: center; margin-top: 3px; }
.pf-cols { display: grid; grid-template-columns: 1fr 1fr; gap: 18px; }
@media (max-width: 760px) { .pf-cols { grid-template-columns: 1fr; } .pf-proj { padding: 14px 12px 8px; } }
.pf h3 { font-size: .95em !important; margin: 10px 0 6px !important; color: var(--pf-mute); text-transform: uppercase; letter-spacing: .04em; }
.pf ul { margin: 0 0 8px; padding-left: 1.2em; }
.pf li { margin: 3px 0; font-size: 1em; }
.pf-note { background: var(--pf-soft); border-left: 3px solid #388bfd; border-radius: 4px; padding: 12px 16px; margin: 8px 0 10px; font-size: 1em; }
.pf-skills { display: grid; grid-template-columns: 130px 1fr; gap: 8px 14px; align-items: start; font-size: 1em; }
@media (max-width: 760px) { .pf-skills { grid-template-columns: 1fr; gap: 2px; } .pf-skills > span { margin-top: 8px; } }
.pf-skills > span, .pf-skills > div { font-size: 1em; line-height: 1.6; }
.pf-skills > span { color: var(--pf-mute); font-weight: 600; }
</style>

<div class="pf">
<div class="pf-hero">
<h1>Xiangyu Miao</h1>
<div class="pf-role">Embedded hardware and firmware</div>
<p>I am a junior in Electronic Science and Technology at Zhejiang University. I like owning a board from start to finish: schematic, layout, soldering, debugging, and then the firmware that runs on it. My most complete work so far is a fire-alarm controller delivered to a customer under contract, and a 4-layer motor controller for a robot prototype. I am looking for Summer 2027 internships in hardware design and embedded systems.</p>
<div class="pf-chips"><span class="pf-chip">U.S. citizen</span><span class="pf-chip">Graduating June 2028</span><span class="pf-chip">Available from June 29, 2027</span></div>
<div class="pf-links"><a class="pf-gh-main" href="https://github.com/xiaomiao321"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/></svg>github.com/xiaomiao321</a><a href="mailto:xiaomiao2026@gmail.com"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M1.75 2h12.5c.97 0 1.75.78 1.75 1.75v8.5A1.75 1.75 0 0114.25 14H1.75A1.75 1.75 0 010 12.25v-8.5C0 2.78.78 2 1.75 2zM1.5 5.06v7.19c0 .14.11.25.25.25h12.5c.14 0 .25-.11.25-.25V5.06L8.4 9.03a.75.75 0 01-.8 0L1.5 5.06zm13-1.4V3.75a.25.25 0 00-.25-.25H1.75a.25.25 0 00-.25.25v-.09L8 7.56l6.5-3.9z"/></svg>xiaomiao2026@gmail.com</a></div>
</div>

<div class="pf-grid">
<a class="pf-card" href="#lamp"><img src="img/lamp_real_top.jpg" alt="Lamp controller"><div><b>Desk Lamp Motor Controller</b><span class="pf-badge pf-ok">Board tested</span></div></a>
<a class="pf-card" href="#temp"><img src="img/temp_v2.jpg" alt="Alarm controller"><div><b>PT100 Alarm Controller</b><span class="pf-badge pf-ok">Delivered</span></div></a>
<a class="pf-card" href="#glove"><img src="img/srtp_stim.jpg" alt="Stimulation board"><div><b>Tremor Glove Boards</b><span class="pf-badge pf-design">Design complete</span></div></a>
<a class="pf-card" href="#drone"><img src="img/drone.jpg" alt="Quadcopter"><div><b>Quadcopter Flight Controller</b><span class="pf-badge pf-wip">Bench-tested</span></div></a>
<a class="pf-card" href="#clock"><img src="img/clock_front.jpg" alt="ESP32 clock"><div><b>ESP32-C3 IoT Clock</b><span class="pf-badge pf-ok">Completed</span></div></a>
</div>

<div class="pf-proj" id="lamp">
<h2>Desk Lamp Motor and Lighting Controller</h2>
<div class="pf-meta">Sep 2026 to present &nbsp; Sole hardware and firmware designer &nbsp; <span class="pf-badge pf-ok">Board tested, firmware running</span> &nbsp; <a class="pf-gh" href="https://github.com/xiaomiao321/taideng"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/></svg>Source on GitHub</a></div>
<p>Motor and lighting controller for a lamp-shaped companion robot prototype. It takes commands from a Linux main board over UART and drives the robot's joints and lights.</p>
<div class="pf-chips"><span class="pf-chip">STM32F407</span><span class="pf-chip">4-layer PCB</span><span class="pf-chip">FreeRTOS</span><span class="pf-chip">8x H-bridge</span><span class="pf-chip">24 V input</span><span class="pf-chip">EasyEDA Pro</span><span class="pf-chip">Python tools</span></div>
<div class="pf-gal">
<figure><img src="img/lamp_real_top.jpg" alt="Assembled lamp controller, powered on"><figcaption>Assembled board, powered on</figcaption></figure>
<figure><img src="img/lamp_top.jpg" alt="Lamp controller top"><figcaption>Top side, 3D render</figcaption></figure>
<figure><img src="img/lamp_bottom.jpg" alt="Lamp controller bottom"><figcaption>Bottom side, 3D render</figcaption></figure>
</div>
<div class="pf-cols">
<div>
<h3>Hardware</h3>
<ul>
<li>24 V input with fuse, P-MOS reverse-polarity protection and TVS; three buck stages for motors, the Linux board and logic, plus a 3.3 V LDO</li>
<li>8 RZ7899 H-bridge motor channels, 6 potentiometer inputs for joint angle, 7 lamp PWM channels</li>
<li>Stackup: signal, solid GND plane, power plane split into 24 V, 12 V and 5 V regions, signal; motor and lamp power kept to the board edges, away from PWM and feedback lines</li>
</ul>
</div>
<div>
<h3>Firmware and tools</h3>
<ul>
<li>Binary UART protocol to the main board: framing, CRC16, duplicate filtering, timeout and error recovery</li>
<li>Joint calibration stored in on-chip flash and restored at power-up</li>
<li>Watchdog; on fault, e-stop or heartbeat timeout all outputs stop until explicitly re-armed</li>
<li>Protocol and control layers unit-tested on PC with gcc; Python GUI for driving all motors and lights on the bench</li>
</ul>
</div>
</div>
<div class="pf-note">Debug note: on the first board, one of four lamp PWM channels had no output while the other three worked. All four share the same timer configuration, so a software cause was unlikely. I added a probe mode that drives the suspect pin and a known-good pin as plain 1 Hz GPIO: the suspect pin stayed flat right at the MCU, which ruled out the series resistor and connector and pointed to a cold solder joint on the QFP pin. Reworking it fixed the channel; one ADC channel had the same cause.</div>
</div>

<div class="pf-proj" id="temp">
<h2>8-Channel PT100 Over-Temperature Alarm Controller</h2>
<div class="pf-meta">Contract project, Jul 2026 to present &nbsp; Sole hardware and firmware designer &nbsp; <span class="pf-badge pf-ok">v1 delivered</span> <span class="pf-badge pf-wip">v2 in progress</span> &nbsp; <a class="pf-gh" href="https://github.com/xiaomiao321/Temperature"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/></svg>Source on GitHub</a></div>
<p>Fire-protection controller for kitchens and ducts. When any of eight temperature channels passes its threshold, it sounds the alarm, stops the fan, shuts the gas valve and closes the fire damper. Version 1 was delivered to the customer site in July 2026.</p>
<div class="pf-chips"><span class="pf-chip">STM32F103</span><span class="pf-chip">RS485 Modbus RTU</span><span class="pf-chip">Relay control</span><span class="pf-chip">Fail-safe design</span><span class="pf-chip">Orange Pi Linux</span></div>
<div class="pf-gal">
<figure><img src="img/temp_v1.jpg" alt="Version 1 board"><figcaption>v1 carrier board, 3D render</figcaption></figure>
<figure><img src="img/temp_v2.jpg" alt="Version 2 integrated board"><figcaption>v2 integrated board, 3D render</figcaption></figure>
</div>
<div class="pf-cols">
<div>
<h3>Version 1, delivered</h3>
<ul>
<li>Carrier board for an STM32F103 core module, buck and RS485 modules; 7-segment displays, setting keys, indicators and four relay outputs</li>
<li>Reads a PT100 acquisition card over RS485 Modbus RTU</li>
<li>Alarm latches until manual reset, then a 3-minute hold-off so residual heat at the sensors does not retrigger it</li>
<li>Relays release on power loss and the damper stays open, so a controller failure never blocks other equipment</li>
<li>Installation and maintenance manual for the site electricians</li>
</ul>
</div>
<div>
<h3>Version 2, in progress</h3>
<ul>
<li>Single integrated board: STM32F103, RS485 transceiver, four 250 VAC 10 A relays</li>
<li>Isolation slot between the mains relay area and the low-voltage logic</li>
<li>24 V to 5 V 5 A supply and a UART link for an Orange Pi Linux gateway</li>
<li>Gateway for HTTPS data upload and alarm video recording, software in progress</li>
</ul>
</div>
</div>
</div>

<div class="pf-proj" id="glove">
<h2>Tremor Assessment and Intervention Glove</h2>
<div class="pf-meta">SRTP research project, <a href="https://person.zju.edu.cn/en/panyun">Prof. Yun Pan's lab</a>, Feb 2026 to present &nbsp; Sole board designer &nbsp; <span class="pf-badge pf-design">Design complete, DRC clean, awaiting fabrication</span> &nbsp; <a class="pf-gh" href="https://github.com/xiaomiao321/SRTP"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/></svg>Source on GitHub</a></div>
<p>A wearable glove that measures hand tremor and applies transcutaneous electrical stimulation. Two stacked boards connected over SPI. Research prototype, no medical claims.</p>
<div class="pf-chips"><span class="pf-chip">nRF52832 BLE</span><span class="pf-chip">NNC6121</span><span class="pf-chip">4-layer and 6-layer PCB</span><span class="pf-chip">High-voltage layout</span><span class="pf-chip">EasyEDA scripting</span></div>
<h3>Boards</h3>
<div class="pf-gal pf-gal4">
<figure><img src="img/srtp_main.jpg" alt="Main board top"><figcaption>Main board, top</figcaption></figure>
<figure><img src="img/srtp_main_back.jpg" alt="Main board bottom"><figcaption>Main board, bottom</figcaption></figure>
<figure><img src="img/srtp_stim.jpg" alt="Stimulation board top"><figcaption>Stimulation board, top</figcaption></figure>
<figure><img src="img/srtp_stim_back.jpg" alt="Stimulation board bottom"><figcaption>Stimulation board, bottom</figcaption></figure>
</div>
<h3>Stimulation board layout</h3>
<div class="pf-gal pf-gal3">
<figure><img src="img/srtp_stim_top_layer.jpg" alt="Top layer routing"><figcaption>Top layer, nets colored by class; high-voltage nets in red</figcaption></figure>
<figure><img src="img/srtp_stim_gnd.jpg" alt="Inner GND layer"><figcaption>Inner GND layer: high-voltage ground, red, and digital ground, blue, joined at one point</figcaption></figure>
<figure><img src="img/srtp_stim_bottom_layer.jpg" alt="Bottom layer routing"><figcaption>Bottom layer</figcaption></figure>
<figure><img src="img/srtp_boost.jpg" alt="Boost converter area"><figcaption>Boost converter area, close-up</figcaption></figure>
<figure><img src="img/srtp_nnc.jpg" alt="NNC6121 area"><figcaption>Around the NNC6121, close-up</figcaption></figure>
<figure><img src="img/srtp_stack.jpg" alt="Stack alignment check"><figcaption>Main board outline overlaid on the stimulation board to check connector and button alignment</figcaption></figure>
</div>
<p class="pf-meta">All images on this project are 3D renders and layout exports; the boards are not yet fabricated.</p>
<div class="pf-cols">
<div>
<h3>Main board</h3>
<ul>
<li>nRF52832 with 2.4 GHz antenna matching network</li>
<li>Eight I2C sensor ports for finger sensors, wrist IMU and magnetometer, with switched sensor power</li>
<li>USB battery charging and battery voltage sensing</li>
</ul>
</div>
<div>
<h3>Stimulation board</h3>
<ul>
<li>NNC6121 with on-chip boost up to 55 V, two stimulation channels, electrode-off detection and an e-stop button</li>
<li>Stackup: top, GND, signal, signal, GND, bottom; 0.6 mm clearance rule for all high-voltage nets</li>
<li>High-voltage, analog and digital grounds split and joined at a single point; boost and output stages kept away from the digital area</li>
<li>Python scripts on the EasyEDA API for rule-aware routing and connectivity checks; stackup, rules, part choices and final review done by hand</li>
</ul>
</div>
</div>
</div>

<div class="pf-proj" id="drone">
<h2>STM32 Quadcopter Flight Controller</h2>
<div class="pf-meta">Jan 2026 to Feb 2026 &nbsp; <span class="pf-badge pf-wip">v3 bench-tested, not yet flown</span> &nbsp; <a class="pf-gh" href="https://github.com/xiaomiao321/Drone"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/></svg>Source on GitHub</a></div>
<p>Three revisions of a flight controller board. The first two ran ArduPilot on an STM32H743; the third moved to an STM32F103 running my own flight control firmware.</p>
<div class="pf-chips"><span class="pf-chip">STM32F103</span><span class="pf-chip">STM32H743</span><span class="pf-chip">FreeRTOS</span><span class="pf-chip">Quaternion attitude</span><span class="pf-chip">Cascaded PID</span></div>
<h3>Photos</h3>
<div class="pf-gal pf-gal4">
<figure><img src="img/drone_v1_photo.jpg" alt="v1 flight controller"><figcaption>v1, STM32H743</figcaption></figure>
<figure><img src="img/drone_v2_photo.jpg" alt="v2 flight controller"><figcaption>v2, STM32H743</figcaption></figure>
<figure><img src="img/drone_fc_v3.jpg" alt="v3 flight controller"><figcaption>v3, STM32F103</figcaption></figure>
<figure><img src="img/drone.jpg" alt="Assembled quadcopter"><figcaption>Assembled quadcopter</figcaption></figure>
</div>
<h3>Board renders</h3>
<div class="pf-gal pf-gal4">
<figure><img src="img/drone_v1_3d.jpg" alt="v1 render"><figcaption>v1, 3D render</figcaption></figure>
<figure><img src="img/drone_v2_3d.jpg" alt="v2 render"><figcaption>v2, 3D render</figcaption></figure>
<figure><img src="img/drone_v3_front.jpg" alt="v3 top"><figcaption>v3, top side</figcaption></figure>
<figure><img src="img/drone_v3_back.jpg" alt="v3 bottom"><figcaption>v3, bottom side</figcaption></figure>
</div>
<ul>
<li>Schematic, PCB and assembly for each revision; ArduPilot flashed on v1 and v2</li>
<li>v3 firmware under FreeRTOS: quaternion attitude estimation, cascaded PID and motor mixing</li>
<li>v3 bench test: firmware running and all four motors driven; not yet flown</li>
</ul>
</div>

<div class="pf-proj" id="clock">
<h2>ESP32-C3 IoT Clock</h2>
<div class="pf-meta">Oct 2025 to Nov 2025 &nbsp; Sole hardware and firmware designer &nbsp; <span class="pf-badge pf-ok">Completed</span> &nbsp; <a class="pf-gh" href="https://github.com/xiaomiao321/Aiot-project-ESP32C3"><svg class="pf-ico" viewBox="0 0 16 16" aria-hidden="true"><path fill="currentColor" d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59.4.07.55-.17.55-.38 0-.19-.01-.82-.01-1.49-2.01.37-2.53-.49-2.69-.94-.09-.23-.48-.94-.82-1.13-.28-.15-.68-.52-.01-.53.63-.01 1.08.58 1.23.82.72 1.21 1.87.87 2.33.66.07-.52.28-.87.51-1.07-1.78-.2-3.64-.89-3.64-3.95 0-.87.31-1.59.82-2.15-.08-.2-.36-1.02.08-2.12 0 0 .67-.21 2.2.82.64-.18 1.32-.27 2-.27.68 0 1.36.09 2 .27 1.53-1.04 2.2-.82 2.2-.82.44 1.1.16 1.92.08 2.12.51.56.82 1.27.82 2.15 0 3.07-1.87 3.75-3.65 3.95.29.25.54.73.54 1.48 0 1.07-.01 1.93-.01 2.2 0 .21.15.46.55.38A8.013 8.013 0 0016 8c0-4.42-3.58-8-8-8z"/></svg>Source on GitHub</a></div>
<div class="pf-chips"><span class="pf-chip">ESP32-C3</span><span class="pf-chip">PlatformIO</span><span class="pf-chip">FreeRTOS</span><span class="pf-chip">MQTT</span></div>
<div class="pf-gal pf-gal3">
<figure><img src="img/clock_front.jpg" alt="Clock front"><figcaption>Running clock</figcaption></figure>
<figure><img src="img/clock_back.jpg" alt="Clock back"><figcaption>Back of the board</figcaption></figure>
</div>
<ul>
<li>Designed and soldered the board</li>
<li>Wi-Fi provisioning, NTP time sync, Huawei Cloud IoT connection over MQTT</li>
</ul>
</div>

<div class="pf-proj">
<h2>Skills</h2>
<div class="pf-skills">
<span>PCB</span><div>EasyEDA Pro: schematics, 4 and 6 layer layout, design rules, DRC, Gerber and BOM; Altium Designer</div>
<span>Bench</span><div>Hand soldering and rework, multimeter, oscilloscope, bench supplies, board-level fault isolation</div>
<span>Platforms</span><div>STM32, ESP32, TI MSPM0, FPGA, Raspberry Pi, Orange Pi</div>
<span>Firmware</span><div>C and C++, FreeRTOS, CMake, OpenOCD and gdb, PlatformIO; Python for test tools</div>
<span>Interfaces</span><div>UART, SPI, I2C, RS485 Modbus RTU, USB, BLE, Wi-Fi, MQTT, HTTPS</div>
</div>
</div>
</div>
