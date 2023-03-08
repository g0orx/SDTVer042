/*********************************************************************************************
 * 
 * G0ORX Front Panel
 * 
 * (c) John Melton, G0ORX, 20 August 2022
 * 
 * This software is made available under the GNU GPL v3 license agreement.
 * 
 */

/*
 * The front panel consists of 2 MCP23017 16 bit I/O port expanders.
 * Each device is controlled through the I2C bus and the devices use the I2C address 0x20 and 0x21.
 * 
 * The device at 0x20 has switches 1..16 connected to it.
 * 
 * The device at 0x21 has the switches 17 and 18, encoder 1..4 switches, encoder 1..4 A and B and 2 output LEDS.
 * 
 * An interrupt is generated when an I/O port input changes state.
 *   
 * The device at 0x20 generates an interrupt on pin 39 (pulls it low) - Pin 7 of the IDC connector.
 * The device at 0x21 generates an interrupt on pin 17 (pulls it low) - Pin 9 of the IDC connector.
 * 
 * The IDC connector is connected to Tune/Filter IDC connector of the Main Board.
 * 
 * The Main board IDC connector is modified to have the trace at PIN 8 cut (goes to Pin 15 of Teensy 4.1).
 * The Main board IDC connector Pin 8 is connected to Pin 18 (SDA) of the Teensy 4.1.
 * The Main board IDC connector PIN 10 is connected to PIN 19 (SCL) of the Teensy 4.1.
 *
 * Note: BOURN encoders have their A/B pins reversed compared to cheaper encoders.
 * 
 */

#ifndef BEENHERE
#include "SDT.h"
#endif

#ifdef G0ORX_FRONTPANEL

// comment out to reverse encoders if using cheap encoders
#define BOURN_ENCODERS

#define e1 volumeEncoder
#define e2 filterEncoder
#define e3 tuneEncoder
#define e4 fineTuneEncoder

G0ORX_Rotary volumeEncoder;
G0ORX_Rotary tuneEncoder;
G0ORX_Rotary filterEncoder;
G0ORX_Rotary fineTuneEncoder;

enum {
  PRESSED,
  RELEASED
};

#define MCP23017_ADDR_1 0x20
#define MCP23017_ADDR_2 0x21

#define INT_PIN_1 39
#define INT_PIN_2 17

static Adafruit_MCP23X17 mcp1;
static volatile uint8_t pin1;
static volatile uint8_t state1;
static volatile bool interrupted1 = false;

static Adafruit_MCP23X17 mcp2;
static volatile uint8_t pin2;
static volatile uint8_t state2;
static volatile uint8_t statex;
static volatile bool interrupted2 = false;

int G0ORXButtonPressed = -1;

#define LED1 0
#define LED2 1

#define LED_1_PORT 6
#define LED_2_PORT 7

FASTRUN
static void interrupt1() {
  __disable_irq();
  while((pin1 = mcp1.getLastInterruptPin())!=MCP23XXX_INT_ERR) {
    FrontPanelSetLed(0,HIGH);
    state1 = mcp1.digitalRead(pin1);
    if (state1 == PRESSED) {
      G0ORXButtonPressed = pin1;
    } else {
      //buttonReleased(pin1);
    }
    FrontPanelSetLed(0,LOW);
  }
  __enable_irq();
}

