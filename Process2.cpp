#ifndef BEENHERE
#include "SDT.h"
#endif


/*****
  Purpose: Combined input/ output for the purpose of calibrating the receive IQ

   Parameter List:
      void

   Return value:
      void

   CAUTION: Assumes a spaces[] array is defined
 *****/
void DoReceiveCalibrate() {
  float correctionIncrement = 0.01; //AFP 2-7-23
  int corrChange = 0;

  //IQChoice = 0;  // AFP 02-09-23
  calFreqShift = -24000;
  tft.setFontScale( (enum RA8875tsize) 0);
  tft.setTextColor(RA8875_GREEN);
  tft.setCursor(350, 160);
  tft.print("user1 - Gain/Phase");
  tft.setCursor(350, 175);
  tft.print("User2 - Incr");
  tft.setTextColor(RA8875_CYAN);
  tft.fillRect(350, 125, 100, tft.getFontHeight(), RA8875_BLACK);
  tft.setCursor(400, 125);
  tft.print("dB");
  tft.setCursor(350, 110);
  tft.print("Incr= ");
  tft.setCursor(400, 110);
  tft.print(correctionIncrement, 3);
  currentBand = currentBandA;
  while (1) {
    // ln(" In While()");
    ShowSpectrum2();
    // ============
    int val;
    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == UNUSED_1) {
        IQCalType = !IQCalType;
      }
    }
    if (val == UNUSED_2) {
      corrChange = !corrChange;
      if (corrChange == 1) {
        correctionIncrement = 0.001; //AFP 2-7-23
      } else { //if (corrChange == 0)                   // corrChange is a toggle, so if not needed JJP 2/5/23
        correctionIncrement = 0.01; //AFP 2-7-23
      }
      tft.setFontScale( (enum RA8875tsize) 0);
      tft.fillRect(400, 110, 50, tft.getFontHeight(), RA8875_BLACK);
      tft.setCursor(400, 110);
      tft.print(correctionIncrement, 3);
    }
    // ========== // AFP 2-11-23
    if (IQCalType == 0) { // AFP 2-11-23
      IQAmpCorrectionFactor[currentBandA] = GetEncoderValueLive(-2.0, 2.0, IQAmpCorrectionFactor[currentBandA], correctionIncrement, (char *)"IQ Gain");
    } else {
      IQPhaseCorrectionFactor[currentBandA] = GetEncoderValueLive(-2.0, 2.0, IQPhaseCorrectionFactor[currentBandA], correctionIncrement, (char *)"IQ Phase");
    }
    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == MENU_OPTION_SELECT) {                  // Yep. Make a choice??  I don't have that any more.
        tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH + 35, CHAR_HEIGHT, RA8875_BLACK);
        //IQAmpCorrectionFactor[currentBandA]   = IQAmpCorrectionFactor[currentBandA];//AFP 02-09-23
        //IQPhaseCorrectionFactor[currentBandA] = IQPhaseCorrectionFactor[currentBandA];//AFP 02-09-23
      }
    }
    //==
    updateDisplayFlag = 1;
//    int pushButtonSwitchIndex = -1;
//    int valPin;
    //    valPin = ReadSelectedPushButton();                        // Poll UI push buttons
    //    if (valPin != BOGUS_PIN_READ) {                           // If a button was pushed...
    //      pushButtonSwitchIndex = ProcessButtonPress(valPin);
    //      ExecuteButtonPress(pushButtonSwitchIndex);
    //    }
    // ================= // AFP 2-11-23
    //===// AFP 2-11-23
    digitalWrite(MUTE, LOW);                //turn off mute
    xrState = RECEIVE_STATE;
    ShowTransmitReceiveStatus();
    T41State = CW_RECEIVE ;
    modeSelectInR.gain(0, 1);
    modeSelectInL.gain(0, 1);
    modeSelectInExR.gain(0, 0);
    modeSelectInExL.gain(0, 0);

    modeSelectOutL.gain(0, 1);
    modeSelectOutR.gain(0, 1);
    modeSelectOutL.gain(1, 0);
    modeSelectOutR.gain(1, 0);

    modeSelectOutExL.gain(0, 1);
    modeSelectOutExR.gain(0, 1);
    //==== // AFP 2-11-23
    centerTuneFlag = 1;
    //activeVFO = VFO_A;
    //centerFreq = lastFrequencies[currentBandA][1];

    //NCOFreq = 0L;

    xrState = TRANSMIT_STATE;
    ShowSpectrum2();

    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == MENU_OPTION_SELECT) {                  // Yep. Make a choice??
        tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH + 35, CHAR_HEIGHT, RA8875_BLACK);
        EEPROMData.IQAmpCorrectionFactor[currentBandA]   = IQAmpCorrectionFactor[currentBandA] ;
        EEPROMData.IQPhaseCorrectionFactor[currentBandA] = IQPhaseCorrectionFactor[currentBandA];
        //EEPROMWrite();
        IQChoice = 6;
        break;
      }
    }
  }
  calOnFlag = 0;

  return;

  centerTuneFlag = 1;
  RedrawDisplayScreen();
}

