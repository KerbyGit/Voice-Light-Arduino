#include <SoftwareSerial.h>
#include "DFRobot_DF2301Q.h"

  // defining the different pins
  #define RELAY_PIN 8 // to control the small lightbulb
  #define RED_LED_PIN  3   // to control the red led 

  // 
  SoftwareSerial vrSerial(6, 7);
  DFRobot_DF2301Q_UART asr(&vrSerial);

  void setup() {
    Serial.begin(115200);

    // initializing the pins
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    pinMode(RED_LED_PIN, OUTPUT);
    digitalWrite(RED_LED_PIN, LOW);


    // initializing voice module
    while (!asr.begin()) {
      Serial.println("Voice module not detected! Check wiring & switch to UART.");
      delay(2000);
    }
    Serial.println("Voice module initialized.");

    // voice sensor configurations ; optional
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_MUTE,         0); // low
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_VOLUME,       7); // loudest it can be
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_WAKE_TIME,   20); // duration it will listen to command before turning off automatically
    asr.settingCMD(DF2301Q_UART_MSG_CMD_SET_ENTERWAKEUP,  0); // starts listening as program runs and hears command word

    Serial.println("The program is ready to run. Say the wake up command to commence!");
  }

  void loop() {
    uint8_t cmd = asr.getCMDID();

    switch (cmd) {
      case 103:  // built-in “Turn on the light”
        Serial.println("→ LIGHT ON (103)");
        digitalWrite(RELAY_PIN, HIGH);   // energize relay → bulb on
        break;

      case 104:  // built-in “Turn off the light”
        Serial.println("→ LIGHT OFF (104)");
        digitalWrite(RELAY_PIN, LOW);    // de-energize relay → bulb off
        break;

      case 5:  // Learnt french version of lights on
        Serial.println("→ LUMIERE ALLUME (5)");
        digitalWrite(RELAY_PIN, HIGH);   // ouvert
        break;

      case 6:  // Learnt french version of lights off
        Serial.println("→ LUMIERE ETEINT (6)");
        digitalWrite(RELAY_PIN, LOW);    // fermer
        break;
      
      case 7: // added red led function
        Serial.println("→ RED LED ON (7)");
        digitalWrite(RED_LED_PIN, HIGH);    // on
        break;

      case 8:
        Serial.println("→ RED LED OFF (8)");
        digitalWrite(RED_LED_PIN, LOW);    // off
        break;

      default:
        if (cmd != 0) {
          Serial.print("Unknown CMDID = ");
          Serial.println(cmd);
        }
        break;
    }

    // avoid serial spam
    delay(200);
  }