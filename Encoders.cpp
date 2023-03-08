#ifndef BEENHERE
#include "SDT.h"
#endif

/*****
  Purpose: EncoderFilter

  Parameter list:
    void

  Return value;
    void
    Modified AFP21-12-15
*****/
void FilterSetSSB()
{
  long filter_change;

  // SSB
  if (filter_pos != last_filter_pos) {
    tft.fillRect((MAX_WATERFALL_WIDTH + SPECTRUM_LEFT_X) / 2 - filterWidth, SPECTRUM_TOP_Y + 17, filterWidth, SPECTRUM_HEIGHT - 20, RA8875_BLACK); // Erase old filter background
    filter_change = (filter_pos - last_filter_pos);
    if (filter_change >= 1) {
      filterWidth--;
      if (filterWidth < 10)
        filterWidth = 10;
    }
    if (filter_change <= -1) {
      filterWidth++;
      if (filterWidth > 100)
        filterWidth = 50;
    }
    last_filter_pos = filter_pos;
    // =============  AFP 10-27-22
    switch (bands[currentBand].mode) {
      case DEMOD_LSB :
        if (switchFilterSideband == 0)      // "0" = normal, "1" means change opposite filter
        {
          bands[currentBand].FLoCut = bands[currentBand].FLoCut + filter_change * 50 * ENCODER_FACTOR;
          //fHiCutOld= bands[currentBand].FHiCut;
          FilterBandwidth();
        } else if (switchFilterSideband == 1) {
          //if (abs(bands[currentBand].FHiCut) < 500) {
          bands[currentBand].FHiCut = bands[currentBand].FHiCut + filter_change * 50 * ENCODER_FACTOR;
          fLoCutOld = bands[currentBand].FLoCut;
        }
        break;
      case DEMOD_USB :
        if (switchFilterSideband == 0) {
          bands[currentBand].FHiCut = bands[currentBand].FHiCut - filter_change * 50 * ENCODER_FACTOR;
          //bands[currentBand].FLoCut= fLoCutOld;
          FilterBandwidth();
        } else if (switchFilterSideband == 1) {
          bands[currentBand].FLoCut = bands[currentBand].FLoCut - filter_change * 50 * ENCODER_FACTOR;
          // bands[currentBand].FHiCut= fHiCutOld;
        }
        break;
      case DEMOD_AM :
        bands[currentBand].FHiCut = bands[currentBand].FHiCut - filter_change * 50 * ENCODER_FACTOR;
        bands[currentBand].FLoCut = -bands[currentBand].FHiCut;
        FilterBandwidth();
        InitFilterMask();
        break;
      case DEMOD_SAM : // AFP 11-03-22
        bands[currentBand].FHiCut = bands[currentBand].FHiCut - filter_change * 50 * ENCODER_FACTOR;
        bands[currentBand].FLoCut = -bands[currentBand].FHiCut;
        FilterBandwidth();
        InitFilterMask();
        break;
    }
    // =============  AFP 10-27-22

    //ControlFilterF();
    Menu2 = MENU_F_LO_CUT;      // set Menu2 to MENU_F_LO_CUT
    FilterBandwidth();
    //    centerTuneFlag = 1; //AFP 10-03-22
    //SetFreq();               //  AFP 10-04-22
    ShowFrequency();
  }
  //notchPosOld = filter_pos;

}


/*****
  Purpose: EncoderCenterTune
  Parameter list:
    void
  Return value;
    void
*****/
void EncoderCenterTune()
{
  long tuneChange = 0L;
  unsigned char result  = tuneEncoder.process();   // Read the encoder

  if (result == 0)                                 // Nothing read
    return;

  centerTuneFlag = 1; //AFP 10-03-22

  if (T41State == CW_XMIT && decoderFlag == DECODE_ON) {        // No reason to reset if we're not doing decoded CW AFP 09-27-22
    ResetHistograms();
  }
  if (result == DIR_CW) {
    tuneChange = 1L;
  } else {
    tuneChange = -1L;
  }

  centerFreq += ((long)freqIncrement * tuneChange);                    // tune the master vfo

  //  if (centerFreq != oldFreq) {           // If the frequency has changed...
  //=== AFP 10-19-22

  TxRxFreq = centerFreq + NCOFreq;
  lastFrequencies[currentBand][activeVFO] = TxRxFreq;

  //currentFreqA= centerFreq + NCOFreq;
  DrawBandWidthIndicatorBar(); // AFP 10-20-22
  //FilterOverlay(); // AFP 10-20-22
  ShowFrequency();
  BandInformation();

  //  }
}