/*****
  Purpose: Combined input/ output for the purpose of calibrating the transmit IQ

   Parameter List:
      void

   Return value:
      void

   CAUTION: Assumes a spaces[] array is defined
 *****/
void DoXmitCalibrate() {
  float correctionIncrement = 0.01; // AFP 2-11-23
  int corrChange = 0;
  int val;

  //IQEXChoice = 0;

  tft.setFontScale( (enum RA8875tsize) 0);
  tft.setTextColor(RA8875_GREEN);
  tft.setCursor(350, 160);
  tft.print("user1 - Gain/Phase");
  tft.setCursor(350, 175);
  tft.print("User2 - Incr");
  tft.setTextColor(RA8875_CYAN);
  tft.fillRect(350, 125, 100, tft.getFontHeight(), RA8875_BLACK);
  tft.setCursor(400, 125);
  tft.print("dB");
  tft.setCursor(350, 110);
  tft.print("Incr= ");
  tft.setCursor(400, 110);
  tft.print(correctionIncrement, 3);
  currentBand = currentBandA;
  while (true) {


    ShowSpectrum2();
    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == UNUSED_1) {
        IQEXChoice = !IQEXChoice;
      }
    }
    if (val == UNUSED_2) {
      corrChange = !corrChange;
      if (corrChange == 1) {                            // Toggle increment value
        correctionIncrement = 0.001;  // AFP 2-11-23
      } else {
        correctionIncrement = 0.01;  // AFP 2-11-23
      }
      tft.setFontScale( (enum RA8875tsize) 0);
      tft.fillRect(400, 110, 50, tft.getFontHeight(), RA8875_BLACK);
      tft.setCursor(400, 110);
      tft.print(correctionIncrement, 3);
    }

    //============ // AFP 2-11-23
    if (IQEXChoice == 0) {
      IQXAmpCorrectionFactor[currentBandA] = GetEncoderValueLive(-2.0, 2.0, IQXAmpCorrectionFactor[currentBandA], correctionIncrement, (char *)"IQ Gain X");
    } else {
      IQXPhaseCorrectionFactor[currentBandA] = GetEncoderValueLive(-2.0, 2.0, IQXPhaseCorrectionFactor[currentBandA], correctionIncrement, (char *)"IQ Phase X");
    }
    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == MENU_OPTION_SELECT) {                  // Yep. Make a choice??  I don't have that any more.
        tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH + 35, CHAR_HEIGHT, RA8875_BLACK);
        EEPROMData.IQXAmpCorrectionFactor[currentBandA]   = IQAmpCorrectionFactor[currentBandA];
        EEPROMData.IQXPhaseCorrectionFactor[currentBandA] = IQPhaseCorrectionFactor[currentBandA];
      }
    }
    // ================
    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == MENU_OPTION_SELECT) {                  // Yep. Make a choice??  I don't have that any more.
        tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH + 35, CHAR_HEIGHT, RA8875_BLACK);
        spectrum_zoom = 1;
        EEPROMData.IQXPhaseCorrectionFactor[currentBandA] = IQXPhaseCorrectionFactor[currentBandA];
        EEPROMData.IQXAmpCorrectionFactor[currentBandA]   = IQXAmpCorrectionFactor[currentBandA];
      }
    }
    //== // AFP 2-11-23
    updateDisplayFlag = 1;
    //========== //AFP 2-7-23
    digitalWrite(MUTE, LOW);                //turn off mute
    xrState = RECEIVE_STATE;
    ShowTransmitReceiveStatus();
    T41State = CW_RECEIVE ;
    modeSelectInR.gain(0, 1);
    modeSelectInL.gain(0, 1);
    modeSelectInExR.gain(0, 0);
    modeSelectInExL.gain(0, 0);

    modeSelectOutL.gain(0, 1);
    modeSelectOutR.gain(0, 1);
    modeSelectOutL.gain(1, 0);
    modeSelectOutR.gain(1, 0);

    modeSelectOutExL.gain(0, 1);
    modeSelectOutExR.gain(0, 1);

    //============  //AFP 2-7-23
    centerTuneFlag = 1;
    centerFreq = TxRxFreq;
    NCOFreq = 0L;

    xrState = TRANSMIT_STATE;
    ShowSpectrum2();
    val = ReadSelectedPushButton();
    if (val != BOGUS_PIN_READ) {                        // Any button press??
      val = ProcessButtonPress(val);                    // Use ladder value to get menu choice
      if (val == MENU_OPTION_SELECT) {                  // Yep. Make a choice??
        tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH + 35, CHAR_HEIGHT, RA8875_BLACK);

        //        EEPROMWrite();
        IQChoice = 6; // AFP 2-11-23
        break;
      }
    }
  }
  calOnFlag = 0;
  return;
  centerTuneFlag = 1;
  RedrawDisplayScreen();
}

