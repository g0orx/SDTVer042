/*
 * Rotary encoder library for Arduino.
 */

#ifdef G0ORX_FRONTPANEL

#ifndef G0ORX_Rotary_h
#define G0ORX_Rotary_h

// Enable this to emit codes twice per step.
//#define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS


// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Counter-clockwise step.
#define DIR_CCW 0x20

class G0ORX_Rotary
{
  public:
    G0ORX_Rotary();
    void update(unsigned char pin1State, unsigned char pin2State);
    int process();

  private:
    unsigned char state;
    int value;
};

#endif
#endif
