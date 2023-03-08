#ifndef BEENHERE
#include "SDT.h"
#endif

/***** //AFP 10-11-22 all new
  Purpose:  Reset tuning to center

  Parameter list:
  void

  Return value;
  void
*****/
void ResetTuning() {
  if (activeVFO == VFO_A) {
    currentFreqA = centerFreq + NCOFreq;
    NCOFreq = 0L;
    TxRxFreq = centerFreq = currentFreqA;  //AFP 10-28-22
  } else {
    currentFreqB = centerFreq + NCOFreq;
    NCOFreq = 0L;
    TxRxFreq = centerFreq = currentFreqB;  //AFP 10-28-22
  }

  DrawBandWidthIndicatorBar();
  BandInformation();
  ShowFrequency();
  centerTuneFlag = 1;
}
// ===== End AFP 10-11-22

/*****
  Purpose: SetFrequency

  Parameter list:
    void

  Return value;
    void

  CAUTION: SI5351_FREQ_MULT is set in the si5253.h header file and is 100UL
*****/
void SetFreq() {  //AFP 09-22-22

  // NEVER USE AUDIONOINTERRUPTS HERE: that introduces annoying clicking noise with every frequency change
  // SI5351_FREQ_MULT is 100ULL, MASTER_CLK_MULT is 4;

  if (xmtMode == SSB_MODE) {
    Clk2SetFreq = (((centerFreq)*SI5351_FREQ_MULT) + IFFreq * SI5351_FREQ_MULT) * MASTER_CLK_MULT;  // AFP 09-27-22
    Clk1SetFreq = (TxRxFreq * SI5351_FREQ_MULT) * MASTER_CLK_MULT;                                  // AFP 09-27-22
  } else {
    // =========================  CW Xmit
    if (bands[currentBand].mode == DEMOD_LSB) {                                                                       // Which sideband?
      Clk2SetFreq = (((centerFreq + CWFreqShift) * SI5351_FREQ_MULT) + IFFreq * SI5351_FREQ_MULT) * MASTER_CLK_MULT;  // AFP 09-27-22
      Clk1SetFreq = (((TxRxFreq - CWFreqShift - calFreqShift) * SI5351_FREQ_MULT)) * MASTER_CLK_MULT;                 // AFP 09-27-22;
        } else {                                                              //  DEMOD_USB
      Clk2SetFreq = (((centerFreq + CWFreqShift) * SI5351_FREQ_MULT) + IFFreq * SI5351_FREQ_MULT) * MASTER_CLK_MULT;  // AFP 09-27-22
      Clk1SetFreq = (((TxRxFreq + CWFreqShift + calFreqShift) * SI5351_FREQ_MULT)) * MASTER_CLK_MULT;                 // AFP 10-01-22;
    }
  }
  // =========================  End CW Xmit

#ifdef G0ORX_FRONTPANEL
  if ((my_ptt == LOW ) && (currentBand == BAND_10M )) {
#else
  if ((digitalRead(PTT) == LOW ) && (currentBand == BAND_10M )) {
#endif
    Clk2SetFreq = (((7000000) * SI5351_FREQ_MULT) + IFFreq * SI5351_FREQ_MULT) * MASTER_CLK_MULT;  //AFP 08-22-22
  } else {
    Clk2SetFreq = (((centerFreq)*SI5351_FREQ_MULT) + IFFreq * SI5351_FREQ_MULT) * MASTER_CLK_MULT;
  }
  //=====================  AFP 10-03-22 =================
#ifdef G0ORX_FRONTPANEL
  __disable_irq();
#endif  
    si5351.set_freq(Clk2SetFreq, SI5351_CLK2);

  if (xrState == RECEIVE_STATE) {     // Turn CLK1 off during Receive and on for Transmit  AFP 10-02-22
    si5351.set_freq(0, SI5351_CLK1);  // CLK1 off during receive to prevent birdies
  } else {
    si5351.set_freq(Clk1SetFreq, SI5351_CLK1);  // TRANSMIT_STATE
  }
#ifdef G0ORX_FRONTPANEL
  __enable_irq();
#endif
  //=====================  AFP 10-03-22 =================
  DrawFrequencyBarValue();
}



/*****
  Purpose: Places the Fast Tune cursor in the center of the spectrum display

  Parameter list:

  Return value;
    void
*****/
void CenterFastTune() {
  tft.drawFastVLine(oldCursorPosition, SPECTRUM_TOP_Y + 20, SPECTRUM_HEIGHT - 27, RA8875_BLACK);
  tft.drawFastVLine(newCursorPosition, SPECTRUM_TOP_Y + 20, SPECTRUM_HEIGHT - 27, RA8875_RED);
}

/*****
  Purpose: Purpose is to sety VFOa to receive frequency and VFOb to the transmit frequency

  Parameter list:
    void

  Return value;
    int           the offset as an int

  CAUTION: SI5351_FREQ_MULT is set in the si5253.h header file and is 100UL
*****/
int DoSplitVFO() {
  char freqBuffer[15];
  int val;
  long chunk = SPLIT_INCREMENT;
  long splitOffset;

  tft.drawRect(INFORMATION_WINDOW_X - 10, INFORMATION_WINDOW_Y - 2, 260, 200, RA8875_MAGENTA);
  tft.fillRect(INFORMATION_WINDOW_X - 8, INFORMATION_WINDOW_Y, 250, 185, RA8875_BLACK);  // Clear volume field
  tft.setFontScale((enum RA8875tsize)1);
  tft.setCursor(INFORMATION_WINDOW_X + 10, INFORMATION_WINDOW_Y + 5);
  tft.print("xmit offset: ");

  splitOffset = chunk;  // Set starting offset to 500Hz
  tft.setTextColor(RA8875_GREEN);
  tft.setCursor(INFORMATION_WINDOW_X + 60, INFORMATION_WINDOW_Y + 90);
  tft.print(splitOffset);
  tft.print("Hz  ");

  while (true) {
    if (filterEncoderMove != 0) {  // Changed encoder?
      splitOffset += filterEncoderMove * chunk;
      tft.fillRect(INFORMATION_WINDOW_X + 60, INFORMATION_WINDOW_Y + 90, 150, 50, RA8875_BLACK);
      tft.setCursor(INFORMATION_WINDOW_X + 60, INFORMATION_WINDOW_Y + 90);
      tft.print(splitOffset);
      tft.print("Hz  ");
    }
    filterEncoderMove = 0L;

    val = ReadSelectedPushButton();  // Read pin that controls all switches
    val = ProcessButtonPress(val);
    MyDelay(150L);
    if (val == MENU_OPTION_SELECT) {  // Make a choice??
      Clk1SetFreq += splitOffset;     // New transmit frequency // AFP 09-27-22
      UpdateInfoWindow();
      filterEncoderMove = 0L;
      break;
    }
  }
  currentFreqB = currentFreqA + splitOffset;
  FormatFrequency(currentFreqB, freqBuffer);
  tft.fillRect(FREQUENCY_X_SPLIT, FREQUENCY_Y - 12, VFOB_PIXEL_LENGTH, FREQUENCY_PIXEL_HI, RA8875_BLACK);
  tft.setCursor(FREQUENCY_X_SPLIT, FREQUENCY_Y);
  tft.setFont(&FreeMonoBold24pt7b);
  tft.setTextColor(RA8875_GREEN);
  tft.print(freqBuffer);  // Show VFO_A

  tft.setFont(&FreeMonoBold18pt7b);
  FormatFrequency(currentFreqA, freqBuffer);
  tft.setTextColor(RA8875_LIGHT_GREY);
  tft.setCursor(FREQUENCY_X, FREQUENCY_Y + 6);
  tft.print(freqBuffer);  // Show VFO_A

  tft.useLayers(1);  //mainly used to turn on layers!
  tft.layerEffect(OR);
  tft.writeTo(L2);
  tft.clearMemory();
  tft.writeTo(L1);

  tft.setFont(&FreeMono9pt7b);
  tft.setTextColor(RA8875_RED);
  tft.setCursor(FILTER_PARAMETERS_X + 180, FILTER_PARAMETERS_Y + 6);
  tft.print("Split Active");

  tft.setFontDefault();
  return (int)splitOffset;  // Can be +/-
}
