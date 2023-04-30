# Hardware Report

E-Remote is a wireless game controller system that utilizes an Adafruit HUZZAH32 (ESP32 Feather board) microcontroller to process user inputs and translate them into the appropriate signals for the PC to register game actions. Our system was built with the ESP32-WROOM-32E chip, enabling Bluetooth capabilities for wireless connectivity and a built-in Lithium Ion Polymer charger for added convenience.

Our hardware setup includes a rechargeable Lithium Ion Polymer battery (3.7V, 500mAh) connected to the ESP32 feather board microcontroller, which powers the system in 3.3V. An On/Off switch is also included to allow customers to easily power the controller. All electronic components are wired and soldered on a protoboard for easy assembly.

E-Remote features palm controllable joysticks with modular joystick caps in different sizes and twelve capacitive touch buttons made from aluminum sheets, which are read by an Adafruit 12-Key Capacitive Touch Sensor Breakout MPR121 chip.

We've also included Diffused 5mm Slow Fade Flashing RGB LEDs, each controlled by a corresponding capacitive touch button. The LEDs will slowly change colors, and the brightness level can be adjusted using the 10K logarithmic potentiometer slider.

Thank you for checking out the E-Remote Hardware Github repository, we hope you find our system useful for your gaming needs!

## Schematic

This schematic illustrates the electrical connections between the various components that make up the E-Remote system, including the Adafruit HUZZAH32 microcontroller, two joysticks, twelve capacitive touch buttons, one 10K ohm logarithmic potentiometer slider, and eight diffused 5mm slow fade flashing RGB LEDs

<img src="/Pictures/E-Remote Schematic-1.png">

## Bill of Materials

The Bill of Materials provides a comprehensive inventory of the components needed for E-Remote, including their part numbers, quantities, and prices. This information can be used to source the necessary parts for building the system and to estimate the cost of the project.

| #           | Part Number | Vendor       | Bill of Materials                         | Qty | Unit Price | Total Price |
| ----------- | ----------- | ------------ | ----------------------------------------- | --- | ---------- | ----------- |
| 1           | 334382319302| eBay         | 10K Linear Potentiometer Slider           | 1   | 3.21       | 3.21        |
| 2           | 3405        | Adafruit     | HUZZAH32 - ESP32 Feather Board            | 1   | 19.95      | 19.95       |
| 3           | 1578        | Adafruit     | Lithium Ion Polymer Battery - 3.7V 500mAh | 1   | 7.95       | 7.95        |
| 4           | 679         | Adafruit     | Diffused 5mm Slow Fade Flashing RGB LED   | 8   | 0.495      | 3.96        |
| 5           | N/A         | SchlamzTech  | 2" x 6" Protoboard                        | 1   | 4.99       | 4.99        |
| 6           | N/A         | Home Depot   | 12” x 24” Plain Aluminum Sheet            | 1   | 7.31       | 7.32        |
| 7           | 1982        | Adafruit     | MPR121 - 12-Key Capacitive Touch Sensor   | 1   | 15.90      | 15.90       |
| 8           | B07PFSFFZZ  | Overture     | 3D Printer PLA Filament                   | 10  | 0.60       | 6.00        |
| 9           | 3051        | Micro Center | 22 AGW Wire                               | 4   | .07        | 0.28        |
| 10          | B01N59MK0U  | Amazon       | Joysticks                                 | 4   | 1.12       | 4.48        |
|             |             |              | **Final Total**                           |     |            | 74.03       |

## Datasheets

[HUZZAH32 - ESP32 Feather Board](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-huzzah32-esp32-feather.pdf)

[Lithium Ion Polymer Battery](https://cdn-shop.adafruit.com/product-files/1578/1578+msds.pdf)

[Diffused 5mm Slow Fade Flashing RGB LED](https://www.adafruit.com/product/679)

[MPR121 - 12-Key Capacitive Touch Sensor](https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/overview)

## Power Requirements 

Voltage: 3.3V
Current: 10 mA
Power Supply Model: Lithium Ion Polymer Battery - 3.7V 500mAh

## Assembly

E-Remote is assembled by soldering all of the electronic components onto the solderable breadboard, following the hardware schematic for electrical connections. The breadboard serves as the foundation for the controller and provides a convenient platform for mounting all of the components.

As the assembly process progresses, it is important to periodically test the controller to ensure that it is functioning correctly. To check functionality, connect E-Remote to PC and see if the HUZZAH32 can be connected via bluetooth and check if the touch sensors function and LEDs turn on correctly. 

After the components have been soldered onto the solderable breadboard and tested for functionality, the next step in the assembly process is to integrate the breadboard into the 3D printed model of the E-Remote game controller. This involves gluing, taping, or inserting the components into their respective spots in the model, shown in the photos of the assembled controller below.


### Completed Circuit

<img src="/Pictures/prototypeboard.jpg">

### Zoomed In View

<img src="/Pictures/zoomboard.jpg">

### Cad Visualization

<img src="/Pictures/CadVis.jpg">

### Assembled System

<img src="/Pictures/FinalProductView.jpg">