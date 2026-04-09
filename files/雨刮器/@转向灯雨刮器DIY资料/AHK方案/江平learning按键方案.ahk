
; 远光灯

1Joy4::
Send k
KeyWait 1Joy4
Send k
return

; 双闪灯

1Joy3::
Send {j Down}
KeyWait 1Joy3 ; On release, switch off
Send {j Up}
return

; 左转向灯

1Joy1::
Send [
KeyWait 1Joy1
Send [
return

; 右转向灯

1Joy2::
Send ]
KeyWait 1Joy2
Send ]
return