/*****
  Purpose: Combined input/ output for the purpose of calibrating the transmit IQ

   Parameter List:
      void

   Return value:
      void

   CAUTION: Assumes a spaces[] array is defined
 *****/
void ProcessIQData2()
{
  uint32_t N_BLOCKS_EX = N_B_EX;
  float bandCouplingFactor[5] = {0.5, 0.5, 0.35, 0.15, 0.5}; // AFP 2-11-23
  float bandOutputFactor; // AFP 2-11-23
  float rfGainValue;   // AFP 2-11-23
  float recBandFactor[5] = {1.0, 1.0, 10.0, 10.0, 10.0}; // AFP 2-11-23
  /**********************************************************************************  AFP 12-31-20
        Get samples from queue buffers
        Teensy Audio Library stores ADC data in two buffers size=128, Q_in_L and Q_in_R as initiated from the audio lib.
        Then the buffers are read into two arrays sp_L and sp_R in blocks of 128 up to N_BLOCKS.  The arrarys are
        of size BUFFER_SIZE * N_BLOCKS.  BUFFER_SIZE is 128.
        N_BLOCKS = FFT_LENGTH / 2 / BUFFER_SIZE * (uint32_t)DF; // should be 16 with DF == 8 and FFT_LENGTH = 512
        BUFFER_SIZE*N_BLOCKS = 2024 samples
     **********************************************************************************/

  bandOutputFactor = bandCouplingFactor[currentBandA] * CWPowerCalibrationFactor[currentBandA] / CWPowerCalibrationFactor[1]; //AFP 2-7-23
  if (IQChoice == 2) {

    arm_scale_f32 (cosBuffer4, bandOutputFactor, float_buffer_L_EX, 256);  // // AFP 2-11-23 Use pre-calculated sin & cos instead of Hilbert
    arm_scale_f32 (sinBuffer4, bandOutputFactor, float_buffer_R_EX, 256);  // // AFP 2-11-23 Sidetone = 375
    if (bands[currentBandA].mode == DEMOD_LSB) {
    
      arm_scale_f32 (float_buffer_L_EX, -IQAmpCorrectionFactor[currentBandA], float_buffer_L_EX, 256);  //Adjust level of L buffer // AFP 2-11-23
      IQPhaseCorrection(float_buffer_L_EX, float_buffer_R_EX, IQXPhaseCorrectionFactor[currentBandA], 256);  // Adjust phase
    } else {
      if (bands[currentBandA].mode == DEMOD_USB) {
        arm_scale_f32 (float_buffer_L_EX, IQAmpCorrectionFactor[currentBandA], float_buffer_L_EX, 256); // AFP 2-11-23
        IQPhaseCorrection(float_buffer_L_EX, float_buffer_R_EX, IQXPhaseCorrectionFactor[currentBandA], 256);
      }
    }


  } else {
    if (IQChoice == 3) {
      arm_scale_f32 (cosBuffer3, bandOutputFactor, float_buffer_L_EX, 256);  // AFP 2-11-23 Use pre-calculated sin & cos instead of Hilbert
      arm_scale_f32 (sinBuffer3, bandOutputFactor, float_buffer_R_EX, 256);  // AFP 2-11-23 Sidetone = 3000
    }
  }
  //float rfGainValue;
  if (bands[currentBandA].mode == DEMOD_LSB) {
    arm_scale_f32 (float_buffer_L_EX, -IQXAmpCorrectionFactor[currentBandA], float_buffer_L_EX, 256);  //Adjust level of L buffer // AFP 2-11-23
    IQPhaseCorrection(float_buffer_L_EX, float_buffer_R_EX, IQXPhaseCorrectionFactor[currentBandA], 256);  // Adjust phase
  } else {
    if (bands[currentBandA].mode == DEMOD_USB) {
      arm_scale_f32 (float_buffer_L_EX, IQXAmpCorrectionFactor[currentBandA], float_buffer_L_EX, 256); // AFP 2-11-23
      IQPhaseCorrection(float_buffer_L_EX, float_buffer_R_EX, IQXPhaseCorrectionFactor[currentBandA], 256);
    }
  }
  //24KHz effective sample rate here
  arm_fir_interpolate_f32(&FIR_int1_EX_I, float_buffer_L_EX, float_buffer_LTemp, 256);
  arm_fir_interpolate_f32(&FIR_int1_EX_Q, float_buffer_R_EX, float_buffer_RTemp, 256);

  // interpolation-by-4,  48KHz effective sample rate here
  arm_fir_interpolate_f32(&FIR_int2_EX_I, float_buffer_LTemp, float_buffer_L_EX, 512);
  arm_fir_interpolate_f32(&FIR_int2_EX_Q, float_buffer_RTemp, float_buffer_R_EX, 512);



  //  192KHz effective sample rate here
  //arm_scale_f32(float_buffer_L_EX, 10, float_buffer_L_EX, 2048); //Scale to compensate for losses in Interpolation
  //arm_scale_f32(float_buffer_R_EX, 10, float_buffer_R_EX, 2048);


  // are there at least N_BLOCKS buffers in each channel available ?
  if ( (uint32_t) Q_in_L.available() > N_BLOCKS + 0 && (uint32_t) Q_in_R.available() > N_BLOCKS + 0 ) {

    for (unsigned  i = 0; i < N_BLOCKS_EX; i++) {  //N_BLOCKS_EX=16  BUFFER_SIZE=128 16x128=2048
      sp_L2 = Q_out_L_Ex.getBuffer();
      sp_R2 = Q_out_R_Ex.getBuffer();
      arm_float_to_q15 (&float_buffer_L_EX[BUFFER_SIZE * i], sp_L2, BUFFER_SIZE);
      arm_float_to_q15 (&float_buffer_R_EX[BUFFER_SIZE * i], sp_R2, BUFFER_SIZE);
      Q_out_L_Ex.playBuffer(); // play it !
      Q_out_R_Ex.playBuffer(); // play it !
    }
    usec = 0;
    // get audio samples from the audio  buffers and convert them to float
    // read in 32 blocks á 128 samples in I and Q
    for (unsigned i = 0; i < N_BLOCKS; i++) {
      sp_L1 = Q_in_R.readBuffer();
      sp_R1 = Q_in_L.readBuffer();

      /**********************************************************************************  AFP 12-31-20
          Using arm_Math library, convert to float one buffer_size.
          Float_buffer samples are now standardized from > -1.0 to < 1.0
      **********************************************************************************/
      arm_q15_to_float (sp_L1, &float_buffer_L[BUFFER_SIZE * i], BUFFER_SIZE); // convert int_buffer to float 32bit
      arm_q15_to_float (sp_R1, &float_buffer_R[BUFFER_SIZE * i], BUFFER_SIZE); // convert int_buffer to float 32bit
      Q_in_L.freeBuffer();
      Q_in_R.freeBuffer();
    }

    // Set frequency here only to minimize interruption to signal stream during tuning
    if (centerTuneFlag == 1) { //AFP 10-04-22
      SetFreq();            //AFP 10-04-22
    }                       //AFP 10-04-22
    centerTuneFlag = 0;     //AFP 10-04-22
    rfGainValue = pow(10, (float)rfGainAllBands / 20); //AFP 2-11-23
    arm_scale_f32 (float_buffer_L, rfGainValue, float_buffer_L, BUFFER_SIZE * N_BLOCKS); //AFP 2-11-23
    arm_scale_f32 (float_buffer_R, rfGainValue, float_buffer_R, BUFFER_SIZE * N_BLOCKS); //AFP 2-11-23

    /**********************************************************************************  AFP 12-31-20
      Scale the data buffers by the RFgain value defined in bands[currentBand] structure
    **********************************************************************************/
    arm_scale_f32 (float_buffer_L, recBandFactor[currentBand], float_buffer_L, BUFFER_SIZE * N_BLOCKS); //AFP 2-11-23
    arm_scale_f32 (float_buffer_R, recBandFactor[currentBand], float_buffer_R, BUFFER_SIZE * N_BLOCKS); //AFP 2-11-23

    // Manual IQ amplitude correction
    if (bands[currentBandA].mode == DEMOD_LSB) {
      arm_scale_f32 (float_buffer_L, -IQAmpCorrectionFactor[currentBandA], float_buffer_L, BUFFER_SIZE * N_BLOCKS); //AFP 04-14-22
      IQPhaseCorrection(float_buffer_L, float_buffer_R, IQPhaseCorrectionFactor[currentBandA], BUFFER_SIZE * N_BLOCKS);
    } else {
      if (bands[currentBandA].mode == DEMOD_USB) {
        arm_scale_f32 (float_buffer_L, IQAmpCorrectionFactor[currentBandA], float_buffer_L, BUFFER_SIZE * N_BLOCKS); //AFP 04-14-22
        IQPhaseCorrection(float_buffer_L, float_buffer_R, IQPhaseCorrectionFactor[currentBandA], BUFFER_SIZE * N_BLOCKS);
      }
    }
    FreqShift1();
    //spectrum_zoom = SPECTRUM_ZOOM_4;

    if (spectrum_zoom == SPECTRUM_ZOOM_1) { // && display_S_meter_or_spectrum_state == 1)
      zoom_display = 1;
      CalcZoom1Magn();  //AFP Moved to display function
    }

    if (spectrum_zoom != SPECTRUM_ZOOM_1) {
      //AFP  Used to process Zoom>1 for display
      ZoomFFTExe(BUFFER_SIZE * N_BLOCKS); // there seems to be a BUG here, because the blocksize has to be adjusted according to magnification,
      // does not work for magnifications > 8
    }

    //============================== AFP 10-22-22  Begin new

    if (auto_codec_gain == 1) {
      Codec_gain();
    }
  }
}

