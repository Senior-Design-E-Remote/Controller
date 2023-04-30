# E-Remote Quick Start Guide

<img src="/Pictures/E-RemoteLogo.jpg">

## Introduction and Current State

Welcome to E-Remote, an Inclusive Video Game Controller designed for people with hand arthritis. Our current product as seen below is a streamlined casing designed for maxmimm usability with minimal pain. Our finalized shell design is based on feedback from actual patients at Boston Medical Center, who's responses you can see reported in the Previous Reports folder.


Current Features include:
* Palm controlled joysticks
* Removable joystick caps with different size options available
* Touch capacitive buttons triggered by a tap
* A streamlined shell casing designed for wrist support while gaming
* Bluetooth Capabilities
* Battery and Micro USB power support
* Brightness adjustable color rotating LEDs


E-Remote is fully assembled and is currently able to connect to a Bluetooth capable computer and register itself as a generic gamepad. Once it is connected, you can open any game library that supports generic gamepads and play with minimal setup required (details for Steam can be found in the User Manual). 
On top of that, the WirelessController.ino code that powers E-Remote can also be ported to any Bluetooth capable ESP32 provided the Arduino IDE is properly setup, so you can build as many E-Remotes as you want.  

**Note**: The brightness adjusting logarithmic slider is directly connected to the 3.3V power and acts as a resistor for the LEDs to adjust their brightness. Brightness is not controlled by the code whatsoever.

### Final Product Setup

<img src="/Pictures/FinalProductView.jpg">

<img src="/Pictures/TopDownView.jpg">

## Gotchas

This section is to detail any issues we encountered while developing E-Remote. Make sure to look out for these when starting your E-Remote porject.

### Software

* Some computers require the [CP210x USB to UART Bridge](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) driver to properly read the ESP as connected to a COM port.

* The Arduino IDE can glitch out and refuse to compile code. All you need to do is rerun the Arduino installer [here](https://www.arduino.cc/en/software) and it will fix itself.
	* All your sketches, libraries, and downloaded boards should still be there after the install.

* If the game character is slowly moving even with the joysticks at rest then there is joystick drift. Turn the device off and on again and the drift filtering code should fix it.

* if a capacitive touch button loses connection at any point during use then the device will no longer read its input. Simply restart the device and the button should work again

* If you get the "COM Port X in use" when attempting to upload in the Arduino IDE, try plugging the ESP into a different COM port or restarting your computer.

### Hardware

* The aluminum buttons do not adhere to solder. We drilled a hole to create a connection, but the connection was a bit loose. Make sure to drill small holes.

* The pre-programmed LEDs cannot be changed digitally through the ESP32 (brightness or color pattern). Slider has to be connected directly to LEDs in parallel.

* The wires that connect to the LED add enough resistance to effect the light output due to the length of the wire. Make sure all the wires connected to the LEDs’ cathode is the same length.

* ON/OFF switch could not be connected to the microcontroller because the ESP32 could not digitally turn OFF the system. Instead, the switch is connected in series with the positive side of the battery. Therefore to charge the battery, the switch has to be in the ON position.