FASTRUN
static void interrupt2() {
  __disable_irq();
  while((pin2 = mcp2.getLastInterruptPin())!=MCP23XXX_INT_ERR) {
    FrontPanelSetLed(0,HIGH);
    state2 = mcp2.digitalRead(pin2);
    switch (pin2) {
      case 8:
        statex = mcp2.digitalRead(9);
#ifdef BOURN_ENCODERS
        e1.update(statex, state2);
#else
        e1.update(state2, statex);
#endif
        EncoderVolume();
        break;
      case 9:
        statex = mcp2.digitalRead(8);
#ifdef BOURN_ENCODERS
        e1.update(state2, statex);
#else
        e1.update(statex, state2);
#endif
        EncoderVolume();
        break;
      case 10:
        statex = mcp2.digitalRead(11);
#ifdef BOURN_ENCODERS
        e2.update(statex, state2);
#else
        e2.update(state2, statex);
#endif
        EncoderFilter();
        break;
      case 11:
        statex = mcp2.digitalRead(10);
#ifdef BOURN_ENCODERS
        e2.update(state2, statex);
#else
        e2.update(statex, state2);
#endif
        EncoderFilter();
        break;
      case 12:
        statex = mcp2.digitalRead(13);
#ifdef BOURN_ENCODERS
        e3.update(statex, state2);
#else
        e3.update(state2, statex);
#endif
        break;
      case 13:
        statex = mcp2.digitalRead(12);
#ifdef BOURN_ENCODERS
        e3.update(state2, statex);
#else
        e3.update(statex, state2);
#endif
        break;
      case 14:
        statex = mcp2.digitalRead(15);
#ifdef BOURN_ENCODERS
        e4.update(statex, state2);
#else
        e4.update(state2, statex);
#endif
        EncoderFineTune();
        break;
      case 15:
        statex = mcp2.digitalRead(14);
#ifdef BOURN_ENCODERS
        e4.update(state2, statex);
#else
        e4.update(statex, state2);
#endif
        EncoderFineTune();
        break;
      default:
        //interrupted2 = true;
        if (state2 == PRESSED) {
          G0ORXButtonPressed = (pin2+16);
        } else {
          //buttonReleased(pin2+16);
        }
        break;
    }
  FrontPanelSetLed(0,LOW);
}
  __enable_irq();  
}

#ifdef G0ORX_INCLUDED
FASTRUN
void Select() {
  if (secondaryMenuIndex == -1) {  // Doing primary menu
    secondaryMenuChoiceMade = functionPtr[mainMenuIndex]();  // These are processed in MenuProcessing.cpp
    //secondaryMenuIndex = -1;                                  // Reset secondary menu
  } else {
    secondaryMenuChoiceMade = SubmenuSelect();
  }
}

FASTRUN
void MenuPlus() {
  if (secondaryMenuIndex == -1) {  // Doing primary menu
    mainMenuIndex++;
    if (mainMenuIndex == TOP_MENU_COUNT) {  // At last menu option, so...
      mainMenuIndex = 0;                    // ...wrap around to first menu option
    }
    ShowMenu(&topMenus[mainMenuIndex], PRIMARY_MENU);
  } else {
    SubmenuNext();
  }
}

FASTRUN
void MenuMinus() {
  if (secondaryMenuIndex == -1) {  // Doing primary menu
    mainMenuIndex--;
    if (mainMenuIndex < 0) {               // At last menu option, so...
      mainMenuIndex = TOP_MENU_COUNT - 1;  // ...wrap around to first menu option
    }
    ShowMenu(&topMenus[mainMenuIndex], PRIMARY_MENU);
  } else {
    SubmenuPrevious();
  }
}

FASTRUN
void BandPlus() {
  ShowSpectrum();  //Now calls ProcessIQData and Encoders calls
  digitalWrite(bandswitchPins[currentBand], LOW);
  ButtonBandIncrease();
  digitalWrite(bandswitchPins[currentBand], HIGH);
  BandInformation();
}

FASTRUN
void BandMinus() {
  ShowSpectrum();  //Now calls ProcessIQData and Encoders calls
  digitalWrite(bandswitchPins[currentBand], LOW);
  ButtonBandDecrease();
  digitalWrite(bandswitchPins[currentBand], HIGH);
  BandInformation();
}
#endif

