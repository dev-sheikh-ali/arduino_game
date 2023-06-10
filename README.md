
## ⚡ arduino game

![](https://imagizer.imageshack.com/img924/667/50ulqN.jpg)

---
In this task, i made a simpe using Arduino. The TFT screen and joystick are connected to the Arduino board using the following pin configuration:
## TFT screen:
- LED: 3.3V
- SCK: D13
- SDA (MOSI): D11
- A0: D8
- RST: D9
- CS: D10
- VCC: 5V



<table width="100%"> 
<tr>
<td width="30%">      
&nbsp; 
<br>
<p align="center">
  game
</p>
<img src="https://imagizer.imageshack.com/img924/1379/swQlWf.jpg">
</td> 
<td width="30%">
<br>
<p align="center">
  game over
</p>
<img src="https://imagizer.imageshack.com/img923/2931/5XrG1L.jpg">  
</td>
</table>

## Joystick pins: 
- GND pin connects to the circuit’s ground.
- Vcc pin is used to supply the 5-volt power to the module.
- VRx pin is the analog output pin for X-axis (left and right).
- VRy pin is the analog output pin for Y-axis (up and down).
- SW pin is connected to the pull-up button. Once the button is pressed, SW pin outputs 0

![](https://imagizer.imageshack.com/img924/783/VOiIcV.jpg)

## Library Installation

To get started, we need to include the Adafruit_ILI9163C library in our Arduino code. Follow these steps to install the library:

1. Open the Arduino IDE.
2. Go to "Sketch" -> "Include Library" -> "Manage Libraries".
3. In the Library Manager, search for "Adafruit_GFX".
4. Click on the "Adafruit_GFX" library and click the "Install" button.
5. Wait for the installation to finish.

## Usage

To use the code, follow these steps:

1. Connect the TFT screen and the joystick to the Arduino board according to the provided pin configuration.
2. Open the Arduino IDE and create a new sketch.
3. Include the library at the beginning of your code:

   ```libaries
   #include <Adafruit_GFX.h>
   #include <Adafruit_ST7735.h>


