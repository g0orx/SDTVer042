/* Rotary encoder handler for arduino.
 *
 * Copyright 2011 Ben Buxton. Licenced under the GNU GPL Version 3.
 * Contact: bb@cactii.net
 *
 * Modified by John Melton (G0ORX) to allow feeding A/B pin states
 * to allow working with MCP23017.
 *
 */

#ifndef BEENHERE
#include "SDT.h"
#endif

#ifdef G0ORX_FRONTPANEL

//#define DEBUG_ROTARY

/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */

#define R_START 0x0

//    #define HALF_STEP

#ifdef HALF_STEP
// Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN 0x1
#define R_CW_BEGIN 0x2
#define R_START_M 0x3
#define R_CW_BEGIN_M 0x4
#define R_CCW_BEGIN_M 0x5
const unsigned char ttable[6][4] = {
  // R_START (00)
  {R_START_M,            R_CW_BEGIN,     R_CCW_BEGIN,  R_START},
  // R_CCW_BEGIN
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},
  // R_CW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},
  // R_START_M (11)
  {R_START_M,            R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},
  // R_CW_BEGIN_M
  {R_START_M,            R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},
  // R_CCW_BEGIN_M
  {R_START_M,            R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW},
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
#endif


/*
 * Constructor. Each arg is the pin number for each encoder contact.
 */
G0ORX_Rotary::G0ORX_Rotary () {
  state = R_START;
  value=0;
 }

FASTRUN
void G0ORX_Rotary::update(unsigned char pin1State, unsigned char pin2State) {
  unsigned char pinstate;
  pinstate = (pin2State << 1) | pin1State;
  state = ttable[state & 0xf][pinstate];

  switch(state & 0x30) {
    case DIR_CW:
      //Serial.println("Rotary::process: DIR_CW");
#ifdef DEBUG_ROTARY
  FrontPanelSetLed(0, 1);
#endif
      value++;
      break;
    case DIR_CCW:
      //Serial.println("Rotary::process: DIR_CCW");
#ifdef DEBUG_ROTARY
  FrontPanelSetLed(0, 0);
#endif
      value--;
      break;
    default:
      break;
  }

}

FASTRUN
int G0ORX_Rotary::process() {
  __disable_irq();
  int result=value;
  value=0;
  __enable_irq();
  if(result>0) {
#ifdef DEBUG_ROTARY
  FrontPanelSetLed(1, 1);
#endif
    result=DIR_CW;
  } else if(result<0) {
#ifdef DEBUG_ROTARY
  FrontPanelSetLed(1, 0);
#endif
    result=DIR_CCW;
  } else {
    result=DIR_NONE;
  }
  return result;
}
#endif
