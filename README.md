<div align="center">
  <h1>🚀 Advanced Weather Station</h1>
  <p>An Arduino project simulated in Wokwi</p>
</div>

# Preview

<img width="554" height="551" alt="ADV-wStation-ver1" src="https://github.com/user-attachments/assets/48464f8f-2885-467b-a311-1122bd352337" />

<img width="561" height="570" alt="ADV-wStation-ver1-img2" src="https://github.com/user-attachments/assets/2b47ac33-ffb8-47de-aa84-bc93f7bbfc63" />

------------------------------------------------------------------------------------------------------------------------------------------------------
<div>
<details>
<summary>Click to view the full diagram.json</summary>

```json
{
  "version": 1,
  "author": "Gordon Atsunyo",
  "editor": "wokwi",
  "parts": [
    { "type": "wokwi-breadboard", "id": "bb1", "top": 275.4, "left": -131.6, "attrs": {} },
    { "type": "wokwi-arduino-mega", "id": "mega", "top": 48.6, "left": -22.8, "attrs": {} },
    {
      "type": "wokwi-lcd2004",
      "id": "lcd1",
      "top": 524.8,
      "left": 188,
      "attrs": { "pins": "i2c" }
    },
    { "type": "wokwi-ds1307", "id": "rtc1", "top": -5.4, "left": 528.1, "attrs": {} },
    { "type": "wokwi-microsd-card", "id": "sd1", "top": 105.83, "left": 528.07, "attrs": {} },
    { "type": "wokwi-dht22", "id": "dht1", "top": 67.5, "left": -216.6, "attrs": {} },
    { "type": "wokwi-membrane-keypad", "id": "keypad1", "top": -414.8, "left": 34.4, "attrs": {} },
    {
      "type": "wokwi-buzzer",
      "id": "bz1",
      "top": 549.6,
      "left": -151.8,
      "attrs": { "volume": "0.1" }
    },
    {
      "type": "wokwi-buzzer",
      "id": "bz2",
      "top": 549.6,
      "left": -65.4,
      "attrs": { "volume": "0.1" }
    },
    {
      "type": "wokwi-buzzer",
      "id": "bz3",
      "top": 549.6,
      "left": 21,
      "attrs": { "volume": "0.1" }
    },
    { "type": "wokwi-potentiometer", "id": "pot1", "top": -97.3, "left": -221, "attrs": {} }
  ],
  "connections": [
    [ "mega:5V", "bb1:tp.21", "red", [ "v0" ] ],
    [ "mega:GND.2", "bb1:tn.25", "black", [ "v35.7", "h40.55", "v28.8" ] ],
    [ "sd1:GND", "bb1:tn.50", "black", [ "h38.4", "v134.51" ] ],
    [ "bb1:tp.1", "bb1:bp.1", "red", [ "v0.3", "h-58.4", "v172.8" ] ],
    [ "bz2:1", "bb1:bn.10", "black", [ "v19.2", "h38.4" ] ],
    [ "bz3:1", "bb1:bn.18", "black", [ "v19.2", "h67.2" ] ],
    [ "bz1:1", "bb1:bn.2", "black", [ "v19.2", "h48" ] ],
    [ "lcd1:GND", "bb1:bn.24", "black", [ "h-19.2" ] ],
    [ "lcd1:VCC", "bb1:bp.21", "red", [ "h-57.6", "v-105.5" ] ],
    [ "pot1:VCC", "bb1:tp.3", "red", [ "v19.2", "h-0.8" ] ],
    [ "pot1:GND", "bb1:tn.6", "black", [ "v28.8", "h96" ] ],
    [ "rtc1:SDA", "mega:SDA", "magenta", [ "h0" ] ],
    [ "sd1:VCC", "bb1:tp.50", "red", [ "h9.6", "v124.94" ] ],
    [
      "lcd1:SCL",
      "mega:21",
      "yellow",
      [ "h-28.8", "v-76.5", "h374.4", "v-240", "h-163.2", "v-259.2", "h-59.7" ]
    ],
    [ "rtc1:SCL", "mega:SCL", "cyan", [ "h-240", "v-19.4", "h-153.6" ] ],
    [
      "lcd1:SDA",
      "mega:20",
      "green",
      [ "h-9.6", "v-57.4", "h345.6", "v-259.2", "h-144", "v-240", "h-78.8" ]
    ],
    [ "bz2:2", "mega:32", "#8f4814", [ "v28.8", "h-134.8", "v-393.6", "h240", "v-163.2" ] ],
    [ "bz1:2", "mega:30", "white", [ "v9.6", "h-58", "v-403.2", "h259.2", "v-135.4" ] ],
    [
      "bz3:2",
      "mega:34",
      "purple",
      [ "v38.4", "h-240.4", "v-422.4", "h134.4", "v-115.2", "h163.2", "v-9.6" ]
    ],
    [ "sd1:DO", "mega:50", "violet", [ "h28.8", "v96.11", "h-240", "v-19.2" ] ],
    [ "sd1:CS", "mega:53", "#8f4814", [ "h19.2", "v19.26" ] ],
    [ "sd1:DI", "mega:51", "gray", [ "h-9.6", "v38.31" ] ],
    [ "keypad1:R1", "mega:38", "blue", [ "v230.4" ] ],
    [ "keypad1:R2", "mega:40", "blue", [ "v230.4", "h-0.4" ] ],
    [ "keypad1:R3", "mega:42", "blue", [ "v240", "h-0.3" ] ],
    [ "keypad1:R4", "mega:44", "blue", [ "v249.6", "h-0.2" ] ],
    [ "dht1:VCC", "bb1:tp.2", "red", [ "v76.8", "h124.8", "v9.6" ] ],
    [ "dht1:GND", "bb1:tn.1", "black", [ "v9.6", "h76.8", "v105.6" ] ],
    [ "bb1:tn.2", "bb1:bn.1", "black", [ "v9.5", "h-48.8", "v163.2" ] ],
    [ "mega:2", "dht1:SDA", "orange", [ "v-19.2", "h-368.8", "v163.2", "h-38.4" ] ],
    [ "sd1:SCK", "mega:52", "limegreen", [ "h-19.2", "v86.39", "h-259.2", "v-19.2" ] ],
    [ "rtc1:5V", "bb1:tp.49", "red", [ "h0" ] ],
    [ "rtc1:GND", "bb1:tn.49", "black", [ "h-57.6", "v297.6", "h-19.2" ] ],
    [ "keypad1:C1", "mega:39", "limegreen", [ "v76.8", "h220.7", "v144" ] ],
    [ "keypad1:C2", "mega:41", "limegreen", [ "v67.2", "h220.8", "v153.6" ] ],
    [ "keypad1:C3", "mega:43", "limegreen", [ "v57.6", "h220.65", "v172.8" ] ],
    [ "keypad1:C4", "mega:45", "limegreen", [ "v48", "h220.5", "v192" ] ],
    [ "pot1:SIG", "mega:A0", "gold", [ "v38.4", "h143.6", "v172.8", "h220.8", "v50.7" ] ]
  ],
  "dependencies": {}
}
```
</div>


![Build Status](https://img.shields.io/github/actions/workflow/status/username/repo/main.yml)
![License](https://img.shields.io/github/license/username/repo)