/*****
  Purpose: Show Spectrum display
            Note that this routine calls the Audio process Function during each display cycle,
            for each of the 512 display frequency bins.  This means that the audio is refreshed at the maximum rate
            and does not have to wait for the display to complete drawinf the full spectrum.
            However, the display data are only updated ONCE during each full display cycle,
            ensuring consistent data for the erase/draw cycle at each frequency point.

  Parameter list:
    void

  Return value;
    void
*****/
void ShowSpectrum2()  //AFP 2-10-23
{
  int centerLine              =  (MAX_WATERFALL_WIDTH + SPECTRUM_LEFT_X) / 2;
  int x1                      = 0;
  //==== // AFP 2-11-23
  float adjdB = 0.0;
  float adjAmplitude = 0.0;
  float refAmplitude = 0.0;

  //=========== // AFP 2-11-23
  tft.drawFastVLine(centerLine, SPECTRUM_TOP_Y, h, RA8875_GREEN);     // Draws centerline on spectrum display


  //tft.writeTo(L1);
  pixelnew[0] = 0;
  pixelnew[1] = 0;
  pixelold[0] = 0;
  pixelold[1] = 0;

  for (x1 = 1; x1 < MAX_WATERFALL_WIDTH - 1; x1++)  //AFP, JJP changed init from 0 to 1 for x1: out of bounds addressing in line 112
  {
    if (x1 == 1) {
      updateDisplayFlag = 1;      //Set flag so the display data are saved only once during each display refresh cycle at the start of the cycle, not 512 times
    }
    else updateDisplayFlag = 0;   //  Do not save the the display data for the remainder of the
    ProcessIQData2();              // Call the Audio process from within the display routine to eliminate conflicts with drawing the spectrum and waterfall displays
    EncoderCenterTune();                //Moved the tuning encoder to reduce lag times and interference during tuning.
    y_new  = pixelnew[x1];
    y1_new = pixelnew[x1 - 1];
    y_old  = pixelold[x1];
    y_old2 = pixelold[x1 - 1];

    //================= // AFP 2-11-23
    if (calTypeFlag == 0) {  // Receive Cal
      if (bands[currentBandA].mode == DEMOD_LSB) {
        if (x1 == 319) refAmplitude = y_new ;
        if (x1 == 449) adjAmplitude = y_new ;
      } else {
        if (bands[currentBandA].mode == DEMOD_USB) {
          if (x1 == 61) refAmplitude = y_new ;
          if (x1 == 195) adjAmplitude = y_new ;
        }
      }
    } else {
      if (calTypeFlag == 1) {  //Transmit Cal
        if (bands[currentBandA].mode == DEMOD_LSB) {
          if (x1 == 240) refAmplitude = y_new ;
          if (x1 == 304) adjAmplitude = y_new ;
        } else {
          if (bands[currentBandA].mode == DEMOD_USB) {
            if (x1 == 272) refAmplitude = y_new ;
            if (x1 == 208) adjAmplitude = y_new ;
          }
        }
      }
    }
    //=== // AFP 2-11-23
    if (y_new > base_y)      y_new = base_y;
    if (y_old > base_y)      y_old = base_y;
    if (y_old2 > base_y)    y_old2 = base_y;
    if (y1_new > base_y)    y1_new = base_y;

    if (y_new < 0)           y_new = 0;
    if (y_old < 0)           y_old = 0;
    if (y_old2 < 0)         y_old2 = 0;
    if (y1_new < 0)         y1_new = 0;

    //====== CW Receive code AFP 08-04-22  =================
    if (xmtMode == SSB_MODE) {
      tft.drawLine(x1 + 2 , spectrumNoiseFloor - y_old2, x1 + 2 , spectrumNoiseFloor - y_old , RA8875_BLACK);   // Erase old...
      tft.drawLine(x1 + 2 , spectrumNoiseFloor - y1_new, x1 + 2 , spectrumNoiseFloor - y_new , RA8875_YELLOW);  // Draw new
    }
    if (T41State == CW_RECEIVE) {
      if (currentBand < 2) {
        tft.drawLine(x1 + 5 , spectrumNoiseFloor - y_old2, x1 + 5 , spectrumNoiseFloor - y_old , RA8875_BLACK);   // Erase old...
        tft.drawLine(x1 + 5 , spectrumNoiseFloor - y1_new, x1 + 5 , spectrumNoiseFloor - y_new , RA8875_YELLOW);  // Draw new
      }
      if (currentBand >= 2) {
        tft.drawLine(x1 - 1 , spectrumNoiseFloor - y_old2, x1 - 1 , spectrumNoiseFloor - y_old , RA8875_BLACK); // Erase old...
        tft.drawLine(x1 - 1 , spectrumNoiseFloor - y1_new, x1 - 1 , spectrumNoiseFloor - y_new , RA8875_YELLOW); // Draw new
      }
    }

    //===  AFP 2-11-23
    if (calTypeFlag == 0) {  // Receive Cal
      adjdB = (adjAmplitude - refAmplitude ) / 1.95;
      tft.writeTo(L2);
      if (bands[currentBandA].mode == DEMOD_LSB) {
        tft.fillRect(449 - 5, SPECTRUM_TOP_Y, 20, h + 10, DARK_RED);
      } else {
        tft.fillRect(195 - 9, SPECTRUM_TOP_Y, 20, h + 10, DARK_RED);
      }
      //tft.writeTo(L1);
    } else { //Transmit Cal
      adjdB = (adjAmplitude - refAmplitude ) / 1.95;
      tft.writeTo(L2);
      if (bands[currentBandA].mode == DEMOD_LSB) {
        tft.fillRect(304 - 7, SPECTRUM_TOP_Y, 20, h + 10, DARK_RED);
      } else {
        if (bands[currentBandA].mode == DEMOD_USB) {   //mode == DEMOD_LSB
          tft.fillRect(208 - 10, SPECTRUM_TOP_Y, 20, h + 10, DARK_RED);
        }
        //tft.writeTo(L1);
      }
    }
    tft.writeTo(L1);
  }
  //= AFP 2-11-23
  tft.fillRect(350, 125, 50, tft.getFontHeight(), RA8875_BLACK);
  tft.setCursor(350, 125);
  tft.print(adjdB, 1);

  tft.BTE_move(WATERFALL_LEFT_X, FIRST_WATERFALL_LINE, MAX_WATERFALL_WIDTH, MAX_WATERFALL_ROWS - 2, WATERFALL_LEFT_X, FIRST_WATERFALL_LINE + 1, 1, 2);
  while (tft.readStatus());
  tft.BTE_move(WATERFALL_LEFT_X, FIRST_WATERFALL_LINE + 1, MAX_WATERFALL_WIDTH, MAX_WATERFALL_ROWS - 2, WATERFALL_LEFT_X, FIRST_WATERFALL_LINE + 1, 2);
  while (tft.readStatus());                                  // Make sure it's done.

}