/*****
  Purpose: Encoder volume control

  Parameter list:
    void

  Return value;
    int               0 means encoder didn't move; otherwise it moved
*****/
void EncoderVolume()      //============================== AFP 10-22-22  Begin new
{
  char result;
  result = volumeEncoder.process();    // Read the encoder

  if (result == 0) {                                    // Nothing read
    return;
  }
  switch (result) {
    case DIR_CW:                          // Turned it clockwise, 16
      adjustVolEncoder = 1;
      break;

    case DIR_CCW:                         // Turned it counter-clockwise
      adjustVolEncoder = -1;
      break;
  }
  audioVolume += adjustVolEncoder;

  if (audioVolume > 100) {                // In range?
    audioVolume = 100;
  } else {
    if (audioVolume < 0) {
      audioVolume = 0;
    }
  }
  //set flags for IC calibration

  volumeChangeFlag = true;        // Need this because of unknown timing in display updating.

}     //============================== AFP 10-22-22  End new

/*****
  Purpose: Use the encoder to change the value of a number in some other function

  Parameter list:
    int minValue                the lowest value allowed
    int maxValue                the largest value allowed
    int startValue              the numeric value to begin the count
    int increment               the amount by which each increment changes the value
    char prompt[]               the input prompt
  Return value;
    int                         the new value
*****/
float GetEncoderValueLive(float minValue, float maxValue, float startValue, float increment, char prompt[]) //AFP 10-22-22
{
  float currentValue = startValue;
  tft.setFontScale( (enum RA8875tsize) 1);
  tft.setTextColor(RA8875_WHITE);
  tft.fillRect(250, 0, 280, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setCursor(257, 1);
  tft.print(prompt);
  tft.setCursor(440, 1);
  if (abs(startValue) > 2) {
    tft.print(startValue, 0);
  } else {
    tft.print(startValue, 3);
  }
  //while (true) {
  if (filterEncoderMove != 0) {
    currentValue += filterEncoderMove * increment;    // Bump up or down...
    if (currentValue < minValue)
      currentValue = minValue;
    else if (currentValue > maxValue)
      currentValue = maxValue;

    tft.fillRect(449, 0, 80, CHAR_HEIGHT, RA8875_MAGENTA);
    tft.setCursor(440, 1);
    if (abs(startValue) > 2) {
      tft.print(startValue, 0);
    } else {
      tft.print(startValue, 3);
    }
    filterEncoderMove = 0;
  }
  return currentValue;
}



/*****
  Purpose: Use the encoder to change the value of a number in some other function

  Parameter list:
    int minValue                the lowest value allowed
    int maxValue                the largest value allowed
    int startValue              the numeric value to begin the count
    int increment               the amount by which each increment changes the value
    char prompt[]               the input prompt
  Return value;
    int                         the new value
*****/
int GetEncoderValue(int minValue, int maxValue, int startValue, int increment, char prompt[])
{
  int currentValue = startValue;
  int val;

  tft.setFontScale( (enum RA8875tsize) 1);

  tft.setTextColor(RA8875_WHITE);
  tft.fillRect(250, 0, 280, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setCursor(257, 1);
  tft.print(prompt);
  tft.setCursor(470, 1);
  tft.print(startValue);

  while (true) {
    if (filterEncoderMove != 0) {
      currentValue += filterEncoderMove * increment;    // Bump up or down...
      if (currentValue < minValue)
        currentValue = minValue;
      else if (currentValue > maxValue)
        currentValue = maxValue;

      tft.fillRect(465, 0, 65, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(470, 1);
      tft.print(currentValue);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                     // Read the ladder value
    //MyDelay(100L); //AFP 09-22-22
    if (val != -1  && val < (EEPROMData.switchValues[0] + WIGGLE_ROOM)) {
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == MENU_OPTION_SELECT) {                  // Make a choice??
        return currentValue;
      }
    }
  }
}

/*****
  Purpose: Allows quick setting of WPM without going through a menu

  Parameter list:
    void

  Return value;
    int           the current WPM
*****/
int SetWPM()
{
  int val;
  long lastWPM = currentWPM;

  tft.setFontScale( (enum RA8875tsize) 1);

  tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor(SECONDARY_MENU_X + 1, MENUS_Y + 1);
  tft.print("current WPM:");
  tft.setCursor(SECONDARY_MENU_X + 200, MENUS_Y + 1);
  tft.print(currentWPM);

  while (true) {
    if (filterEncoderMove != 0) {                     // Changed encoder?
      currentWPM += filterEncoderMove;                // Yep
      lastWPM = currentWPM;
      if (lastWPM < 0)
        lastWPM = 5;
      else if (lastWPM > MAX_WPM)
        lastWPM = MAX_WPM;

      tft.fillRect(SECONDARY_MENU_X + 200, MENUS_Y + 1, 50, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X + 200, MENUS_Y + 1);
      tft.print(lastWPM);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                              // Read pin that controls all switches
    val = ProcessButtonPress(val);
    if (val == MENU_OPTION_SELECT) {                             // Make a choice??
      currentWPM = lastWPM;
      EEPROMData.currentWPM = currentWPM;
      UpdateWPMField();
      break;
    }
  }
  tft.setTextColor(RA8875_WHITE);
  EraseMenus();
  return currentWPM;
}

/*****
  Purpose: Determines how long the transmit relay remains on after last CW atom is sent.

  Parameter list:
    void

  Return value;
    long            the delay length in milliseconds
*****/
long SetTransmitDelay()                               // new function JJP 9/1/22
{
  int val;
  long lastDelay = cwTransmitDelay;
  long increment = 250;                               // Means a quarter second change per detent

  tft.setFontScale( (enum RA8875tsize) 1);

  tft.fillRect(SECONDARY_MENU_X - 150, MENUS_Y, EACH_MENU_WIDTH + 150, CHAR_HEIGHT, RA8875_MAGENTA);  // scoot left cuz prompt is long
  tft.setTextColor(RA8875_WHITE);
  tft.setCursor(SECONDARY_MENU_X - 149, MENUS_Y + 1);
  tft.print("current delay:");
  tft.setCursor(SECONDARY_MENU_X + 79, MENUS_Y + 1);
  tft.print(cwTransmitDelay);

  while (true) {
    if (filterEncoderMove != 0) {                     // Changed encoder?
      lastDelay += filterEncoderMove * increment;     // Yep
      if (lastDelay < 0L)
        lastDelay = 250L;

      tft.fillRect(SECONDARY_MENU_X + 80, MENUS_Y + 1, 200, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X + 79, MENUS_Y + 1);
      tft.print(lastDelay);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                              // Read pin that controls all switches
    val = ProcessButtonPress(val);
    //MyDelay(150L);  //ALF 09-22-22
    if (val == MENU_OPTION_SELECT) {                             // Make a choice??
      cwTransmitDelay = lastDelay;
      EEPROMData.cwTransmitDelay = cwTransmitDelay;
      //      EEPROMWrite();
      break;
    }
  }
  tft.setTextColor(RA8875_WHITE);
  EraseMenus();
  return cwTransmitDelay;
}
/*****
  Purpose: Fine tune control.

  Parameter list:
    void

  Return value;
    void               cannot return value from interrupt
*****/
FASTRUN                   // Causes function to be allocated in RAM1 at startup for fastest performance.
void EncoderFineTune()
{
  char result;

  result = fineTuneEncoder.process();       // Read the encoder
//  MyDelay(50L);
  if (result == 0) {                        // Nothing read
    fineTuneEncoderMove = 0L;
    return;
  } else {
    if (result == DIR_CW) {                 // 16 = CW, 32 = CCW
      fineTuneEncoderMove = 1L;
    } else {
      fineTuneEncoderMove = -1L;
    }
  }
  //if (spectrum_zoom == 0) {
  NCOFreq += stepFT * fineTuneEncoderMove; //AFP 11-01-22
  centerTuneFlag = 1;
  SubFineTune();
}

void SubFineTune()
{
  // ============  AFP 10-28-22
  if (activeVFO == VFO_A) {
    currentFreqA = centerFreq + NCOFreq;   //AFP 10-05-22   
  } else {
    currentFreqB = centerFreq + NCOFreq;  //AFP 10-05-22
  }
  // ===============  Recentering at band edges ==========
  if (spectrum_zoom != 0) {
    if (NCOFreq > (95000 / (1 << spectrum_zoom)) || NCOFreq < (-93000 / (1 << spectrum_zoom))) {
      NCOFreq    = 0L;
      if (activeVFO == VFO_A) {                           // JJP 2/25/23
        centerFreq = TxRxFreq = currentFreqA;             // JJP 2/25/23
        lastFrequencies[currentBand][VFO_A] = TxRxFreq;  // JJP 2/25/23
      } else {                                            // JJP 2/25/23
        centerFreq = TxRxFreq = currentFreqB;             // JJP 2/25/23    
        lastFrequencies[currentBand][VFO_B] = TxRxFreq;  // JJP 2/25/23
      }
    }
  } else {
    if (NCOFreq > (142000) || NCOFreq < (-43000)) {  // Offset tuning window in zoom 1x
      NCOFreq    = 0L;
      if (activeVFO == VFO_A) {                           // JJP 2/25/23
        centerFreq = TxRxFreq = currentFreqA;             // JJP 2/25/23
        lastFrequencies[currentBand][VFO_A] = TxRxFreq;  // JJP 2/25/23
      } else {                                            // JJP 2/25/23
        centerFreq = TxRxFreq = currentFreqB;             // JJP 2/25/23    
        lastFrequencies[currentBand][VFO_B] = TxRxFreq;  // JJP 2/25/23
      }
    }
    centerTuneFlag = 1;
  }
  fineTuneEncoderMove = 0L;
  if (activeVFO == VFO_A) {
    TxRxFreq = currentFreqA;
    lastFrequencies[currentBand][VFO_A] = TxRxFreq;  // JJP 2/25/23
  } else {
    TxRxFreq = currentFreqB;
    lastFrequencies[currentBand][VFO_B] = TxRxFreq;  // JJP 2/25/23
  }
}
FASTRUN                   // Causes function to be allocated in RAM1 at startup for fastest performance.



void EncoderFilter()
{
  char result;

  result = filterEncoder.process();   // Read the encoder

  if (result == 0) {
    //    filterEncoderMove = 0;// Nothing read
    return;
  }

  switch (result) {
    case DIR_CW:                          // Turned it clockwise, 16
      filterEncoderMove = 1;
      //filter_pos = last_filter_pos - 5 * filterEncoderMove;  // AFP 10-22-22
      break;

    case DIR_CCW:                         // Turned it counter-clockwise
      filterEncoderMove = -1;
      // filter_pos = last_filter_pos - 5 * filterEncoderMove;   // AFP 10-22-22
      break;
  }
#ifdef G0ORX_WATERFALL
  if(bSettingWaterfallGrad) {
    waterfallGrad += ((float) filterEncoderMove);
    if (waterfallGrad < 0)
      waterfallGrad = 0;
    else if (waterfallGrad > 50)                 // 100% max
      waterfallGrad = 50;
/*
    tft.setFontScale( (enum RA8875tsize) 1);
    tft.setTextColor(RA8875_WHITE);
    tft.fillRect(SECONDARY_MENU_X + 180, MENUS_Y, 80, CHAR_HEIGHT, RA8875_MAGENTA);
    tft.setCursor(SECONDARY_MENU_X + 180, MENUS_Y + 1);
    tft.print(waterfallGrad);
*/
    gradientChangeFlag = true;
  } else
#endif
  if (calibrateFlag == 0) {// AFP 10-22-22
    filter_pos = last_filter_pos - 5 * filterEncoderMove;// AFP 10-22-22
  }// AFP 10-22-22
}
