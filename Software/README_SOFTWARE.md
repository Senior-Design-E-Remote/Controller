# Software Report

## Libraries

E-Remote is programmed using the Arduino IDE for its compatibility with the Adafruit HUZZAH32 ESP32 Feather board and access to the two driving libraries, Adafruit_MPR121 and ESP32-BLE-Gamepad. These two libraries are essential to the E-Remote program and implement the numerous functionalities needed for E-Remote to act as a game controller.

### Adafruit_MPR121
The Adafruit_MPR121 library is used to communicate with the MPR121 Capacitive touch board. The Adafruit_MPR121 object needs to be constructed and run its begin function, but its main use is the MPR121.touched() function which returns an uint16_t value representing the state of all twelve touch buttons. This value is then bit shifted by an amount representing the pin whose state the program wants to check and stored in a boolean value.

### ESP32-BLE-Gamepad
ESP32-BLE-Gamepad is the heart of the program as it takes the E-Remote and turns it into a video game controller. The first thing it does is enable the  ESP32-WROOM-32E chip and allow the ESP to connect to the computer via Bluetooth. Second, it registers as a Bluetooth game controller so it can be properly recognized by the computer. Finally, it takes user inputs and properly converts them to the game action signal (A button to A action, left joystick to move, etc.). 

## Wireless Controller

### Explanation
Since the ESP is programmed with the Arduino IDE, the code is written in the C++ programming language. 
The program follows the basic Arduino programming structure of the Setup and Loop blocks. 
The Setup loop is used for initialization. It declares input pins for the physical buttons, starts the MPR121 chip, and most importantly, sets the configurations for the ESP32-BLE-Gamepad so there are no extraneous controls added.
The Loop will cycle through every user input and check its current state, and send its corresponding signal to the computer. 

If the input is a button (physical or touch), the program will check its current state against its previous state and will only send an updated signal if the state has changed, preventing extraneous repeat signals from being sent. 
It is important to note that although the state storage arrays and library variables are global variables, this is normal for Arduino-style code since there is no singular Main function to both declare and use variables and the loop and set-up blocks cannot access each other's variables. 

The joysticks are not as simple as they output noise when at rest which can cause the player controlled character to move even when their hands are at rest. 
To circumvent this, the device will take 3000 reads from each joystick axis and finds all their maximum and minimum values. Then, while in the loop, the code will take 100 reads of each axis and average them to find a value. 
If this value falls inside of the max and min for that axis, the code will instead send a rest value of 16383 which is true neutral for any joystick axis. 
Otherwise, it will map the value from the joysticks 0-4095 to the computer's range of 0-32767 to find the movement position.

### Pseudocode

```
Setup {
    MPR121 Begin
    Physical Button Pins = Input
    Set Gamepad Configurations

    for each Joystick Axis{
        Take 3000 reads
        Set Axis Max
        Set Axis Min
    }
}

Loop {
    Poll Inputs

    If Button{
        Check previous state and send Button Signal if changed
    }
	
    If Joystick{
        Average 100 reads
        If Average in Rest Range: send Rest Val
        Else: Map 0-4095 -> 0-32767
    }
    Send Joystick Signal
}
```

### Block Diagram

<img src="SoftwareFlowchart.jpg">

## Using the Code
### Setup
In order to upload the WirelessController code to your ESP, you need to setup the Arduino IDE, which you can install [here](https://www.arduino.cc/en/software).

#### Step 1: Installing the Boards
The Arduino IDE does not come with the ESP boards preinstalled, so you need to follow a few simple steps in order to get them installed. 

1. Go to **File** -> **Preferences** to open the preferences menu. 

2. Copy this url: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json to the text box labeled "Additional Board Manager URLs". 

3. Go to the Board Manager and search for esp, they should pop up and you should be able to hit install. Wait for the intall to finsh and you should be able to select ESP boards.

#### Step 2: Installing the Libraries
There are two different methods of installing the required libraries depending on what version of the Arduino IDE you have. 

1. In Arduino IDE 1.6.2 and above, go to the Libraries Manager and search for both the Adafruit_MPR121 and ESP32-BLE-Gamepad libraries. Both should come up and there will be an option to install both.

2. Go to the Githubs for each library found [here](*https://github.com/adafruit/Adafruit_MPR121) and [here](https://github.com/lemmingDev/ESP32-BLE-Gamepad). Download them as zip files, go to **Sketch** -> **Include Library** -> **Add .Zip Library**, and select the zip files. The library should appear in the library manager where you can then install them.

### Uploading the Code:
Now that the Arduino IDE is properly configured, you can now upload the code to your ESP by following these steps.
1. Plug your ESP into the computer 
2. Open the Arduino IDE and open the Board Manager
3. Choose the Adafruit ESP32 Feather as the board for the corresponding COM Port.
    * **Important Note**: Some computeres require the [CP210x USB to UART Bridge](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads) driver to properly read the ESP as connected to a COM port.
4. If the text in the Board Manager dropdown menu becomes bolded, that means the ESP is connected and you can begin the upload.
5. Wait for the upload to finish and verify the code is working by going to your bluetooth menu and see if E-Remote is avaiable to connect
    * Note that first time compile and upload can take upwards of 5-10 minutes as the ESP32-BLE-Gamepad library takes a long time to compile. This is will go down in subsiquent compilations.

If all is successfull, you can connect to E-Remote through your computer's bluetooth menu where it will be registered as a generic gamepad. You can then connect it to the game library of your choice (we used Steam and you can find those steps in the User Manual).

## Other Code
This section will explain the other code found in the Software folder of this repository. These are various examples of hardware and other controller code that we made to help develop the final E-Remote product
### Hardware Examples
In this folder are various examples we made to test hardware for the E-Remote. These include tests for the logarithmic slider, a test for joystick drift, and several examples of tests for the MPR121 and the capacitive touch buttons. These examples hsould help you test individual hardware should you run into trouble with any of your components.
### Wired Controller
In this folder is the code for a wired controller which was the first working version of our controller code. This code is only compatible with the [Arduino Micro](https://store.arduino.cc/products/arduino-micro) and the [Arduino Leonardo](https://store.arduino.cc/products/arduino-leonardo-with-headers?queryID=undefined) as they are the only board with the ATmega32u4 which allows for USb communication with a computer. This example uses the XInput library and is a similar concept to the wireless controller code, but without the need to check previous button state or filter analog joystick noise as the library handles it automatically. When connected to a computer, it automatically registers as an Xbox 360 controller and works as any other Xbox controller would. This is an interesting tradeoff with the E-remote as the Wired controller has an easier setup with the predefined Xbox controlls but loses the user customizable controlls that come with E-Remote's generic gamepad status. Note: if you wish to run this code, the XInput library requires its own version of board installs. Just input follow Step 1 in the Setup seciton and use this url: https://raw.githubusercontent.com/dmadison/ArduinoXInput_Boards/master/package_dmadison_xinput_index.json