FASTRUN
void buttonPressed(uint8_t pin) {
  G0ORXButtonPressed = pin;  
  /*  
  switch(pin) {
    case 0: // SW1 (SELECT)
      Select();
      break;
    case 1: // SW2 (MENU+)
      MenuPlus();
      break;
    case 2: // SW3
      BandPlus();
      break;
    case 3: // SW4
      //ButtonZoom();
      break;
    case 4: // SW5 (MENU-)
      MenuMinus();
      break;
    case 5: // SW6 (Band -)
      BandMinus();
      break;
    case 6: // SW7
      ButtonFilter();
      break;;
    case 7: // SW8
      ButtonDemodMode();
      break;
    case 8: // SW9
      ButtonMode();
      break;
    case 9: // SW10
      ButtonNR();
      break;
    case 10: // SW11
      ButtonNotchFilter();  int val;
    case 14: // SW15
      break;
    case 15: // SW16
      ButtonFreqIncrement();
      break;
    case 16: // SW17
      break;
    case 17: // SW18
      break;
    case 18: // E1SW
      break;
    case 19: // E2SW
      break;
    case 20: // E3SW
      break;
    case 21: // E4SW
      break;
    case 22: // LED1 OUTPUT (should not happen)
      break;
    case 23: // LED2 OUTPUT (should not happen)
      break;
  }
*/
}

FASTRUN
void buttonReleased(uint8_t pin) {
  /*
  switch(pin) {
    case 0: // SW1
      break;
    case 1: // SW2
      break;
    case 2: // SW3
      break;
    case 3: // SW4
      break;
    case 4: // SW5
      break;
    case 5: // SW6
      break;__disable_irq();
    case 6: // SW7
        break;;
    case 7: // SW8
      break;
    case 8: // SW9
      break;
    case 9: // SW10
      break;
    case 10: // SW11
      break;
    case 11: // SW12
      break;
    case 12: // SW13
      break;
    case 13: // SW14
      break;
    case 14: // SW15
      break;
    case 15: // SW16
      break;
    case 16: // SW17
      break;
    case 17: // SW18
      break;
    case 18: // E1SW
      break;
    case 19: // E2SW
      break;
    case 20: // E3SW
      break;
    case 21: // E4SW
      break;
    case 22: // LED1 OUTPUT (should not happen)
      break;
    case 23: // LED2 OUTPUT (should not happen)
      break;
  }
*/
}

void FrontPanelInit() {

  // just in case not already done - should have been done in si5351 library
  Wire.begin();

  // set I2C bus to 1.7MHz
  Wire.setClock(1700000);

  if (!mcp1.begin_I2C(MCP23017_ADDR_1)) {
    Serial.println("MCP1 begin_I2C Error.");
    return;
  }

  if (!mcp2.begin_I2C(MCP23017_ADDR_2)) {
    Serial.println("MCP1 begin_I2C Error.");
    return;    
  }

  // setup the mcp23017 devices
  mcp1.setupInterrupts(true, true, LOW);
  mcp2.setupInterrupts(true, true, LOW);

  // setup switches 1..16
  for (int i = 0; i < 16; i++) {
    mcp1.pinMode(i, INPUT_PULLUP);
    mcp1.setupInterruptPin(i, CHANGE);
  }

  // setup switches 17..18 and Encoder switches 1..4 (note 6 and 7 are output LEDs)
  for (int i = 0; i < 6; i++) {
    mcp2.pinMode(i, INPUT_PULLUP);
    mcp2.setupInterruptPin(i, CHANGE);
  }

  mcp2.pinMode(LED_1_PORT, OUTPUT);  // LED1
  mcp2.digitalWrite(LED_1_PORT, LOW);
  mcp2.pinMode(LED_2_PORT, OUTPUT);  // LED2
  mcp2.digitalWrite(LED_2_PORT, LOW);

  // setup encoders 1..4 A and B
  for (int i = 8; i < 16; i++) {
    mcp2.pinMode(i, INPUT_PULLUP);
    mcp2.setupInterruptPin(i, CHANGE);
  }

  // clear interrupts
  mcp1.readGPIOAB(); // ignore any return value
  mcp2.readGPIOAB(); // ignore any return value

  pinMode(INT_PIN_1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_1), interrupt1, FALLING);

  pinMode(INT_PIN_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN_2), interrupt2, FALLING);
}

FASTRUN
void FrontPanelSetLed(int led, uint8_t state) {
  switch (led) {
    case LED1:
      mcp2.digitalWrite(LED_1_PORT, state);
      break;
    case LED2:
      mcp2.digitalWrite(LED_2_PORT, state);
      break;
  }
}
#endif
