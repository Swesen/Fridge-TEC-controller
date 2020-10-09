# This is my attempt at creating a mini fridge controller.

## Key functions:
- Voltage controlled TEC, this is more optimal than simply switching between on and off.
- Controlls standard 4-pin PWM computer fans.
- Very good performance, over 20°C temperature difference from ambient.
- No wait timers, arduino runns at real time as much as possible.
- Automatically turns of OLED display.

## It uses an arduino nano as the controller and aditionall components:  
- 0.96" Inch 128x64 Oled LCD Display  
- 2x Momentairy buttons for menu navigation and changing settings  
- ntc 100k thermistor
- 10k resistor
- Peltier TEC 12v 5A  
- Cooler Master MasterLiquid Lite 240  
- 2x PWM 120mm fans for radiator  
- 40x10mm fan internal  
- 3D printed main body  
- 6x M3 screws  
- 12v 6A powersupply  
- Selfmade switchmode powersupply (buck converter) for controlling the voltage of the TEC consisting of:  
  - A Common Mode Choke capable of 5A(I used one of unknown rating)  
  - A transistor, BJT or Mosfet capable of  5A
  - A capacitor capable of 12v
  - Reference: https://www.electronics-tutorials.ws/power/switch-mode-power-supply.html
  
## Project was created in Visual Studio Code using PlatformIO
  Dependacies:  
  - Adafruit SSD1306 - https://github.com/adafruit/Adafruit_SSD1306
  - Adafruit BusIO - https://github.com/adafruit/Adafruit_BusIO
  - PID by Br3ttb - https://github.com/br3ttb/Arduino-PID-Library
  
#### 3D printer .stl files not provided since it is a very specific use case.
