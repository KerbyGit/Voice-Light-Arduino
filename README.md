# Arduino Project: Voice Controlled Lighting System

## Project Overview

This project aims to allow the users to control their lighting system via voice control, thus allowing for a hands-free system. We can remotely control a red LED as well as small lightbulb with the sound of our voice.With the use of an Arduino Uno and a voice recognition sensor, this beginner project serves as introductory step to the progression of home-automation. 

## Hardware Components

- Arduino Uno
- DFRobot Voice Recognition Sensor (or a voice recognition module of your choice)
- Relay Modules (can depend on how many lightbulbs or other gadgets used)
- Any Colour LED
- Any Lightbulb
- Jumper Wires
- Breadboard
- Power Supply (connected to Mac)

## Circuit Diagram

[Insert circuit diagram image or description]

## Wiring Instructions

| Arduino Pin | Connected To | Description |
|-------------|--------------|-------------|
| Pin 2       | [Component]  | [Purpose]   |
| Pin 3       | [Component]  | [Purpose]   |
| ...         | ...          | ...         |

## Software Requirements

- Arduino IDE 2.3.6
- Libraries:
  - DFRobot_DF2301Q.h (need to install via library)
  - SoftwareSerial.h (included)

## Code Explanation

```arduino
#include <SoftwareSerial.h>
#include "DFRobot_DF2301Q.h"

  // defining the pins
  #define RELAY_PIN 8 // relay control pin (Needed for the lightbulb)
  #define RED_LED_PIN  3   // led pin (to control the red led 

  // 
  SoftwareSerial vrSerial(6, 7);
  DFRobot_DF2301Q_UART asr(&vrSerial);

  void setup() {
    Serial.begin(115200);

    // initializing the pins and setting their output to low so that they are off at the start
    pinMode(RELAY_PIN, OUTPUT); 
    digitalWrite(RELAY_PIN, LOW); // light loff
    pinMode(RED_LED_PIN, OUTPUT);
    digitalWrite(RED_LED_PIN, LOW); // led off


    // initializing voice module
    while (!asr.begin()) {
      Serial.println("Voice module not detected! Check wiring & switch to UART.");
      delay(2000);
    }
    Serial.println("Voice Module is Properly Functioning."); // confirming that the Voice Sensor was correctly initialized into the serial monitor

    // voice sensor configurations ; optional
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_MUTE,         0); // low
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_VOLUME,       7); // loudest it can be
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_WAKE_TIME,   20); // 20 s (duration it will listen to a command before turning off automatically)
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_ENTERWAKEUP,  0); // starts listening as program runs and hears command word

    Serial.println("The program is ready to run. Say the wake up command to commence!"); // further confirmation that system runs
  }

  void loop() {
    uint8_t cmd = asr.getCMDID();

// switch case to handle the different IDs
    switch (cmd) {
      case 103:  // built-in command for the sensor
        Serial.println("→ LIGHT ON (103)");
        digitalWrite(RELAY_PIN, HIGH);   // energize relay → bulb turns on
        break;

      case 104:  // built-in “Turn off the light”
        Serial.println("→ LIGHT OFF (104)");
        digitalWrite(RELAY_PIN, LOW);    // de-energize relay → bulb turns off
        break;

      case 5:  // learnt command french version of lights on
        Serial.println("→ LUMIERE ALLUME (5)");
        digitalWrite(RELAY_PIN, HIGH);   // same as case 103
        break;

      case 6:  // learnt command french lights off
        Serial.println("→ LUMIERE ETEINT (6)");
        digitalWrite(RELAY_PIN, LOW);    // same as 104
        break;
      
      case 7: // added red led function on
        Serial.println("→ RED LED ON (7)");
        digitalWrite(RED_LED_PIN, HIGH);    // changes low to high, led on 
        break;

      case 8: // added red led function off
        Serial.println("→ RED LED OFF (8)");
        digitalWrite(RED_LED_PIN, LOW);    // turns it back off
        break;

      default: // gives the id for the unrecognized command, debugging tool
        if (cmd != 0) {
          Serial.print("Unknown CMDID = ");
          Serial.println(cmd);
        }
        break;
    }

    // avoid serial spam
    delay(200);
  }
```

## Usage Instructions

1. Open the Arduino IDE and select the correct Arduino Uno Modem
2. Verify if the required libaries are installed (DFRobot_DF2301Q). If not, download them.
3. Download the voicelightarduino.ino sketch and upload it to your Uno 
4. Open the Serial Monitor at 115200 baud
5. Speak clearly to the Voice Recognition Module:
  - 
    - Say wake command word "Hello Robot" (blue light appears)
  - 
    - Make sure the module is listening (continued presence of blue light)
6. Say any of the following commands:
  - 
    -  "Turn On The Light" 
  - 
    -  "Turn Off The Light"  
  - 
    -  "Ouvre La Lumiere"  
  - 
    -  "Ferme La Lumiere"
  - 
    -  "Red LED On"  
   - 
    -  "Red Off"
    
## Troubleshooting

- **No Voice Response**: Confirm UART switch position and make sure the module is in listening mode (blue) when saying your command
- **Light Constantly On**: Verify if beginning output has been changed. Reset Arduino and recommence.

## Future Improvements

- Integrate other device (e.g. fans and motors)
- Support higher voltage lightbulbs (e.g. multiple bulbs or RGB leds)

## References

- https://github.com/jtrudeau/arduinogitresource2025/blob/main/templates/ARDUINO_PROJECT_TEMPLATE.md
- https://projecthub.arduino.cc/rohan_barnwal/wave-speak-control-the-future-of-smart-homes-is-here-d5bc55
- https://wiki.dfrobot.com/SKU_SEN0539-EN_Gravity_Voice_Recognition_Module_I2C_UART#target_9