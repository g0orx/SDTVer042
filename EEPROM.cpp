#ifndef BEENHERE
#include "SDT.h"
#endif

/*****
  Purpose: void EEPROMRead()

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMRead()
{
  EEPROM.get(EEPROM_BASE_ADDRESS, EEPROMData);                // Read as one large chunk

  strcpy(versionSettings, EEPROMData.versionSettings);
  AGCMode                 = EEPROMData.AGCMode;
  audioVolume             = EEPROMData.audioVolume; // 4 bytes
  rfGainAllBands          = EEPROMData.rfGainAllBands;
  spectrumNoiseFloor      = EEPROMData.spectrumNoiseFloor;    // AFP 09-26-22
  tuneIndex               = EEPROMData.tuneIndex;
  transmitPowerLevel      = EEPROMData.powerLevel;
  xmtMode                 = EEPROMData.xmtMode;                    // AFP 09-26-22
  nrOptionSelect          = EEPROMData.nrOptionSelect;     // 1 byte
  currentScale            = EEPROMData.currentScale;
  spectrum_zoom           = EEPROMData.spectrum_zoom;
  spectrum_display_scale  = EEPROMData.spectrum_display_scale;// 4 bytes

  CWFilterIndex           = EEPROMData.CWFilterIndex;  // Off
  paddleDit               = EEPROMData.paddleDit;
  paddleDah               = EEPROMData.paddleDah;
  decoderFlag             = EEPROMData.decoderFlag;
  keyType                 = EEPROMData.keyType;  // straight key = 0, keyer = 1
  currentWPM              = EEPROMData.currentWPM; // 4 bytes
  sidetoneVolume          = EEPROMData.sidetoneVolume;// 4 bytes
  cwTransmitDelay         = EEPROMData.cwTransmitDelay;   // 4 bytes

  activeVFO               = EEPROMData.activeVFO;  // 2 bytes
  freqIncrement           = EEPROMData.freqIncrement;  // 4 bytes

  currentBand             = EEPROMData.currentBand; // 4 bytes
  currentBandA            = EEPROMData.currentBandA;// 4 bytes
  currentBandB            = EEPROMData.currentBandB;// 4 bytes
  currentFreqA            = EEPROMData.currentFreqA;
  currentFreqB            = EEPROMData.currentFreqB;
  freqCorrectionFactor    = EEPROMData.freqCorrectionFactor;

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    recEQ_Level[i]        =  EEPROMData.equalizerRec[i];// 4 bytes each
  }
  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    xmtEQ_Level[i]        =  EEPROMData.equalizerXmt[i];
  }

  currentMicThreshold    = EEPROMData.currentMicThreshold;// 4 bytes      // AFP 09-22-22
  currentMicCompRatio    = EEPROMData.currentMicCompRatio;
  currentMicAttack       = EEPROMData.currentMicAttack;
  currentMicRelease      = EEPROMData.currentMicRelease;
  currentMicGain         = EEPROMData.currentMicGain;

  //  Note: switch values are read and written to EEPROM only
  switchThreshholds[0]       = EEPROMData.switchValues[0];
  switchThreshholds[1]       = EEPROMData.switchValues[1];
  switchThreshholds[2]       = EEPROMData.switchValues[2];
  switchThreshholds[3]       = EEPROMData.switchValues[3];
  switchThreshholds[4]       = EEPROMData.switchValues[4];
  switchThreshholds[5]       = EEPROMData.switchValues[5];
  switchThreshholds[6]       = EEPROMData.switchValues[6];
  switchThreshholds[7]       = EEPROMData.switchValues[7];
  switchThreshholds[8]       = EEPROMData.switchValues[8];
  switchThreshholds[9]       = EEPROMData.switchValues[9];
  switchThreshholds[10]      = EEPROMData.switchValues[10];
  switchThreshholds[11]      = EEPROMData.switchValues[11];
  switchThreshholds[12]      = EEPROMData.switchValues[12];
  switchThreshholds[13]      = EEPROMData.switchValues[13];
  switchThreshholds[14]      = EEPROMData.switchValues[14];
  switchThreshholds[15]      = EEPROMData.switchValues[15];
  switchThreshholds[16]      = EEPROMData.switchValues[16];
  switchThreshholds[17]      = EEPROMData.switchValues[17];

  LPFcoeff                   = EEPROMData.LPFcoeff;// 4 bytes
  NR_PSI                     = EEPROMData.NR_PSI;// 4 bytes
  NR_alpha                   = EEPROMData.NR_alpha;// 4 bytes
  NR_beta                    = EEPROMData.NR_beta;// 4 bytes
  omegaN                     = EEPROMData.omegaN;// 4 bytes
  pll_fmax                   = EEPROMData.pll_fmax;// 4 bytes

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    powerOutCW[i]               = EEPROMData.powerOutCW[i];
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    powerOutSSB[i]              = EEPROMData.powerOutSSB[i];
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    CWPowerCalibrationFactor[i] = EEPROMData.CWPowerCalibrationFactor[i];  // 0.019;
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    SSBPowerCalibrationFactor[i] = EEPROMData.SSBPowerCalibrationFactor[i]; // 0.008
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    IQAmpCorrectionFactor[i]    = EEPROMData.IQAmpCorrectionFactor[i];
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    IQPhaseCorrectionFactor[i]  = EEPROMData.IQPhaseCorrectionFactor[i];
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    IQXAmpCorrectionFactor[i]   = EEPROMData.IQXAmpCorrectionFactor[i];
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    IQXPhaseCorrectionFactor[i] = EEPROMData.IQXPhaseCorrectionFactor[i];
  }
  favoriteFrequencies[0]      = EEPROMData.favoriteFreqs[0];
  favoriteFrequencies[1]      = EEPROMData.favoriteFreqs[1];
  favoriteFrequencies[2]      = EEPROMData.favoriteFreqs[2];
  favoriteFrequencies[3]      = EEPROMData.favoriteFreqs[3];
  favoriteFrequencies[4]      = EEPROMData.favoriteFreqs[4];
  favoriteFrequencies[5]      = EEPROMData.favoriteFreqs[5];
  favoriteFrequencies[6]      = EEPROMData.favoriteFreqs[6];
  favoriteFrequencies[7]      = EEPROMData.favoriteFreqs[7];
  favoriteFrequencies[8]      = EEPROMData.favoriteFreqs[8];
  favoriteFrequencies[9]      = EEPROMData.favoriteFreqs[9];
  favoriteFrequencies[10]     = EEPROMData.favoriteFreqs[10];
  favoriteFrequencies[11]     = EEPROMData.favoriteFreqs[11];
  favoriteFrequencies[12]     = EEPROMData.favoriteFreqs[12];

  lastFrequencies[0][0]      = EEPROMData.lastFrequencies[0][0];
  lastFrequencies[1][0]      = EEPROMData.lastFrequencies[1][0];
  lastFrequencies[2][0]      = EEPROMData.lastFrequencies[2][0];
  lastFrequencies[3][0]      = EEPROMData.lastFrequencies[3][0];
  lastFrequencies[4][0]      = EEPROMData.lastFrequencies[4][0];
  lastFrequencies[5][0]      = EEPROMData.lastFrequencies[5][0];
  lastFrequencies[6][0]      = EEPROMData.lastFrequencies[6][0];

  lastFrequencies[0][1]      = EEPROMData.lastFrequencies[0][1];
  lastFrequencies[1][1]      = EEPROMData.lastFrequencies[1][1];
  lastFrequencies[2][1]      = EEPROMData.lastFrequencies[2][1];
  lastFrequencies[3][1]      = EEPROMData.lastFrequencies[3][1];
  lastFrequencies[4][1]      = EEPROMData.lastFrequencies[4][1];
  lastFrequencies[5][1]      = EEPROMData.lastFrequencies[5][1];
  lastFrequencies[6][1]      = EEPROMData.lastFrequencies[6][1];
  
  centerFreq                 = EEPROMData.lastFrequencies[currentBand][activeVFO]; // 4 bytes
}


/*****
  Purpose: To save the configuration data (working variables) to EEPROM

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMWrite()
{
  strcpy(EEPROMData.versionSettings, VERSION);        // Save version number

  EEPROMData.AGCMode                    = AGCMode;
  EEPROMData.CWFilterIndex              = CWFilterIndex;
  EEPROMData.nrOptionSelect             = nrOptionSelect;     
  EEPROMData.rfGainAllBands             = rfGainAllBands;

  EEPROMData.activeVFO                  = activeVFO;  // 2 bytes

  EEPROMData.audioVolume                = audioVolume; // 4 bytes
  EEPROMData.currentBand                = currentBand; // 4 bytes
  EEPROMData.currentBandA               = currentBandA;
  EEPROMData.currentBandB               = currentBandB;
  EEPROMData.decoderFlag                = decoderFlag;

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    EEPROMData.equalizerRec[i] = recEQ_Level[i];// 4 bytes each
    EEPROMData.equalizerXmt[i] = xmtEQ_Level[i];
  }

  EEPROMData.freqIncrement              = freqIncrement;  // 4 bytes
  EEPROMData.keyType                    = keyType;  // straight key = 0, keyer = 1
  EEPROMData.currentMicThreshold        = currentMicThreshold;// 4 bytes      // AFP 09-22-22
  EEPROMData.currentMicCompRatio        = currentMicCompRatio;
  EEPROMData.currentMicAttack           = currentMicAttack;
  EEPROMData.currentMicRelease          = currentMicRelease;
  EEPROMData.currentMicGain             = currentMicGain;

  EEPROMData.paddleDit                  = paddleDit;
  EEPROMData.paddleDah                  = paddleDah;
  EEPROMData.spectrumNoiseFloor         = spectrumNoiseFloor;    // AFP 09-26-22

  EEPROMData.tuneIndex                  = tuneIndex;
  EEPROMData.powerLevel                 = transmitPowerLevel;
  EEPROMData.currentWPM                 = currentWPM; // 4 bytes
  EEPROMData.xmtMode                    = xmtMode;                    // AFP 09-26-22

  EEPROMData.currentScale               = currentScale;
  EEPROMData.spectrum_zoom              = spectrum_zoom;
  EEPROMData.spectrum_display_scale     = spectrum_display_scale;// 4 bytes
  EEPROMData.sidetoneVolume             = sidetoneVolume;// 4 bytes
  EEPROMData.cwTransmitDelay            = cwTransmitDelay;   // 4 bytes

  EEPROMData.LPFcoeff                   = LPFcoeff;// 4 bytes
  EEPROMData.NR_PSI                     = NR_PSI;// 4 bytes
  EEPROMData.NR_alpha                   = NR_alpha;// 4 bytes
  EEPROMData.NR_beta                    = NR_beta;// 4 bytes
  EEPROMData.omegaN                     = omegaN;// 4 bytes
  EEPROMData.pll_fmax                   = pll_fmax;// 4 bytes

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    EEPROMData.CWPowerCalibrationFactor[i]          = CWPowerCalibrationFactor[i];  // 0.019;   //AFP 10-29-22
    EEPROMData.SSBPowerCalibrationFactor[i]         = SSBPowerCalibrationFactor[i]; // 0.008;   //AFP 10-29-22
    EEPROMData.powerOutCW[i]                        = powerOutCW[i];// 4 bytes //AFP 10-21-22
    EEPROMData.powerOutSSB[i]                       = powerOutSSB[i];     // 4 bytes AFP 10-21-22
    EEPROMData.IQAmpCorrectionFactor[i]             = IQAmpCorrectionFactor[i] ;
    EEPROMData.IQPhaseCorrectionFactor[i]           = IQPhaseCorrectionFactor[i] ;
    EEPROMData.IQXAmpCorrectionFactor[i]            = IQXAmpCorrectionFactor[i];
    EEPROMData.IQXPhaseCorrectionFactor[i]          = IQXPhaseCorrectionFactor[i];
  }
  //  Note:favoriteFreqs are written as they are saved.

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    EEPROMData.lastFrequencies[i][0]    = lastFrequencies[i][0];
    EEPROMData.lastFrequencies[i][1]    = lastFrequencies[i][1];
  }

  EEPROMData.lastFrequencies[currentBand][activeVFO]  = currentFreq;   // 4 bytes
  EEPROMData.lastFrequencies[currentBandA][VFO_A]     = currentFreqA;     // 4 bytes
  EEPROMData.lastFrequencies[currentBandB][VFO_B]     = currentFreqB;     // 4 bytes
  EEPROMData.freqCorrectionFactor                     = freqCorrectionFactor;
  
  EEPROM.put(EEPROM_BASE_ADDRESS, EEPROMData);
  CopyEEPROMToSD();
  syncEEPROM = 0;                                                   // SD EEPROM different that memory EEPROM
  EEPROMSyncIndicator(0);
} // end void eeProm SAVE

/*****
  Purpose: To show the current EEPROM values. Used for debugging

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMShow()
{
  int i;

  Serial.println("----- EEPROM Parameters: -----");

  Serial.print("Version              = "); Serial.println(EEPROMData.versionSettings);
  Serial.print("AGCMode              = "); Serial.println(EEPROMData.AGCMode);
  Serial.print("audioVolume          = "); Serial.println(EEPROMData.audioVolume);
  Serial.print("rfGainAllBands       = "); Serial.println(EEPROMData.rfGainAllBands);
  Serial.print("spectrumNoiseFloor   = "); Serial.println(EEPROMData.spectrumNoiseFloor);
  Serial.print("tuneIndex            = "); Serial.println(EEPROMData.tuneIndex);
  Serial.print("powerLevel           = "); Serial.println(EEPROMData.powerLevel);
  Serial.print("xmtMode              = "); Serial.println(EEPROMData.xmtMode);
  Serial.print("nrOptionSelect       = "); Serial.println(EEPROMData.nrOptionSelect);
  Serial.print("currentScale         = "); Serial.println(EEPROMData.currentScale);
  Serial.print("spectrum_zoom        = "); Serial.println(EEPROMData.spectrum_zoom);
  Serial.print("spect_display_scale  = "); Serial.println(EEPROMData.spectrum_display_scale);
  Serial.println("----- CW Parameters: -----");
  Serial.print("CWFilterIndex        = "); Serial.println(EEPROMData.CWFilterIndex);
  Serial.print("paddleDah            = "); Serial.println(EEPROMData.paddleDah);
  Serial.print("paddleDit            = "); Serial.println(EEPROMData.paddleDit);
  Serial.print("decoderFlag          = "); Serial.println(EEPROMData.decoderFlag);
  Serial.print("keyType              = "); Serial.println(EEPROMData.keyType);
  Serial.print("wordsPerMinute       = "); Serial.println(EEPROMData.currentWPM);
  Serial.print("sidetoneVolume       = "); Serial.println(EEPROMData.sidetoneVolume, 5);
  Serial.print("cwTransmitDelay      = "); Serial.println(EEPROMData.cwTransmitDelay);
  Serial.println("----- Current Frequencies & Bands: -----");
  Serial.print("activeVFO            = "); Serial.println(EEPROMData.activeVFO);
  Serial.print("freqIncrement        = "); Serial.println(EEPROMData.freqIncrement);
  Serial.print("currentBand          = "); Serial.println(EEPROMData.currentBand);
  Serial.print("currentBandA         = "); Serial.println(EEPROMData.currentBandA);
  Serial.print("currentBandB         = "); Serial.println(EEPROMData.currentBandB);
  Serial.print("currentFreqA         = "); Serial.println(EEPROMData.currentFreqA);
  Serial.print("currentFreqB         = "); Serial.println(EEPROMData.currentFreqB);
  Serial.print("freqCorrectionFactor = "); Serial.println(EEPROMData.freqCorrectionFactor);
  Serial.println("----- Equalizer Parameters -----");
  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    Serial.print("     equalizerRec[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.equalizerRec[i]);
  }
  Serial.println(" ");
  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    Serial.print("     equalizerXmt[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.equalizerXmt[i]);
  }
  Serial.println("----- Mic Compressor Parameters -----");
  Serial.print("micCompression        = "); Serial.println(EEPROMData.currentMicThreshold);
  Serial.print("currentMicCompRatio   = "); Serial.println(EEPROMData.currentMicCompRatio);
  Serial.print("currentMicAttack      = "); Serial.println(EEPROMData.currentMicAttack);
  Serial.print("currentMicRelease     = "); Serial.println(EEPROMData.currentMicRelease);
  Serial.print("currentMicGain        = "); Serial.println(EEPROMData.currentMicGain);
  Serial.println("----- Switch Matrix Values -----");
  for (i = 0; i < NUMBER_OF_SWITCHES; i++) {
    Serial.print("       switchValues[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.switchValues[i]);
  }
  Serial.println("----- Filter Parameters -----");
  Serial.print("LPF coeff            = "); Serial.println(EEPROMData.LPFcoeff);
  Serial.print("NR_PSI               = "); Serial.println(EEPROMData.NR_PSI);
  Serial.print("NR_alpha             = "); Serial.println(EEPROMData.NR_alpha);
  Serial.print("NR_beta              = "); Serial.println(EEPROMData.NR_beta);
  Serial.print("NR_omega             = "); Serial.println(EEPROMData.omegaN);
  Serial.print("pll_fmax             = "); Serial.println(EEPROMData.pll_fmax);
  Serial.println("----- Power Out Calibration Parameters -----");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("         powerOutCW["); Serial.print(i); Serial.print("] = "); Serial.println(EEPROMData.powerOutCW[i], 5); //AFP 10-13-22
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("        powerOutSSB["); Serial.print(i); Serial.print("] = "); Serial.println(EEPROMData.powerOutSSB[i], 5);
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("    CWPowerCalFactor["); Serial.print(i); Serial.print("] = "); Serial.println(EEPROMData.CWPowerCalibrationFactor[i], 5);
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("    SSBPowerCalFactor["); Serial.print(i); Serial.print("] = "); Serial.println(EEPROMData.SSBPowerCalibrationFactor[i], 5);
  }
  Serial.println(" ");
  Serial.println("----- I/Q Calibration Parameters -----");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("IQAmplitudeCorrectionFactor["); Serial.print(i); Serial.print("] = ");
    Serial.println(EEPROMData.IQAmpCorrectionFactor[i], 3);
  }
  Serial.println(" ");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("   IQPhaseCorrectionFactor["); Serial.print(i); Serial.print("] = ");
    Serial.println(EEPROMData.IQPhaseCorrectionFactor[i], 3);
  }
  Serial.println(" ");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print(" IQXAmplitudeCorrectionFactor["); Serial.print(i); Serial.print("] = ");
    Serial.println(EEPROMData.IQXAmpCorrectionFactor[i], 3);
  }
  Serial.println(" ");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("  IQXPhaseCorrectionFactor["); Serial.print(i); Serial.print("]= ");
    Serial.println(EEPROMData.IQXPhaseCorrectionFactor[i], 3);
  }
  Serial.println(" ");
  Serial.println("----- Favorite Frequencies -----");
  for (i = 0; i < MAX_FAVORITES; i++) {
    Serial.print("            favoriteFreqs[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(EEPROMData.favoriteFreqs[i]);
  }
  Serial.println("----- Last Frequencies -----");
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("        lastFrequencies[");
    Serial.print(i);
    Serial.print("][0] = ");
    Serial.println(EEPROMData.lastFrequencies[i][0]);
  }
  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    Serial.print("        lastFrequencies[");
    Serial.print(i);
    Serial.print("][1] = ");
    Serial.println(EEPROMData.lastFrequencies[i][1]);
  }
  Serial.println(" ");
  Serial.print("centerFreq             = "); Serial.println( (long)EEPROMData.centerFreq);

  Serial.println("----- End EEPROM Parameters -----");
}


/*****
  Purpose: To save the default setting for EEPROM variables

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMSaveDefaults()
{
  strncpy(EEPROMData.versionSettings, VERSION, sizeof(EEPROMData.versionSettings)); // Update version
  
  EEPROMData.AGCMode                    = 1;      // 1 byte
  EEPROMData.audioVolume                = 30;     // 4 bytes
  EEPROMData.rfGainAllBands             = 1;
  EEPROMData.spectrumNoiseFloor         = SPECTRUM_NOISE_FLOOR;    // AFP 09-26-22
  EEPROMData.tuneIndex                  = 5;
  EEPROMData.powerLevel                 = 10;
  EEPROMData.xmtMode                    = SSB_MODE;                    // AFP 09-26-22
  EEPROMData.nrOptionSelect             = 0;     // 1 byte
  EEPROMData.currentScale               = 1;
  EEPROMData.spectrum_zoom              = SPECTRUM_ZOOM_2;
  EEPROMData.spectrum_display_scale     = 20.0;// 4 bytes
  //----- CW Parameters: -----
  EEPROMData.CWFilterIndex              = 5;     // Off
  EEPROMData.paddleDit                  = KEYER_DIT_INPUT_TIP;
  EEPROMData.paddleDah                  = KEYER_DAH_INPUT_RING;
  EEPROMData.decoderFlag                = 0;  // Off
  EEPROMData.keyType                    = 0;  // straight key = 0, keyer = 1
  EEPROMData.currentWPM                 = 15; // 4 bytes
  EEPROMData.sidetoneVolume             = 0.001;// 4 bytes AFP 10-19-22
  EEPROMData.cwTransmitDelay            = 750;   // ms for xmt relay to cycle
  //----- Current Frequencies & Bands: -----
  EEPROMData.activeVFO                  = VFO_A;  // 2 bytes
  EEPROMData.freqIncrement              = 5;  // 4 bytes
  EEPROMData.currentBand                = 1;  // 4 bytes
  EEPROMData.currentBandA               = 1;
  EEPROMData.currentBandB               = 1;
  EEPROMData.currentFreqA               = 7200000;
  EEPROMData.currentFreqB               = 7030000;
  EEPROMData.freqCorrectionFactor       = 68000;
  //----- Equalizer Parameters -----
  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    EEPROMData.equalizerRec[i] = 100;// 4 bytes each
    EEPROMData.equalizerXmt[i] = 100;
  }
  //----- Mic Compressor Parameters -----
  EEPROMData.currentMicThreshold        = -10;// 4 bytes      // AFP 09-22-22
  EEPROMData.currentMicCompRatio        = 5.0;//
  EEPROMData.currentMicAttack           = 0.1;//
  EEPROMData.currentMicRelease          = 2.0;//
  EEPROMData.currentMicGain             = -10;
  //----- Switch Matrix Values -----
  EEPROMData.switchValues[0]                 = 924;      // Your values will likely be different
  EEPROMData.switchValues[1]                 = 870;
  EEPROMData.switchValues[2]                 = 817;
  EEPROMData.switchValues[3]                 = 769;
  EEPROMData.switchValues[4]                 = 713;
  EEPROMData.switchValues[5]                 = 669;
  EEPROMData.switchValues[6]                 = 616;
  EEPROMData.switchValues[7]                 = 565;
  EEPROMData.switchValues[8]                 = 513;
  EEPROMData.switchValues[9]                 = 459;
  EEPROMData.switchValues[10]                = 407;
  EEPROMData.switchValues[11]                = 356;
  EEPROMData.switchValues[12]                = 298;
  EEPROMData.switchValues[13]                = 242;
  EEPROMData.switchValues[14]                = 183;
  EEPROMData.switchValues[15]                = 131;
  EEPROMData.switchValues[16]                = 67;
  EEPROMData.switchValues[17]                = 10;
  //----- Filter Parameters -----
  EEPROMData.LPFcoeff                        = 0.0;// 4 bytes
  EEPROMData.NR_PSI                          = 0.0;// 4 bytes
  EEPROMData.NR_alpha                        = 0.0;// 4 bytes
  EEPROMData.NR_beta                         = 0.0;// 4 bytes
  EEPROMData.omegaN                          = 0.0;// 4 bytes
  EEPROMData.pll_fmax                        = 4000.0;// 4 bytes
  //----- Power Out Calibration Parameters -----
  EEPROMData.powerOutCW[0]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[1]                 = 0.21;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[2]                 = 0.34;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[3]                 = 0.44;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[4]                 = 0.31;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[5]                 = 0.31;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[6]                 = 0.31;// 4 bytes  AFP 10-21-22

  EEPROMData.powerOutSSB[0]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[1]                 = 0.11;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[2]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[3]                 = 0.21;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[4]                 = 0.23;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[5]                 = 0.23;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[6]                 = 0.24;// 4 bytes  AFP 10-21-22
  EEPROMData.CWPowerCalibrationFactor[0]    = 0.023;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[1]    = 0.023;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[2]    = 0.038;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[3]    = 0.052;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[4]    = 0.051;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[5]    = 0.028;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[6]    = 0.028;   //AFP 10-29-22

  EEPROMData.SSBPowerCalibrationFactor[0]   = 0.017;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[1]   = 0.019;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[2]   = 0.017;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[3]   = 0.019;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[4]   = 0.021;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[5]   = 0.020;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[6]   = 0.022;   //AFP 10-29-22

  //----- I/Q Calibration Parameters -----
  EEPROMData.IQAmpCorrectionFactor[0]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[1]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[2]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[3]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[4]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[5]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[6]            = 1.0;

  EEPROMData.IQPhaseCorrectionFactor[0]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[1]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[2]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[3]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[4]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[5]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[6]          = 0.0;

  EEPROMData.IQXAmpCorrectionFactor[0]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[1]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[2]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[3]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[4]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[5]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[6]           = 1.0;

  EEPROMData.IQXPhaseCorrectionFactor[0]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[1]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[2]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[3]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[4]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[5]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[6]        = 0.0;
  //----- Favorite Frequencies -----
  EEPROMData.favoriteFreqs[0]                =  3560000;             // These are CW/SSB calling frequencies for HF bands
  EEPROMData.favoriteFreqs[1]                =  3690000;
  EEPROMData.favoriteFreqs[2]                =  7030000;
  EEPROMData.favoriteFreqs[3]                =  7200000;
  EEPROMData.favoriteFreqs[4]                = 14060000;
  EEPROMData.favoriteFreqs[5]                = 14200000;
  EEPROMData.favoriteFreqs[6]                = 21060000;
  EEPROMData.favoriteFreqs[7]                = 21285000;
  EEPROMData.favoriteFreqs[8]                = 28060000;
  EEPROMData.favoriteFreqs[9]                = 28365000;
  EEPROMData.favoriteFreqs[10]               =  5000000;
  EEPROMData.favoriteFreqs[11]               = 10000000;
  EEPROMData.favoriteFreqs[12]               = 15000000;
  //----- Last Frequencies -----
  // The following are QRP calling frequencies
  EEPROMData.lastFrequencies[0][0] =  3985000;  // 80 Phone
  EEPROMData.lastFrequencies[1][0] =  7200000;  // 40
  EEPROMData.lastFrequencies[2][0] = 14285000;  // 50
  EEPROMData.lastFrequencies[3][0] = 18130000;  // 17
  EEPROMData.lastFrequencies[4][0] = 21385000;  // 15
  EEPROMData.lastFrequencies[5][0] = 24950000;  // 12
  EEPROMData.lastFrequencies[6][0] = 28385800;  // 10

  EEPROMData.lastFrequencies[0][1] =  3560000;  // 80 CW
  EEPROMData.lastFrequencies[1][1] =  7030000;  // 40
  EEPROMData.lastFrequencies[2][1] = 14060000;  // 20
  EEPROMData.lastFrequencies[3][1] = 18096000;  // 17
  EEPROMData.lastFrequencies[4][1] = 21060000;  // 15
  EEPROMData.lastFrequencies[5][1] = 24906000;  // 12
  EEPROMData.lastFrequencies[6][1] = 28060000;  // 10

  EEPROMData.centerFreq            = EEPROMData.lastFrequencies[currentBand][activeVFO];   // 4 bytes

  EEPROM.put(0, EEPROMData);
  if (sdCardPresent == 1) {                         // No SD card
    syncEEPROM = 0;                                 // SD EEPROM may be different that memory EEPROM
    EEPROMSyncIndicator(0);
  }
}


/*****
  Purpose: Read default favorite frequencies

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMStuffFavorites(unsigned long current[])
{
  int i;

  for (i = 0; i < MAX_FAVORITES; i++) {
    current[i] = EEPROMData.favoriteFreqs[i];
  }
}

/*****
  Purpose: Used to save a favortie frequency to EEPROM

  Parameter list:

  Return value;
    void

  CAUTION: This code assumes you have set the curently active VFO frequency to the new
           frequency you wish to save. You them use the menu encoder to scroll through
           the current list of stored frequencies. Stop on the one that you wish to
           replace and press Select to save in EEPROM. The currently active VFO frequency
           is then stored to EEPROM.
*****/
void SetFavoriteFrequency()
{
  int index;
  int val;

  tft.setFontScale( (enum RA8875tsize) 1);

  index = 0;
  tft.setTextColor(RA8875_WHITE);
  tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
  tft.print(EEPROMData.favoriteFreqs[index]);
  while (true) {
    if (filterEncoderMove != 0) {                 // Changed encoder?
      index += filterEncoderMove;                 // Yep
      if (index < 0) {
        index = MAX_FAVORITES - 1;                // Wrap to last one
      } else {
        if (index > MAX_FAVORITES)
          index = 0;                                // Wrap to first one
      }
      tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
      tft.print(EEPROMData.favoriteFreqs[index]);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                               // Read pin that controls all switches
    val = ProcessButtonPress(val);
    MyDelay(150L);
    if (val == MENU_OPTION_SELECT) {                              // Make a choice??
      EraseMenus();
      EEPROMData.favoriteFreqs[index] = TxRxFreq;
      syncEEPROM = 0;                                                   // SD EEPROM different that memory EEPROM
      EEPROMSyncIndicator(0);
      if (activeVFO == VFO_A) {
        currentFreqA = TxRxFreq;
      } else {
        currentFreqB = TxRxFreq;
      }
//      EEPROMWrite();
      SetFreq();
      BandInformation();
      ShowBandwidth();
      FilterBandwidth();
      ShowFrequency();
      break;
    }
  }
}

/*****
  Purpose: Used to fetch a favortie frequency as stored in EEPROM. It then copies that
           frequency to the currently active VFO

  Parameter list:

  Return value;
    void
*****/
void GetFavoriteFrequency()
{
  int index = 0;
  int val;
  int currentBand2 = 0;
  tft.setFontScale( (enum RA8875tsize) 1);

  tft.setTextColor(RA8875_WHITE);
  tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
  tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
  tft.print(EEPROMData.favoriteFreqs[index]);
  while (true) {
    if (filterEncoderMove != 0) {                 // Changed encoder?
      index += filterEncoderMove;                 // Yep
      if (index < 0) {
        index = MAX_FAVORITES - 1;                // Wrap to last one
      } else {
        if (index > MAX_FAVORITES)
          index = 0;                                // Wrap to first one
      }
      tft.fillRect(SECONDARY_MENU_X, MENUS_Y, EACH_MENU_WIDTH, CHAR_HEIGHT, RA8875_MAGENTA);
      tft.setCursor(SECONDARY_MENU_X, MENUS_Y);
      tft.print(EEPROMData.favoriteFreqs[index]);
      filterEncoderMove = 0;
    }

    val = ReadSelectedPushButton();                               // Read pin that controls all switches
    val = ProcessButtonPress(val);
    MyDelay(150L);

    centerFreq = EEPROMData.favoriteFreqs[index];    // current frequency  AFP 09-27-22
    if (centerFreq >= bands[BAND_80M].fBandLow && centerFreq <= bands[BAND_80M].fBandHigh) {
      currentBand2 = BAND_80M;
    } else if (centerFreq >= bands[BAND_80M].fBandHigh && centerFreq <= 7000000L) { // covers 5MHz WWV AFP 11-03-22
      currentBand2 = BAND_80M;
    } else if (centerFreq >= bands[BAND_40M].fBandLow && centerFreq <= bands[BAND_40M].fBandHigh) {
      currentBand2 = BAND_40M;
    } else if (centerFreq >= bands[BAND_40M].fBandHigh && centerFreq <= 14000000L) {   // covers 10MHz WWV AFP 11-03-22
      currentBand2 = BAND_40M;
    } else if (centerFreq >= bands[BAND_20M].fBandLow && centerFreq <= bands[BAND_20M].fBandHigh) {
      currentBand2 = BAND_20M;
    } else if (centerFreq >= 14000000L && centerFreq <= 18000000L) {      // covers 15MHz WWV AFP 11-03-22
      currentBand2 = BAND_20M;
    } else if (centerFreq >= bands[BAND_17M].fBandLow && centerFreq <= bands[BAND_17M].fBandHigh) {
      currentBand2 = BAND_17M;
    } else if (centerFreq >= bands[BAND_15M].fBandLow && centerFreq <= bands[BAND_15M].fBandHigh) {
      currentBand2 = BAND_15M;
    } else if (centerFreq >= bands[BAND_12M].fBandLow && centerFreq <= bands[BAND_12M].fBandHigh) {
      currentBand2 = BAND_12M;
    } else if (centerFreq >= bands[BAND_10M].fBandLow && centerFreq <= bands[BAND_10M].fBandHigh) {
      currentBand2 = BAND_10M;
    }
    currentBand = currentBand2;


    if (val == MENU_OPTION_SELECT) {                              // Make a choice??
      switch (activeVFO) {
        case VFO_A:
          if (currentBandA == NUMBER_OF_BANDS) {                         // Incremented too far?
            currentBandA = 0;                                            // Yep. Roll to list front.
          }
          currentBandA = currentBand2;
          TxRxFreq = centerFreq  + NCOFreq;
          lastFrequencies[currentBand][VFO_A] = TxRxFreq;
          break;

        case VFO_B:
          if (currentBandB == NUMBER_OF_BANDS) {                         // Incremented too far?
            currentBandB = 0;                                            // Yep. Roll to list front.
          }        // Same for VFO B
          currentBandB = currentBand2 ;
          TxRxFreq = centerFreq  + NCOFreq;
          lastFrequencies[currentBand][VFO_B] = TxRxFreq;
          break;
      }
    }
    if (val == MENU_OPTION_SELECT) {

      EraseSpectrumDisplayContainer();
      currentMode = bands[currentBand].mode;
      DrawSpectrumDisplayContainer();
      DrawFrequencyBarValue();
      SetBand();
      SetFreq();
      ShowFrequency();
      ShowSpectrumdBScale();
      EraseMenus();
      ResetTuning();
      FilterBandwidth();
      BandInformation();
      NCOFreq = 0L;
      DrawBandWidthIndicatorBar(); // AFP 10-20-22
      digitalWrite(bandswitchPins[currentBand], LOW);
      SetFreq();
      ShowSpectrumdBScale();
      ShowSpectrum();
      //bands[currentBand].mode = currentBand;
      return;
    }
  }
}

//===================================================================
/*****
  Purpose: Copy EEPROM data into working variables

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void CopyEEPROM()
{
  //  EEPROM.get(EEPROM_BASE_ADDRESS, EEPROMData);                       // Read as one large chunk

  AGCMode                               = EEPROMData.AGCMode;        // 1 byte
  CWFilterIndex                         = EEPROMData.CWFilterIndex;  // Off
  nrOptionSelect                        = EEPROMData.nrOptionSelect; // 1 byte

  activeVFO                             = EEPROMData.activeVFO;  // 2 bytes

  audioVolume                           = EEPROMData.audioVolume; // 4 bytes
  currentBand                           = EEPROMData.currentBand; // 4 bytes
  currentBandA                          = EEPROMData.currentBandA;// 4 bytes
  currentBandB                          = EEPROMData.currentBandB;// 4 bytes
  decoderFlag                           = EEPROMData.decoderFlag;

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    recEQ_Level[i] =  EEPROMData.equalizerRec[i];// 4 bytes each
    xmtEQ_Level[i] =  EEPROMData.equalizerXmt[i];
  }

  freqIncrement                         = EEPROMData.freqIncrement;  // 4 bytes
  keyType                               = EEPROMData.keyType;  // straight key = 0, keyer = 1
  currentMicThreshold                   = EEPROMData.currentMicThreshold;// 4 bytes      // AFP 09-22-22
  currentMicCompRatio                   = EEPROMData.currentMicCompRatio;
  currentMicAttack                      = EEPROMData.currentMicAttack;
  currentMicRelease                     = EEPROMData.currentMicRelease;
  currentMicGain                        = EEPROMData.currentMicGain;

  paddleDit                             = EEPROMData.paddleDit;
  paddleDah                             = EEPROMData.paddleDah;
  rfGainAllBands                        = EEPROMData.rfGainAllBands;
  spectrumNoiseFloor                    = EEPROMData.spectrumNoiseFloor;    // AFP 09-26-22

  //  Note: switch values are read and written to EEPROM only

  tuneIndex                             = EEPROMData.tuneIndex;
  transmitPowerLevel                    = EEPROMData.powerLevel;
  currentWPM                            = EEPROMData.currentWPM; // 4 bytes
  xmtMode                               = EEPROMData.xmtMode;                    // AFP 09-26-22

  currentScale                          = EEPROMData.currentScale;
  spectrum_zoom                         = EEPROMData.spectrum_zoom;
  spectrum_display_scale                = EEPROMData.spectrum_display_scale;// 4 bytes
  sidetoneVolume                        = EEPROMData.sidetoneVolume;// 4 bytes
  cwTransmitDelay                       = EEPROMData.cwTransmitDelay;   // 4 bytes

  freqCorrectionFactor                  = EEPROMData.freqCorrectionFactor;

  LPFcoeff                              = EEPROMData.LPFcoeff;// 4 bytes
  NR_PSI                                = EEPROMData.NR_PSI;// 4 bytes
  NR_alpha                              = EEPROMData.NR_alpha;// 4 bytes
  NR_beta                               = EEPROMData.NR_beta;// 4 bytes
  omegaN                                = EEPROMData.omegaN;// 4 bytes
  pll_fmax                              = EEPROMData.pll_fmax;// 4 bytes

  for (int i = 0; i < NUMBER_OF_BANDS; i++) {
    CWPowerCalibrationFactor[i]           = EEPROMData.CWPowerCalibrationFactor[i];  // 0.019;   //AFP 10-29-22
    SSBPowerCalibrationFactor[i]          = EEPROMData.SSBPowerCalibrationFactor[i]; // 0.008;   //AFP 10-29-22
    powerOutCW[i]                         = EEPROMData.powerOutCW[i];// 4 bytes  //AFP 10-28-22
    powerOutSSB[i]                        = EEPROMData.powerOutSSB[i];     // 4 bytes AFP 10-28-22
    IQAmpCorrectionFactor[i]              = EEPROMData.IQAmpCorrectionFactor[i];
    IQPhaseCorrectionFactor[i]            = EEPROMData.IQPhaseCorrectionFactor[i];
    IQXAmpCorrectionFactor[i]             = EEPROMData.IQXAmpCorrectionFactor[i]; //AFP 2-21-23
    IQXPhaseCorrectionFactor[i]           = EEPROMData.IQXPhaseCorrectionFactor[i]; //AFP 2-21-23
  }

  if (EEPROMData.lastFrequencies[0][1] < 3560000L || EEPROMData.lastFrequencies[0][0] > 3985000L) {  // Already set?
    EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 Phone
    EEPROMData.lastFrequencies[1][0] =  7200000L;  // 40
    EEPROMData.lastFrequencies[2][0] = 14285000L;  // 50
    EEPROMData.lastFrequencies[3][0] = 18130000L;  // 17
    EEPROMData.lastFrequencies[4][0] = 21385000L;  // 15
    EEPROMData.lastFrequencies[5][0] = 24950000L;  // 12
    EEPROMData.lastFrequencies[6][0] = 28385800L;  // 10

    EEPROMData.lastFrequencies[0][1] =  3560000L;  // 80 CW
    EEPROMData.lastFrequencies[1][1] =  7030000L;  // 40
    EEPROMData.lastFrequencies[2][1] = 14060000L;  // 20
    EEPROMData.lastFrequencies[3][1] = 18096000L;  // 17
    EEPROMData.lastFrequencies[4][1] = 21060000L;  // 15
    EEPROMData.lastFrequencies[5][1] = 24906000L;  // 12
    EEPROMData.lastFrequencies[6][1] = 28060000L;  // 10
  } else {
    for (int i = 0; i < NUMBER_OF_BANDS; i++) {
      lastFrequencies[i][0] = EEPROMData.lastFrequencies[i][0];
      lastFrequencies[i][1] = EEPROMData.lastFrequencies[i][1];
    }
  }

  //  long favoriteFreqs[MAX_FAVORITES];               // 40 bytes
  centerFreq                            = EEPROMData.lastFrequencies[currentBandA][activeVFO]; // 4 bytes
  currentFreqA                          = EEPROMData.lastFrequencies[currentBandA][VFO_A];     // 4 bytes
  currentFreqB                          = EEPROMData.lastFrequencies[currentBandB][VFO_B];     // 4 bytes
}

/*****
  Purpose: To save the default setting for EEPROM variables

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    void
*****/
void EEPROMSaveDefaults2()
{
  strncpy(EEPROMData.versionSettings, VERSION, sizeof(EEPROMData.versionSettings)); // Update version

  EEPROMData.AGCMode             = 1;
  EEPROMData.audioVolume         = 30;   // 4 bytes
  EEPROMData.rfGainAllBands      = 1;
  EEPROMData.spectrumNoiseFloor  = SPECTRUM_NOISE_FLOOR;
  EEPROMData.tuneIndex           = 5;
  EEPROMData.powerLevel          = 10;
  EEPROMData.xmtMode             = 0;
  EEPROMData.nrOptionSelect      = 0;     // 1 byte
  EEPROMData.currentScale        = 1;
  EEPROMData.spectrum_zoom       = 1;
  EEPROMData.spectrum_display_scale = 20.0;// 4 bytes

  EEPROMData.CWFilterIndex       = 5;  // Off
  EEPROMData.paddleDit           = 36;
  EEPROMData.paddleDah           = 35;
  EEPROMData.decoderFlag         = 0;
  EEPROMData.keyType             = 0;  // straight key = 0, keyer = 1
  EEPROMData.currentWPM          = 15; // 4 bytes
  EEPROMData.sidetoneVolume      = .001;// 4 bytes
  EEPROMData.cwTransmitDelay     = 750;   // 4 bytes

  EEPROMData.activeVFO           = 0;  // 2 bytes, 0 = VFOa
  EEPROMData.freqIncrement       = 5;  // 4 bytes
  EEPROMData.currentBand         = 1; // 4 bytes
  EEPROMData.currentBandA        = 1;// 4 bytes
  EEPROMData.currentBandB        = 1;// 4 bytes
  EEPROMData.currentFreqA        = 7200000;
  EEPROMData.currentFreqB        = 7030000;
  EEPROMData.freqCorrectionFactor = 68000;

  for (int i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    EEPROMData.equalizerRec[i] = 100;// 4 bytes each
    EEPROMData.equalizerXmt[i] = 100;
  }

  EEPROMData.currentMicThreshold = -10;// 4 bytes      // AFP 09-22-22
  EEPROMData.currentMicCompRatio = 5.0;
  EEPROMData.currentMicAttack    = 0.1;
  EEPROMData.currentMicRelease   = 2.0;
  EEPROMData.currentMicGain     = -10;

  EEPROMData.switchValues[0]       = 924;
  EEPROMData.switchValues[1]       = 870;
  EEPROMData.switchValues[2]       = 817;
  EEPROMData.switchValues[3]       = 769;
  EEPROMData.switchValues[4]       = 713;
  EEPROMData.switchValues[5]       = 669;
  EEPROMData.switchValues[6]       = 616;
  EEPROMData.switchValues[7]       = 565;
  EEPROMData.switchValues[8]       = 513;
  EEPROMData.switchValues[9]       = 459;
  EEPROMData.switchValues[10]      = 407;
  EEPROMData.switchValues[11]      = 356;
  EEPROMData.switchValues[12]      = 298;
  EEPROMData.switchValues[13]      = 242;
  EEPROMData.switchValues[14]      = 183;
  EEPROMData.switchValues[15]      = 131;
  EEPROMData.switchValues[16]      = 67;
  EEPROMData.switchValues[17]      = 10;

  EEPROMData.LPFcoeff                   = 0.0;// 4 bytes
  EEPROMData.NR_PSI                     = 0.0;// 4 bytes
  EEPROMData.NR_alpha                   = 0.0;// 4 bytes
  EEPROMData.NR_beta                    = 0.0;// 4 bytes
  EEPROMData.omegaN                     = 0.0;// 4 bytes
  EEPROMData.pll_fmax                   = 4000.0;// 4 bytes

  EEPROMData.powerOutCW[0]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[1]                 = 0.21;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[2]                 = 0.34;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[3]                 = 0.44;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[4]                 = 0.31;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[5]                 = 0.31;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutCW[6]                 = 0.31;// 4 bytes  AFP 10-21-22

  EEPROMData.powerOutSSB[0]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[1]                 = 0.11;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[2]                 = 0.188;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[3]                 = 0.21;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[4]                 = 0.23;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[5]                 = 0.23;// 4 bytes  AFP 10-21-22
  EEPROMData.powerOutSSB[6]                 = 0.24;// 4 bytes  AFP 10-21-22

  EEPROMData.CWPowerCalibrationFactor[0]   = 0.023;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[1]   = 0.023;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[2]   = 0.038;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[3]   = 0.052;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[4]   = 0.051;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[5]   = 0.028;   //AFP 10-29-22
  EEPROMData.CWPowerCalibrationFactor[6]   = 0.028;   //AFP 10-29-22

  EEPROMData.SSBPowerCalibrationFactor[0]  = 0.017;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[1]  = 0.019;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[2]  = 0.017;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[3]  = 0.019;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[4]  = 0.021;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[5]  = 0.020;   //AFP 10-29-22
  EEPROMData.SSBPowerCalibrationFactor[6]  = 0.022;   //AFP 10-29-22

  EEPROMData.IQAmpCorrectionFactor[0]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[1]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[2]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[3]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[4]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[5]            = 1.0;
  EEPROMData.IQAmpCorrectionFactor[6]            = 1.0;

  EEPROMData.IQPhaseCorrectionFactor[0]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[1]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[2]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[3]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[4]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[5]          = 0.0;
  EEPROMData.IQPhaseCorrectionFactor[6]          = 0.0;

  EEPROMData.IQXAmpCorrectionFactor[0]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[1]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[2]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[3]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[4]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[5]           = 1.0;
  EEPROMData.IQXAmpCorrectionFactor[6]           = 1.0;

  EEPROMData.IQXPhaseCorrectionFactor[0]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[1]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[2]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[3]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[4]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[5]        = 0.0;
  EEPROMData.IQXPhaseCorrectionFactor[6]        = 0.0;

  EEPROMData.favoriteFreqs[0]                =  3560000L;             // These are CW/SSB calling frequencies for HF bands
  EEPROMData.favoriteFreqs[1]                =  3690000L;
  EEPROMData.favoriteFreqs[2]                =  7030000L;
  EEPROMData.favoriteFreqs[3]                =  7200000L;
  EEPROMData.favoriteFreqs[4]                = 14060000L;
  EEPROMData.favoriteFreqs[5]                = 14200000L;
  EEPROMData.favoriteFreqs[6]                = 21060000L;
  EEPROMData.favoriteFreqs[7]                = 21285000L;
  EEPROMData.favoriteFreqs[8]                = 28060000L;
  EEPROMData.favoriteFreqs[9]                = 28365000L;
  EEPROMData.favoriteFreqs[10]               =  5000000L;
  EEPROMData.favoriteFreqs[11]               = 10000000L;
  EEPROMData.favoriteFreqs[12]               = 15000000L;

  // The following are QRP calling frequencies
  EEPROMData.lastFrequencies[0][0] =  3985000L;  // 80 Phone
  EEPROMData.lastFrequencies[1][0] =  7200000L;  // 40
  EEPROMData.lastFrequencies[2][0] = 14285000L;  // 50
  EEPROMData.lastFrequencies[3][0] = 18130000L;  // 17
  EEPROMData.lastFrequencies[4][0] = 21385000L;  // 15
  EEPROMData.lastFrequencies[5][0] = 24950000L;  // 12
  EEPROMData.lastFrequencies[6][0] = 28385800L;  // 10

  EEPROMData.lastFrequencies[0][1] =  3560000L;  // 80 CW
  EEPROMData.lastFrequencies[1][1] =  7030000L;  // 40
  EEPROMData.lastFrequencies[2][1] = 14060000L;  // 20
  EEPROMData.lastFrequencies[3][1] = 18096000L;  // 17
  EEPROMData.lastFrequencies[4][1] = 21060000L;  // 15
  EEPROMData.lastFrequencies[5][1] = 24906000L;  // 12
  EEPROMData.lastFrequencies[6][1] = 28060000L;  // 10

  EEPROMData.centerFreq = 7150000;

  if (sdCardPresent == 1) {                         // SD card
    syncEEPROM = 0;                                 // SD EEPROM may be different that memory EEPROM
    EEPROMSyncIndicator(0);
  }
}

/*****
  Purpose: Read the EEPROM data from the SD card and assign it to the
           proper EEPROM members.

  Parameter list:
    struct config_t e[]       pointer to the EEPROM structure

  Return value;
    int                         0 unsuccessful, 1 ok
*****/
int CopySDToEEPROM()
{
  char character;
  char line[150];
  char *target;
  char temp[50];
  int index = 0;
  int lineCount = 0;

  if (!SD.begin(chipSelect)) {        // SD failed
    // don't do anything more:
    return 0;                         // Go home and report it
  }

  File file = SD.open("SDEEPROMData.txt", FILE_READ); // Try to open file...
  if (file == 0) {
    return 0;                         // Could not get a file handle, so go home and report it
  }

  while (file.available() > 0) {
    character = file.read();
    line[index++] = character;
    if ((character == '\n')) {        // Have we read the complete line?
      line[index - 2] = '\0';         // Overwrite newline and semicolon, we have the complete line as string
      target = strstr(line, " = ");   // Look for token
      strcpy(temp, target + 3);       // Skip past the token
      index = 0;
      switch (lineCount++) {                      // This is a hack, but it works
        case 0:     // Version
          strcpy(EEPROMData.versionSettings, temp); // Real assignment from header file
          break;
        case 1:
          EEPROMData.AGCMode =  atoi(temp);
          break;
        case 2:
          EEPROMData.audioVolume = atoi(temp);
          break;
        case 3:
          EEPROMData.rfGainAllBands = atoi(temp);
          break;
        case 4:
          EEPROMData.spectrumNoiseFloor = atoi(temp);
          break;
        case 5:
          EEPROMData.tuneIndex = atoi(temp);
          break;
        case 6:
          EEPROMData.powerLevel = atoi(temp);
          break;
        case 7:
          EEPROMData.xmtMode = atoi(temp);
          break;
        case 8:
          EEPROMData.nrOptionSelect = (int8_t) atoi(temp);
          break;
        case 9:
          EEPROMData.currentScale = (uint16_t) atoi(temp);
          break;
        case 10:
          EEPROMData.spectrum_zoom = (int32_t) atol(temp);
          break;
        case 11:
          EEPROMData.spectrum_display_scale = atof(temp);
          break;
        case 12:
          EEPROMData.CWFilterIndex = atoi(temp);
          break;
        case 13:
          EEPROMData.paddleDit = atoi(temp);
          break;
        case 14:
          EEPROMData.paddleDah = atoi(temp);
          break;
        case 15:
          EEPROMData.decoderFlag = atoi(temp);
          break;
        case 16:
          EEPROMData.keyType = atoi(temp);
          break;
        case 17:
          EEPROMData.currentWPM = atoi(temp);
          break;
        case 18:
          EEPROMData.sidetoneVolume = atof(temp);
          break;
        case 19:
          EEPROMData.cwTransmitDelay = atol(temp);
          break;
        case 20:
          EEPROMData.activeVFO = (int16_t) atoi(temp);
          break;
        case 21:
          EEPROMData.freqIncrement = atoi(temp);
          break;
        case 22:
          EEPROMData.currentBand = atoi(temp);
          break;
        case 23:
          EEPROMData.currentBandA = atoi(temp);
          break;
        case 24:
          EEPROMData.currentBandB = atoi(temp);
          break;
        case 25:
          EEPROMData.currentFreqA = atol(temp);
          break;
        case 26:
          EEPROMData.currentFreqB = atol(temp);
          break;
        case 27:
          EEPROMData.freqCorrectionFactor = (long long)atol(temp);
          break;
        case 28:
          EEPROMData.equalizerRec[0] = atoi(temp);
          break;
        case 29:
          EEPROMData.equalizerRec[1] = atoi(temp);
          break;
        case 30:
          EEPROMData.equalizerRec[2] = atoi(temp);
          break;
        case 31:
          EEPROMData.equalizerRec[3] = atoi(temp);
          break;
        case 32:
          EEPROMData.equalizerRec[4] = atoi(temp);
          break;
        case 33:
          EEPROMData.equalizerRec[5] = atoi(temp);
          break;
        case 34:
          EEPROMData.equalizerRec[6] = atoi(temp);
          break;
        case 35:
          EEPROMData.equalizerRec[7] = atoi(temp);
          break;
        case 36:
          EEPROMData.equalizerRec[8] = atoi(temp);
          break;
        case 37:
          EEPROMData.equalizerRec[9] = atoi(temp);
          break;
        case 38:
          EEPROMData.equalizerRec[10] = atoi(temp);
          break;
        case 39:
          EEPROMData.equalizerRec[11] = atoi(temp);
          break;
        case 40:
          EEPROMData.equalizerRec[12] = atoi(temp);
          break;
        case 41:
          EEPROMData.equalizerRec[13] = atoi(temp);
          break;
        case 42:
          EEPROMData.equalizerXmt[0] = atoi(temp);
          break;
        case 43:
          EEPROMData.equalizerXmt[1] = atoi(temp);
          break;
        case 44:
          EEPROMData.equalizerXmt[2] = atoi(temp);
          break;
        case 45:
          EEPROMData.equalizerXmt[3] = atoi(temp);
          break;
        case 46:
          EEPROMData.equalizerXmt[4] = atoi(temp);
          break;
        case 47:
          EEPROMData.equalizerXmt[5] = atoi(temp);
          break;
        case 48:
          EEPROMData.equalizerXmt[6] = atoi(temp);
          break;
        case 49:
          EEPROMData.equalizerXmt[7] = atoi(temp);
          break;
        case 50:
          EEPROMData.equalizerXmt[8] = atoi(temp);
          break;
        case 51:
          EEPROMData.equalizerXmt[9] = atoi(temp);
          break;
        case 52:
          EEPROMData.equalizerXmt[10] = atoi(temp);
          break;
        case 53:
          EEPROMData.equalizerXmt[11] = atoi(temp);
          break;
        case 54:
          EEPROMData.equalizerXmt[12] = atoi(temp);
          break;
        case 55:
          EEPROMData.equalizerXmt[13] = atoi(temp);
          break;
        case 56:
          EEPROMData.currentMicThreshold = atoi(temp);
          break;
        case 57:
          EEPROMData.currentMicCompRatio = atof(temp);
          break;
        case 58:
          EEPROMData.currentMicAttack = atof(temp);
        case 59:
          EEPROMData.currentMicRelease = atof(temp);
          break;
        case 60:
          EEPROMData.currentMicGain = atoi(temp);
          break;
        case 61:
          EEPROMData.switchValues[0] = atoi(temp);
          break;
        case 62:
          EEPROMData.switchValues[1] = atoi(temp);
          break;
        case 63:
          EEPROMData.switchValues[2] = atoi(temp);
          break;
        case 64:
          EEPROMData.switchValues[3] = atoi(temp);
          break;
        case 65:
          EEPROMData.switchValues[4] = atoi(temp);
          break;
        case 66:
          EEPROMData.switchValues[5] = atoi(temp);
          break;
        case 67:
          EEPROMData.switchValues[6] = atoi(temp);
          break;
        case 68:
          EEPROMData.switchValues[7] = atoi(temp);
          break;
        case 69:
          EEPROMData.switchValues[8] = atoi(temp);
          break;
        case 70:
          EEPROMData.switchValues[9] = atoi(temp);
          break;
        case 71:
          EEPROMData.switchValues[10] = atoi(temp);
          break;
        case 72:
          EEPROMData.switchValues[11] = atoi(temp);
          break;
        case 73:
          EEPROMData.switchValues[12] = atoi(temp);
          break;
        case 74:
          EEPROMData.switchValues[13] = atoi(temp);
          break;
        case 75:
          EEPROMData.switchValues[14] = atoi(temp);
          break;
        case 76:
          EEPROMData.switchValues[15] = atoi(temp);
          break;
        case 77:
          EEPROMData.switchValues[16] = atoi(temp);
          break;
        case 78:
          EEPROMData.switchValues[17] = atoi(temp);
          break;
        case 79:
          EEPROMData.LPFcoeff = atof(temp);
          break;
        case 80:
          EEPROMData.NR_PSI = atof(temp);
          break;
        case 81:
          EEPROMData.NR_alpha = atof(temp);
          break;
        case 82:
          EEPROMData.NR_beta = atof(temp);
          break;
        case 83:
          EEPROMData.omegaN = atof(temp);
          break;
        case 84:
          EEPROMData.pll_fmax = atof(temp);
          break;
        case 85:
          EEPROMData.powerOutCW[0] = atof(temp);
          break;
        case 86:
          EEPROMData.powerOutCW[1] = atof(temp);
          break;
        case 87:
          EEPROMData.powerOutCW[2] = atof(temp);
          break;
        case 88:
          EEPROMData.powerOutCW[3] = atof(temp);
          break;
        case 89:
          EEPROMData.powerOutCW[4] = atof(temp);
          break;
        case 90:
          EEPROMData.powerOutCW[5] = atof(temp);
          break;
        case 91:
          EEPROMData.powerOutCW[6] = atof(temp);
          break;
        case 92:
          EEPROMData.powerOutSSB[0] = atof(temp);
          break;
        case 93:
          EEPROMData.powerOutSSB[1] = atof(temp);
          break;
        case 94:
          EEPROMData.powerOutSSB[2] = atof(temp);
          break;
        case 95:
          EEPROMData.powerOutSSB[3] = atof(temp);
          break;
        case 96:
          EEPROMData.powerOutSSB[4] = atof(temp);
          break;
        case 97:
          EEPROMData.powerOutSSB[5] = atof(temp);
          break;
        case 98:
          EEPROMData.powerOutSSB[6] = atof(temp);
          break;
        case 99:
          EEPROMData.CWPowerCalibrationFactor[0] = atof(temp);
          break;
        case 100:
          EEPROMData.CWPowerCalibrationFactor[1] = atof(temp);
          break;
        case 101:
          EEPROMData.CWPowerCalibrationFactor[2] = atof(temp);
          break;
        case 102:
          EEPROMData.CWPowerCalibrationFactor[3] = atof(temp);
          break;
        case 103:
          EEPROMData.CWPowerCalibrationFactor[4] = atof(temp);
          break;
        case 104:
          EEPROMData.CWPowerCalibrationFactor[5] = atof(temp);
          break;
        case 105:
          EEPROMData.CWPowerCalibrationFactor[6] = atof(temp);
          break;
        case 106:
          EEPROMData.SSBPowerCalibrationFactor[0] = atof(temp);
          break;
        case 107:
          EEPROMData.SSBPowerCalibrationFactor[1] = atof(temp);
          break;
        case 108:
          EEPROMData.SSBPowerCalibrationFactor[2] = atof(temp);
          break;
        case 109:
          EEPROMData.SSBPowerCalibrationFactor[3] = atof(temp);
          break;
        case 110:
          EEPROMData.SSBPowerCalibrationFactor[4] = atof(temp);
          break;
        case 111:
          EEPROMData.SSBPowerCalibrationFactor[5] = atof(temp);
          break;
        case 112:
          EEPROMData.SSBPowerCalibrationFactor[6] = atof(temp);
          break;
        case 113:
          EEPROMData.IQAmpCorrectionFactor[0] = atof(temp);
          break;
        case 114:
          EEPROMData.IQAmpCorrectionFactor[1] = atof(temp);
          break;
        case 115:
          EEPROMData.IQAmpCorrectionFactor[2] = atof(temp);
          break;
        case 116:
          EEPROMData.IQAmpCorrectionFactor[3] = atof(temp);
          break;
        case 117:
          EEPROMData.IQAmpCorrectionFactor[4] = atof(temp);
          break;
        case 118:
          EEPROMData.IQAmpCorrectionFactor[5] = atof(temp);
          break;
        case 119:
          EEPROMData.IQAmpCorrectionFactor[6] = atof(temp);
          break;
        case 120:
          EEPROMData.IQPhaseCorrectionFactor[0] = atof(temp);
          break;
        case 121:
          EEPROMData.IQPhaseCorrectionFactor[1] = atof(temp);
          break;
        case 122:
          EEPROMData.IQPhaseCorrectionFactor[2] = atof(temp);
          break;
        case 123:
          EEPROMData.IQPhaseCorrectionFactor[3] = atof(temp);
          break;
        case 124:
          EEPROMData.IQPhaseCorrectionFactor[4] = atof(temp);
          break;
        case 125:
          EEPROMData.IQPhaseCorrectionFactor[5] = atof(temp);
          break;
        case 126:
          EEPROMData.IQPhaseCorrectionFactor[6] = atof(temp);
          break;
        case 127:
          EEPROMData.IQXAmpCorrectionFactor[0] = atof(temp);
          break;
        case 128:
          EEPROMData.IQXAmpCorrectionFactor[1] = atof(temp);
          break;
        case 129:
          EEPROMData.IQXAmpCorrectionFactor[2] = atof(temp);
          break;
        case 130:
          EEPROMData.IQXAmpCorrectionFactor[3] = atof(temp);
          break;
        case 131:
          EEPROMData.IQXAmpCorrectionFactor[4] = atof(temp);
          break;
        case 132:
          EEPROMData.IQXAmpCorrectionFactor[5] = atof(temp);
          break;
        case 133:
          EEPROMData.IQXAmpCorrectionFactor[6] = atof(temp);
          break;
        case 134:
          EEPROMData.IQXPhaseCorrectionFactor[0] = atof(temp);
          break;
        case 135:
          EEPROMData.IQXPhaseCorrectionFactor[1] = atof(temp);
          break;
        case 136:
          EEPROMData.IQXPhaseCorrectionFactor[2] = atof(temp);
          break;
        case 137:
          EEPROMData.IQXPhaseCorrectionFactor[3] = atof(temp);
          break;
        case 138:
          EEPROMData.IQXPhaseCorrectionFactor[4] = atof(temp);
          break;
        case 139:
          EEPROMData.IQXPhaseCorrectionFactor[5] = atof(temp);
          break;
        case 140:
          EEPROMData.IQXPhaseCorrectionFactor[6] = atof(temp);
          break;
        case 141:
          EEPROMData.favoriteFreqs[0] = atol(temp);
          break;
        case 142:
          EEPROMData.favoriteFreqs[1] = atol(temp);
          break;
        case 143:
          EEPROMData.favoriteFreqs[2] = atol(temp);
          break;
        case 144:
          EEPROMData.favoriteFreqs[3] = atol(temp);
          break;
        case 145:
          EEPROMData.favoriteFreqs[4] = atol(temp);
          break;
        case 146:
          EEPROMData.favoriteFreqs[5] = atol(temp);
          break;
        case 147:
          EEPROMData.favoriteFreqs[6] = atol(temp);
          break;
        case 148:
          EEPROMData.favoriteFreqs[7] = atol(temp);
          break;
        case 149:
          EEPROMData.favoriteFreqs[8] = atol(temp);
          break;
        case 150:
          EEPROMData.favoriteFreqs[9] = atol(temp);
          break;
        case 151:
          EEPROMData.favoriteFreqs[10] = atol(temp);
          break;
        case 152:
          EEPROMData.favoriteFreqs[11] = atol(temp);
          break;
        case 153:
          EEPROMData.favoriteFreqs[12] = atol(temp);
          break;
        case 154:
          EEPROMData.lastFrequencies[0][0] = atol(temp);
          break;
        case 155:
          EEPROMData.lastFrequencies[1][0] = atol(temp);
          break;
        case 156:
          EEPROMData.lastFrequencies[2][0] = atol(temp);
          break;
        case 157:
          EEPROMData.lastFrequencies[3][0] = atol(temp);
          break;
        case 158:
          EEPROMData.lastFrequencies[4][0] = atol(temp);
          break;
        case 159:
          EEPROMData.lastFrequencies[5][0] = atol(temp);
          break;
        case 160:
          EEPROMData.lastFrequencies[6][0] = atol(temp);
          break;
        case 161:
          EEPROMData.lastFrequencies[0][1] = atol(temp);
          break;
        case 162:
          EEPROMData.lastFrequencies[1][1] = atol(temp);
          break;
        case 163:
          EEPROMData.lastFrequencies[2][1] = atol(temp);
          break;
        case 164:
          EEPROMData.lastFrequencies[3][1] = atol(temp);
          break;
        case 165:
          EEPROMData.lastFrequencies[4][1] = atol(temp);
          break;
        case 166:
          EEPROMData.lastFrequencies[5][1] = atol(temp);
          break;
        case 167:
          EEPROMData.lastFrequencies[6][1] = atol(temp);
          break;
        case 168:
          EEPROMData.centerFreq = atol(temp);
          goto DONE;
          break;
        default:
          Serial.print("Shouldn't be here: lineCount = ");
          Serial.println(lineCount);
          break;
      }
    }
  }
DONE:
  file.close();
  syncEEPROM = 1;                                                   // SD EEPROM same as memory EEPROM
  EEPROMSyncIndicator(1);
  return 1;
}

/*****
  Purpose: Provides a display indicator that the memory-based EEPROM is different than SD card EEPROM

  Parameter list:
    int inSync                    0 = no, memory and SD card not necessarily the same, 1 = same

  Return value;
    void

*****/
void EEPROMSyncIndicator(int inSync)
{
  if (inSync == 0) {                                                   // SD EEPROM different that memory EEPROM
    tft.setFontScale( (enum RA8875tsize) 0);
    tft.fillRect(BAND_INDICATOR_X + 167, BAND_INDICATOR_Y + 70, tft.getFontWidth() * 7, tft.getFontHeight(), RA8875_RED);
    tft.setCursor(BAND_INDICATOR_X + 170, BAND_INDICATOR_Y + 70);
    tft.setTextColor(RA8875_WHITE);
    tft.print("EEPROM");
  } else {                                                                  // Erase message
    tft.fillRect(BAND_INDICATOR_X + 167, BAND_INDICATOR_Y + 70, tft.getFontWidth() * 5, tft.getFontHeight(), RA8875_BLACK);
  }
}

/*****
  Purpose: Writes the current values to the SD card as SDEEPROMData.txt

  Parameter list:
    void

  Return value;
    int               0, no write  1, write
*****/
int SDEEPROMWriteDefaults()
{
  char temp[100];

  File file = SD.open("SDEEPROMData.txt", O_RDWR);   // Get a file handle
  if (!file) {                                                            // Can't open the file
    return 0;                                                             // Go home
  }
  file.seek(0L);                                        // Reset to BOF so we don't append

  strcpy(temp, "EEPROMData.versionSettings = ");        // Copy current version number
  strcat(temp, VERSION);
  file.println(temp);

  file.println("EEPROMData.AGCMode = 1");
  file.println("EEPROMData.audioVolume = 30");
  file.println("EEPROMData.rfGainAllBands = 1");
  file.println("EEPROMData.spectrumNoiseFloor = 247");
  file.println("EEPROMData.tuneIndex = 5");
  file.println("EEPROMData.powerLevel = 10");
  file.println("EEPROMData.xmtMode = 0");
  file.println("EEPROMData.nrInUse = 0");
  file.println("EEPROMData.currentScale = 1");
  file.println("EEPROMData.spectrum_zoom = 1");
  file.println("EEPROMData.spectrum_display_scale = 20.0");

  file.println("EEPROMData.CWFilterIndex = 5");
  file.println("EEPROMData.paddleDah = 35");
  file.println("EEPROMData.paddleDit = 36");
  file.println("EEPROMData.decoderFlag = 0");
  file.println("EEPROMData.keyType = 0");
  file.println("EEPROMData.currentWPM = 15");
  file.println("EEPROMData.sidetoneVolume = 0.001");
  file.println("EEPROMData.cwTransmitDelay = 750");

  file.println("EEPROMData.activeVFO = 0");
  file.println("EEPROMData.freqIncrement = 5");
  file.println("EEPROMData.currentBand = 1");
  file.println("EEPROMData.currentBandA = 1");
  file.println("EEPROMData.currentBandB = 1");
  file.println("EEPROMData.currentFreqA = 7200000");
  file.println("EEPROMData.currentFreqB = 7030000");
  file.println("EEPROMData.freqCorrectionFactor = 68000");

  file.println("EEPROMData.equalizerRec[0] = 100");
  file.println("EEPROMData.equalizerRec[1] = 100");
  file.println("EEPROMData.equalizerRec[2] = 100");
  file.println("EEPROMData.equalizerRec[3] = 100");
  file.println("EEPROMData.equalizerRec[4] = 100");
  file.println("EEPROMData.equalizerRec[5] = 100");
  file.println("EEPROMData.equalizerRec[6] = 100");
  file.println("EEPROMData.equalizerRec[7] = 100");
  file.println("EEPROMData.equalizerRec[8] = 100");
  file.println("EEPROMData.equalizerRec[9] = 100");
  file.println("EEPROMData.equalizerRec[10] = 100");
  file.println("EEPROMData.equalizerRec[11] = 100");
  file.println("EEPROMData.equalizerRec[12] = 100");
  file.println("EEPROMData.equalizerRec[13] = 100");

  file.println("EEPROMData.equalizerXmt[0] = 100");
  file.println("EEPROMData.equalizerXmt[1] = 100");
  file.println("EEPROMData.equalizerXmt[2] = 100");
  file.println("EEPROMData.equalizerXmt[3] = 100");
  file.println("EEPROMData.equalizerXmt[4] = 100");
  file.println("EEPROMData.equalizerXmt[5] = 100");
  file.println("EEPROMData.equalizerXmt[6] = 100");
  file.println("EEPROMData.equalizerXmt[7] = 100");
  file.println("EEPROMData.equalizerXmt[8] = 100");
  file.println("EEPROMData.equalizerXmt[9] = 100");
  file.println("EEPROMData.equalizerXmt[10] = 100");
  file.println("EEPROMData.equalizerXmt[11] = 100");
  file.println("EEPROMData.equalizerXmt[12] = 100");
  file.println("EEPROMData.equalizerXmt[13] = 100");

  file.println("EEPROMData.currentMicThreshold = -10");
  file.println("EEPROMData.currentMicCompRatio = 5.0");
  file.println("EEPROMData.currentMicAttack = 0.1");
  file.println("EEPROMData.currentMicRelease = 2.0");
  file.println("EEPROMData.currentMicGain = -10");

  file.println("EEPROMData.switchValues[0] = 924");
  file.println("EEPROMData.switchValues[1] = 870");
  file.println("EEPROMData.switchValues[2] = 817");
  file.println("EEPROMData.switchValues[3] = 769");
  file.println("EEPROMData.switchValues[4] = 713");
  file.println("EEPROMData.switchValues[5] = 669");
  file.println("EEPROMData.switchValues[6] = 616");
  file.println("EEPROMData.switchValues[7] = 565");
  file.println("EEPROMData.switchValues[8] = 513");
  file.println("EEPROMData.switchValues[9] = 459");
  file.println("EEPROMData.switchValues[10] = 407");
  file.println("EEPROMData.switchValues[11] = 356");
  file.println("EEPROMData.switchValues[12] = 298");
  file.println("EEPROMData.switchValues[13] = 242");
  file.println("EEPROMData.switchValues[14] = 183");
  file.println("EEPROMData.switchValues[15] = 131");
  file.println("EEPROMData.switchValues[16] = 67");
  file.println("EEPROMData.switchValues[17] = 10");

  file.println("EEPROMData.LPFcoeff = 0.0");
  file.println("EEPROMData.NR_PSI = 0.0");
  file.println("EEPROMData.NR_alpha = 0.0");
  file.println("EEPROMData.NR_beta = 0.0");
  file.println("EEPROMData.omegaN = 0.0");
  file.println("EEPROMData.pll_fmax = 4000.0");

  file.println("EEPROMData.powerOutCW[0] = 0.188");
  file.println("EEPROMData.powerOutCW[1] = 0.21");
  file.println("EEPROMData.powerOutCW[2] = 0.34");
  file.println("EEPROMData.powerOutCW[3] = 0.44");
  file.println("EEPROMData.powerOutCW[4] = 0.31");
  file.println("EEPROMData.powerOutCW[5] = 0.31");
  file.println("EEPROMData.powerOutCW[6] = 0.31");

  file.println("EEPROMData.powerOutSSB[0] = 0.188");
  file.println("EEPROMData.powerOutSSB[1] = 0.11");
  file.println("EEPROMData.powerOutSSB[2] = 0.188");
  file.println("EEPROMData.powerOutSSB[3] = 0.21");
  file.println("EEPROMData.powerOutSSB[4] = 0.23");
  file.println("EEPROMData.powerOutSSB[5] = 0.23");
  file.println("EEPROMData.powerOutSSB[6] = 0.24");

  file.println("EEPROMData.CWPowerCalibrationFactor[0] = 0.023");
  file.println("EEPROMData.CWPowerCalibrationFactor[1] = 0.023");
  file.println("EEPROMData.CWPowerCalibrationFactor[2] = 0.038");
  file.println("EEPROMData.CWPowerCalibrationFactor[3] = 0.052");
  file.println("EEPROMData.CWPowerCalibrationFactor[4] = 0.051");
  file.println("EEPROMData.CWPowerCalibrationFactor[5] = 0.028");
  file.println("EEPROMData.CWPowerCalibrationFactor[6] = 0.028");

  file.println("EEPROMData.SSBPowerCalibrationFactor[0] = 0.017");
  file.println("EEPROMData.SSBPowerCalibrationFactor[1] = 0.019");
  file.println("EEPROMData.SSBPowerCalibrationFactor[2] = 0.017");
  file.println("EEPROMData.SSBPowerCalibrationFactor[3] = 0.019");
  file.println("EEPROMData.SSBPowerCalibrationFactor[4] = 0.021");
  file.println("EEPROMData.SSBPowerCalibrationFactor[5] = 0.020");
  file.println("EEPROMData.SSBPowerCalibrationFactor[6] = 0.022");

  file.println("EEPROMData.IQAmpCorrectionFactor[0] = 1.008");
  file.println("EEPROMData.IQAmpCorrectionFactor[1] = 1.027");
  file.println("EEPROMData.IQAmpCorrectionFactor[2] = 1.057");
  file.println("EEPROMData.IQAmpCorrectionFactor[3] = 1.061");
  file.println("EEPROMData.IQAmpCorrectionFactor[4] = 1.06");
  file.println("EEPROMData.IQAmpCorrectionFactor[5] = 1.092");
  file.println("EEPROMData.IQAmpCorrectionFactor[6] = 1.105");

  file.println("EEPROMData.IQPhaseCorrectionFactor[0] = 0.003");
  file.println("EEPROMData.IQPhaseCorrectionFactor[1] = 0.007");
  file.println("EEPROMData.IQPhaseCorrectionFactor[2] = -0.027");
  file.println("EEPROMData.IQPhaseCorrectionFactor[3] = -0.041");
  file.println("EEPROMData.IQPhaseCorrectionFactor[4] = -0.047");
  file.println("EEPROMData.IQPhaseCorrectionFactor[5] = -0.032");
  file.println("EEPROMData.IQPhaseCorrectionFactor[6] = -0.044");

  file.println("EEPROMData.IQXAmpCorrectionFactor[0] = 1.098");
  file.println("EEPROMData.IQXAmpCorrectionFactor[1] = 1.043");
  file.println("EEPROMData.IQXAmpCorrectionFactor[2] = 0.956");
  file.println("EEPROMData.IQXAmpCorrectionFactor[3] = 0.956");
  file.println("EEPROMData.IQXAmpCorrectionFactor[4] = 0.741");
  file.println("EEPROMData.IQXAmpCorrectionFactor[5] = 0.9");
  file.println("EEPROMData.IQXAmpCorrectionFactor[6] = 0.9");

  file.println("EEPROMData.IQXPhaseCorrectionFactor[0] = 0.021");
  file.println("EEPROMData.IQXPhaseCorrectionFactor[1] = 0.239");
  file.println("EEPROMData.IQXPhaseCorrectionFactor[2] = 0.581");
  file.println("EEPROMData.IQXPhaseCorrectionFactor[3] = 0.887");
  file.println("EEPROMData.IQXPhaseCorrectionFactor[4] = 0.891");
  file.println("EEPROMData.IQXPhaseCorrectionFactor[5] = 0.75");
  file.println("EEPROMData.IQXPhaseCorrectionFactor[6] = 0.75");

  file.println("EEPROMData.favoriteFreqs[0] = 3560000");
  file.println("EEPROMData.favoriteFreqs[1] = 3690000");
  file.println("EEPROMData.favoriteFreqs[2] = 7030000");
  file.println("EEPROMData.favoriteFreqs[3] = 7200000");
  file.println("EEPROMData.favoriteFreqs[4] = 14060000");
  file.println("EEPROMData.favoriteFreqs[5] = 14200000");
  file.println("EEPROMData.favoriteFreqs[6] = 21060000");
  file.println("EEPROMData.favoriteFreqs[7] = 21285000");
  file.println("EEPROMData.favoriteFreqs[8] = 28060000");
  file.println("EEPROMData.favoriteFreqs[9] = 28365000");
  file.println("EEPROMData.favoriteFreqs[10] = 5000000");
  file.println("EEPROMData.favoriteFreqs[11] = 10000000");
  file.println("EEPROMData.favoriteFreqs[12] = 15000000");

  file.println("EEPROMData.lastFrequencies[0][0] = 3985000");
  file.println("EEPROMData.lastFrequencies[1][0] = 7200000");
  file.println("EEPROMData.lastFrequencies[2][0] = 14285000");
  file.println("EEPROMData.lastFrequencies[3][0] = 18130000");
  file.println("EEPROMData.lastFrequencies[4][0] = 21385000");
  file.println("EEPROMData.lastFrequencies[5][0] = 24950000");
  file.println("EEPROMData.lastFrequencies[6][0] = 28385800");

  file.println("EEPROMData.lastFrequencies[0][1] = 3560000");
  file.println("EEPROMData.lastFrequencies[1][1] = 7030000");
  file.println("EEPROMData.lastFrequencies[2][1] = 14060000");
  file.println("EEPROMData.lastFrequencies[3][1] = 18096000");
  file.println("EEPROMData.lastFrequencies[4][1] = 21060000");
  file.println("EEPROMData.lastFrequencies[5][1] = 24906000");
  file.println("EEPROMData.lastFrequencies[6][1] = 28060000");

  file.println("EEPROMData.centerFreq = 7150000");
  file.close();
  return 1;
}

/*****
  Purpose: Copy EEPROMData objects into working variables

  Parameter list:
    void

  Return value;
    void

*****/
void AssignEEPROMObjectToVariable()
{
  int i;

  strcpy(EEPROMData.versionSettings, VERSION);                // Update version
  strcpy(versionSettings, EEPROMData.versionSettings);        // Update working variable
  AGCMode                 = EEPROMData.AGCMode;     // 1 byte
  audioVolume             = EEPROMData.audioVolume; // 4 bytes
  rfGainAllBands          = EEPROMData.rfGainAllBands;
  spectrumNoiseFloor      = EEPROMData.spectrumNoiseFloor; // AFP 09-26-22
  tuneIndex               = EEPROMData.tuneIndex;
  transmitPowerLevel      = EEPROMData.powerLevel;
  xmtMode                 = EEPROMData.xmtMode;            // AFP 09-26-22
  nrOptionSelect          = EEPROMData.nrOptionSelect;     // 1 byte
  currentScale            = EEPROMData.currentScale;
  spectrum_zoom           = EEPROMData.spectrum_zoom;
  spectrum_display_scale  = EEPROMData.spectrum_display_scale;// 4 bytes

  CWFilterIndex       = EEPROMData.CWFilterIndex;  // Off
  paddleDit           = EEPROMData.paddleDit;
  paddleDah           = EEPROMData.paddleDah;
  decoderFlag         = EEPROMData.decoderFlag;
  keyType             = EEPROMData.keyType;  // straight key = 0, keyer = 1
  currentWPM          = EEPROMData.currentWPM; // 4 bytes
  sidetoneVolume      = EEPROMData.sidetoneVolume;// 4 bytes
  cwTransmitDelay     = EEPROMData.cwTransmitDelay;   // 4 bytes

  activeVFO           = EEPROMData.activeVFO;  // 2 bytes
  freqIncrement       = EEPROMData.freqIncrement;  // 4 bytes

  currentBand         = EEPROMData.currentBand; // 4 bytes
  currentBandA        = EEPROMData.currentBandA;// 4 bytes
  currentBandB        = EEPROMData.currentBandB;// 4 bytes
  currentFreqA        = EEPROMData.currentFreqA;
  currentFreqB        = EEPROMData.currentFreqB;
  freqCorrectionFactor = EEPROMData.freqCorrectionFactor;

  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    recEQ_Level[i]    = EEPROMData.equalizerRec[i];// 4 bytes each
    xmtEQ_Level[i]    = EEPROMData.equalizerXmt[i];
  }
  currentMicThreshold = EEPROMData.currentMicThreshold;// 4 bytes      // AFP 09-22-22
  currentMicCompRatio = EEPROMData.currentMicCompRatio;
  currentMicAttack    = EEPROMData.currentMicAttack;
  currentMicRelease   = EEPROMData.currentMicRelease;
  currentMicGain      = EEPROMData.currentMicGain;

  for (i = 0; i < NUMBER_OF_SWITCHES; i++) {
    switchThreshholds[i] = EEPROMData.switchValues[i];
  }
  LPFcoeff             = EEPROMData.LPFcoeff;// 4 bytes
  NR_PSI               = EEPROMData.NR_PSI;// 4 bytes
  NR_alpha             = EEPROMData.NR_alpha;// 4 bytes
  NR_beta              = EEPROMData.NR_beta;// 4 bytes
  omegaN               = EEPROMData.omegaN;// 4 bytes
  pll_fmax             = EEPROMData.pll_fmax;// 4 bytes
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    powerOutCW[i]                = EEPROMData.powerOutCW[i];
    powerOutSSB[i]               = EEPROMData.powerOutSSB[i];
    CWPowerCalibrationFactor[i]  = EEPROMData.CWPowerCalibrationFactor[i];  // 0.019;
    SSBPowerCalibrationFactor[i] = EEPROMData.SSBPowerCalibrationFactor[i]; // 0.008
    IQAmpCorrectionFactor[i]     = EEPROMData.IQAmpCorrectionFactor[i];
    IQPhaseCorrectionFactor[i]   = EEPROMData.IQPhaseCorrectionFactor[i];
    IQXAmpCorrectionFactor[i]    = EEPROMData.IQXAmpCorrectionFactor[i] ;
    IQXPhaseCorrectionFactor[i]  = EEPROMData.IQXPhaseCorrectionFactor[i];
    lastFrequencies[i][0]        = EEPROMData.lastFrequencies[i][0];
    lastFrequencies[i][1]        = EEPROMData.lastFrequencies[i][1];
  }
  for (i = 0; i < 13; i++) {
    favoriteFrequencies[i]       = EEPROMData.favoriteFreqs[i];
  }
  centerFreq = EEPROMData.centerFreq; // 4 bytes
}

/*****
  Purpose: Converts EEPROMData members and value to ASCII

  Parameter list:
    File file             file handle for the SD file
    char *buffer          pointer to the EEPROMData member
    int val               the current value of the member
    int whatDataType      1 = int, 2 = long, 3 = float, 4 = string

  Return value;
    void

*****/
void ConvertForEEPROM(File file, char *buffer, int val, int whatDataType)
{
  char temp[10];

  temp[0] = '\0';
  switch (whatDataType) {
    case 1:                       // int
      itoa(val, temp, DEC);
      break;
    case 2:                       // long
      ltoa(val, temp, DEC);
      break;
    case 3:                       // float
      dtostrf(val, 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
      break;
    case 4:
      strcpy(temp, VERSION);
      break;
    default:
#ifdef DEBUG
      Serial.println("Error");
#endif
      break;
  }
  strcat(buffer, " = ");
  strcat(buffer, temp);
#ifdef DEBUG
  Serial.println(buffer);
#endif
  file.println(buffer);
  buffer[0] = '\0';
}

/*****
  Purpose: Copy working variables into EEPROMData object variables

  Parameter list:
    void

  Return value;
    void

*****/
void SDUpdate()
{
  char buffer[100];
  char temp[12];
  int i;
  File file = SD.open("SDEEPROMData.txt", FILE_WRITE);  // Get a file handle
  if (!file) {                                          // Can't open the file
    return;                                             // Go home
  }
  //  strcpy(EEPROMData.versionSettings, VERSION);          // Only copy to EEPROM, not SD     // Build like the other members
  file.seek(0L);                                        // Reset to BOF so we don't append

  //  file.print(                                           // Write everything to the SD card

  //    EEPROMData.versionSettings        = VERSION;
  ConvertForEEPROM(file, (char *)"EEPROMData.versionSettings", 0, 4);
  //    EEPROMData.AGCMode                = AGCMode;
  ConvertForEEPROM(file, (char *)"EEPROMData.AGCMode", AGCMode, 1);
  //    EEPROMData.audioVolume            = audioVolume;
  ConvertForEEPROM(file, (char *)"EEPROMData.audioVolume", audioVolume, 1);
  //    EEPROMData.rfGainAllBands         = rfGainAllBands;
  ConvertForEEPROM(file, (char *)"EEPROMData.rfGainAllBands", rfGainAllBands, 1);
  //    EEPROMData.spectrumNoiseFloor     = spectrumNoiseFloor;
  ConvertForEEPROM(file, (char *)"EEPROMData.spectrumNoiseFloor", spectrumNoiseFloor, 1);
  //    EEPROMData.tuneIndex              = tuneIndex;
  ConvertForEEPROM(file, (char *)"EEPROMData.tuneIndex", tuneIndex, 1);
  //    EEPROMData.powerLevel             = transmitPowerLevel;
  ConvertForEEPROM(file, (char *)"EEPROMData.powerLevel", transmitPowerLevel, 1);
  //    EEPROMData.xmtMode                = xmtMode;
  ConvertForEEPROM(file, (char *)"EEPROMData.xmtMode", xmtMode, 1);
  //    EEPROMData.nrOptionSelect         = nrOptionSelect;
  ConvertForEEPROM(file, (char *)"EEPROMData.nrOptionSelect", nrOptionSelect, 1);
  //    EEPROMData.currentScale           = currentScale;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentScale", currentScale, 1);
  //    EEPROMData.spectrum_zoom          = spectrum_zoom;
  ConvertForEEPROM(file, (char *)"EEPROMData.spectrum_zoom", spectrum_zoom, 1);
  EEPROMData.spectrum_display_scale = spectrum_display_scale;
  ConvertForEEPROM(file, (char *)"EEPROMData.spectrum_display_scale", spectrum_display_scale, 1);

  //    EEPROMData.CWFilterIndex          = CWFilterIndex;
  ConvertForEEPROM(file, (char *)"EEPROMData.CWFilterIndex", CWFilterIndex, 1);
  //    EEPROMData.paddleDit              = paddleDit;
  ConvertForEEPROM(file, (char *)"EEPROMData.paddleDit", paddleDit, 1);
  //    EEPROMData.paddleDah              = paddleDah;
  ConvertForEEPROM(file, (char *)"EEPROMData.paddleDah", paddleDah, 1);
  //    EEPROMData.decoderFlag            = decoderFlag;
  ConvertForEEPROM(file, (char *)"EEPROMData.decoderFlag", decoderFlag, 1);
  //    EEPROMData.keyType                = keyType;
  ConvertForEEPROM(file, (char *)"EEPROMData.keyType", keyType, 1);
  //    EEPROMData.currentWPM             = currentWPM;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentWPM", currentWPM, 1);
  //    EEPROMData.sidetoneVolume         = sidetoneVolume;
  ConvertForEEPROM(file, (char *)"EEPROMData.sidetoneVolume", sidetoneVolume, 3);      // This is a float
  //    EEPROMData.cwTransmitDelay        = cwTransmitDelay;
  ConvertForEEPROM(file, (char *)"EEPROMData.cwTransmitDelay", cwTransmitDelay, 1);

  //    EEPROMData.activeVFO              = activeVFO;
  ConvertForEEPROM(file, (char *)"EEPROMData.activeVFO", activeVFO, 1);
  //    EEPROMData.freqIncrement          = freqIncrement;
  ConvertForEEPROM(file, (char *)"EEPROMData.freqIncrement", freqIncrement, 1);

  //    EEPROMData.currentBand            = currentBand;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentBand", currentBand, 1);
  //    EEPROMData.currentBandA           = currentBandA;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentBandA", currentBandA, 1);
  //    EEPROMData.currentBandB           = currentBandB;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentBandB", currentBandB, 1);
  //    EEPROMData.currentFreqA           = currentFreqA;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentFreqA", currentFreqA, 2);    // These are longs
  //    EEPROMData.currentFreqB           = currentFreqB;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentFreqB", currentFreqB, 2);
  //    EEPROMData.freqCorrectionFactor   = freqCorrectionFactor;
  ConvertForEEPROM(file, (char *)"EEPROMData.freqCorrectionFactor", freqCorrectionFactor, 2);

  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    //    EEPROMData.equalizerRec[i]      = recEQ_Level[i];// 4 bytes each
    strcpy(buffer, "EEPROMData.equalizerRec[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    itoa(recEQ_Level[i], temp, DEC);
    strcat(buffer, "] = ");
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.equalizerXmt[i]      = xmtEQ_Level[i];
  for (i = 0; i < EQUALIZER_CELL_COUNT; i++) {
    strcpy(buffer, "EEPROMData.equalizerXmt[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    itoa(xmtEQ_Level[i], temp, DEC);
    strcat(buffer, "] = ");
    strcat(buffer, temp);
    file.println(buffer);
  }
  //  EEPROMData.currentMicThreshold    = currentMicThreshold;// 4 bytes
  ConvertForEEPROM(file, (char *)"EEPROMData.currentMicThreshold", currentMicThreshold, 1);
  //  EEPROMData.currentMicCompRatio    = currentMicCompRatio;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentMicCompRatio", currentMicCompRatio, 3);    //Floats
  //  EEPROMData.currentMicAttack       = currentMicAttack;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentMicAttack", currentMicAttack, 3);
  //  EEPROMData.currentMicRelease      = currentMicRelease;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentMicRelease", currentMicRelease, 3);
  //  EEPROMData.currentMicGain         = currentMicGain ;
  ConvertForEEPROM(file, (char *)"EEPROMData.currentMicGain", currentMicGain, 1);

  for (i = 0; i < NUMBER_OF_SWITCHES; i++) {
    //  EEPROMData.switchValues[i]      = switchThreshholds[i];
    strcpy(buffer, "EEPROMData.switchValues[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    itoa(switchThreshholds[i], temp, DEC);
    strcat(buffer, "] = ");
    strcat(buffer, temp);
    file.println(buffer);
  }
  //  EEPROMData.LPFcoeff               = LPFcoeff;
  ConvertForEEPROM(file, (char *)"EEPROMData.LPFcoeff", LPFcoeff, 3);
  //  EEPROMData.NR_PSI                 = NR_PSI;
  ConvertForEEPROM(file, (char *)"EEPROMData.NR_PSI", NR_PSI, 3);
  //  EEPROMData.NR_alpha               = NR_alpha;
  ConvertForEEPROM(file, (char *)"EEPROMData.NR_alpha", NR_alpha, 3);
  //  EEPROMData.NR_beta                = NR_beta;
  ConvertForEEPROM(file, (char *)"EEPROMData.NR_beta", NR_beta, 3);
  //  EEPROMData.omegaN                 = omegaN;
  ConvertForEEPROM(file, (char *)"EEPROMData.omegaN", omegaN, 3);
  //  EEPROMData.pll_fmax = pll_fmax;
  ConvertForEEPROM(file, (char *)"EEPROMData.pll_fmax", pll_fmax, 3);

  //    EEPROMData.powerOutCW[i]                = powerOutCW[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.powerOutCW[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(powerOutCW[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.powerOutSSB[i]               = powerOutSSB[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.powerOutSSB[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(powerOutSSB[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.CWPowerCalibrationFactor[i]  = CWPowerCalibrationFactor[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(CWPowerCalibrationFactor[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.SSBPowerCalibrationFactor[i] = SSBPowerCalibrationFactor[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(SSBPowerCalibrationFactor[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.IQAmpCorrectionFactor[i]     = IQAmpCorrectionFactor[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(IQAmpCorrectionFactor[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.IQPhaseCorrectionFactor[i]   = IQPhaseCorrectionFactor[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(IQPhaseCorrectionFactor[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.IQXAmpCorrectionFactor[i]    = IQXAmpCorrectionFactor[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(IQXAmpCorrectionFactor[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.IQXPhaseCorrectionFactor[i]  = IQXPhaseCorrectionFactor[i];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.IQXPhaseCorrectionFactor[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(IQXPhaseCorrectionFactor[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.lastFrequencies[i][0]        = lastFrequencies[i][0];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.lastFrequencies[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "][0] = ");
    dtostrf(lastFrequencies[i][0], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //    EEPROMData.lastFrequencies[i][1]        = lastFrequencies[i][1];
  for (i = 0; i < NUMBER_OF_BANDS; i++) {
    strcpy(buffer, "EEPROMData.lastFrequencies[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "][1] = ");
    dtostrf(lastFrequencies[i][1], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  for (i = 0; i < 13; i++) {
    //  EEPROMData.favoriteFreqs[i]             = favoriteFrequencies[i];
    strcpy(buffer, "EEPROMData.favoriteFreqs[");
    itoa(i, temp, DEC);
    strcat(buffer, temp);
    strcat(buffer, "] = ");
    dtostrf(favoriteFrequencies[i], 9, 4, temp);   //Field of up to 9 digits with 4 decimal places
    strcat(buffer, temp);
    file.println(buffer);
  }
  //  EEPROMData.centerFreq                     = centerFreq;
  ConvertForEEPROM(file, (char *)"EEPROMData.centerFreq", centerFreq, 2);

  file.close();
}

/*****
  Purpose: Writes the current values of the working variable
           to the SD card as SDEEPROMData.txt

  Parameter list:
    void

  Return value;
    int               0 = no write, 1 = write
*****/
int CopyEEPROMToSD()
{
  char buffer[100];
  char temp[15];
  char digits[5];
  int i;

  File file = SD.open("SDEEPROMData.txt", O_RDWR);   // Get a file handle
  if (!file) {                                                            // Can't open the file
    return 0;                                                             // Go home
  }
  file.seek(0L);                                        // Reset to BOF so we don't append
  strcpy(buffer, "EEPROMData.versionSettings = ");
  strcat(buffer, VERSION);
  file.println(buffer);

  strcpy(buffer, "EEPROMData.AGCMode = ");
  itoa(AGCMode, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.audioVolume = ");
  itoa(audioVolume, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.rfGainAllBands = ");
  itoa(rfGainAllBands, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.spectrumNoiseFloor = ");
  itoa(spectrumNoiseFloor, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.tuneIndex = ");
  itoa(tuneIndex, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.powerLevel = ");
  itoa(transmitPowerLevel, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.xmtMode = 0");
  itoa(xmtMode, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.nrInUse = ");
  itoa(nrOptionSelect, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentScale = ");
  itoa(currentScale, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.spectrum_zoom = ");
  itoa(spectrum_zoom, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.spectrum_zoom = ");            // long data type
  ltoa(spectrum_zoom, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.spectrum_display_scale = ");   // float data type
  dtostrf(spectrum_display_scale, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.CWFilterIndex = ");
  itoa(CWFilterIndex, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.paddleDit = ");
  itoa(paddleDit, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.paddleDah = ");
  itoa(paddleDah, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.decoderFlag = ");
  itoa(decoderFlag, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.keyType = ");
  itoa(keyType, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentWPM = ");
  itoa(currentWPM, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.sidetoneVolume = ");   // float data type
  dtostrf(sidetoneVolume, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.cwTransmitDelay = ");            // long data type
  ltoa(cwTransmitDelay, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.activeVFO = 0");
  itoa(activeVFO, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.freqIncrement = ");
  itoa(freqIncrement, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentBand = ");
  itoa(currentBand, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentBandA = ");
  itoa(currentBandA, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentBandB = ");
  itoa(currentBandB, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentFreqA = ");            // long data type
  ltoa(currentFreqA, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentFreqB = ");            // long data type
  ltoa(currentFreqB, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.freqCorrectionFactor = ");            // long data type
  ltoa(freqCorrectionFactor, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);

  for (i = 0; i < 14; i++) {
    itoa(i, digits, DEC);
    strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
    strcat(buffer, digits);
    strcat(buffer, "] = 100");
    file.println(buffer);
  }
  for (i = 0; i < 14; i++) {
    itoa(i, digits, DEC);
    strcpy(buffer, "EEPROMData.equalizerXmt[");            // long data type
    strcat(buffer, digits);
    strcat(buffer, "] = 100");
    file.println(buffer);
  }
  strcpy(buffer, "EEPROMData.currentMicThreshold = ");
  itoa(currentMicThreshold, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentMicCompRatio = ");   // float data type
  dtostrf(currentMicCompRatio, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentMicAttack = ");   // float data type
  dtostrf(currentMicAttack, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentMicRelease = ");   // float data type
  dtostrf(currentMicRelease, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.currentMicGain = ");
  itoa(currentMicGain, temp, DEC);
  strcat(buffer, temp);
  file.println(buffer);

  strcpy(buffer, "EEPROMData.switchValues[0] = ");            // long data type
  itoa(924, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[1] = ");            // long data type
  itoa(870, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[2] = ");            // long data type
  itoa(817, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[3] = ");            // long data type
  itoa(769, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[4] = ");            // long data type
  itoa(713, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[5] = ");            // long data type
  itoa(669, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[6] = ");            // long data type
  itoa(616, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[7] = ");            // long data type
  itoa(565, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[8] = ");            // long data type
  itoa(513, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[9] = ");            // long data type
  itoa(459, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[10] = ");            // long data type
  itoa(407, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[11] = ");            // long data type
  itoa(356, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[12] = ");            // long data type
  itoa(298, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[13] = ");            // long data type
  itoa(242, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[14] = ");            // long data type
  itoa(183, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[15] = ");            // long data type
  itoa(131, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[16] = ");            // long data type
  itoa(67, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.switchValues[17] = ");            // long data type
  itoa(10, digits, DEC);
  strcat(buffer, digits);
  file.println(buffer);

  strcpy(buffer, "EEPROMData.LPFcoeff = ");   // float data type
  dtostrf(LPFcoeff, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EPROMData.NR_PSI = ");   // float data type
  dtostrf(NR_PSI, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.NR_alpha = ");   // float data type
  dtostrf(NR_alpha, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.NR_beta = ");   // float data type
  dtostrf(NR_beta, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.omegaN = ");   // float data type
  dtostrf(omegaN, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);
  strcpy(buffer, "EEPROMData.pll_fmax = ");   // float data type
  dtostrf(pll_fmax, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);

  strcpy(buffer, "EEPROMData.powerOutCW[");   // float data type
  dtostrf(pll_fmax, 6, 1, temp);              // Field of up to 6 digits with 1 decimal place
  strcat(buffer, temp);
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.188");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.21");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.34");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.44");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.31");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.31");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.equalizerRec[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.31");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.188");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.11");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.188");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.21");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.23");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.23");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.powerOutSSB[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.24");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.023");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.023");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.038");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.052");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.051");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.028");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.CWPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.038");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.017");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.019");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.017");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.019");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.021");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.020");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.SSBPowerCalibrationFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.022");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.008");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.027");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.057");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.061");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.06");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.092");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.IQAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.105");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.003");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.007");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = -0.027");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = -0.041");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = -0.047");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = -0..32");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.IQPhaseCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = -0.044");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.098");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 1.043");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.956");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.956");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.741");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.9");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.9");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");
  strcat(buffer, digits);
  strcat(buffer, "] = 0.021");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");
  strcat(buffer, digits);
  strcat(buffer, "] = 0.239");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");
  strcat(buffer, digits);
  strcat(buffer, "] = 0.581");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");
  strcat(buffer, digits);
  strcat(buffer, "] = 0.887");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");
  strcat(buffer, digits);
  strcat(buffer, "] = 0.891");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.75");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 0.75");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 3560000");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 3690000");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 7030000");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 7200000");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 14060000");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 14200000");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 21060000");
  file.println(buffer);
  itoa(7, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 21285000");
  file.println(buffer);
  itoa(8, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 28060000");
  file.println(buffer);
  itoa(9, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 28365000");
  file.println(buffer);
  itoa(10, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 5000000");
  file.println(buffer);
  itoa(11, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 10000000");
  file.println(buffer);
  itoa(12, digits, DEC);
  strcpy(buffer, "EEPROMData.IQXAmpCorrectionFactor[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "] = 15000000");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 3985000");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 7200000");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 14285000");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 18130000");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 21385000");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 24950000");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][0] = 28385800");
  file.println(buffer);

  itoa(0, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 3560000");
  file.println(buffer);
  itoa(1, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 7030000");
  file.println(buffer);
  itoa(2, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 14060000");
  file.println(buffer);
  itoa(3, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 18096000");
  file.println(buffer);
  itoa(4, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 21060000");
  file.println(buffer);
  itoa(5, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 24906000");
  file.println(buffer);
  itoa(6, digits, DEC);
  strcpy(buffer, "EEPROMData.lastFrequencies[");            // long data type
  strcat(buffer, digits);
  strcat(buffer, "][1] = 28060000");
  file.println(buffer);

  file.println("EEPROMData.centerFreq = 7150000");
  file.close();
  return 1;
}

/*****
  Purpose: The SD card is present, but does it contain valid data?

  Parameter list:
    void

  Return value;
    int               0 = no valid data, 1 = valid data
*****/
/*
int SDDataCheck()
{
  char buffer[100], c = '\0';
  int i;

  if (!SD.begin(chipSelect)) {
    return 0;                                                             // Go home
  }
  File file = SD.open("SDEEPROMData.txt");   // Get a file handle
  if (!file) {                                                            // Can't open the file
    return 0;                                                             // Go home
  }

  i = 0;
  while (c != '\n') {
    c = file.read();
    if (c < 0) {                    // Read failed
      file.close();
      return 0;
    }
    buffer[i++] = c;
  }
  buffer[i] = '\0';
  file.close();
  file.seek(0L);                                        // Reset to BOF so we don't append
  return 1;
}
*/
/*****
  Purpose: See if the EEPROM has ever been set

  Parameter list:
    void

  Return value;
    int               1 = used before, 0 = nope
*****/
int ValidEEPROMData()
{
  int val = EEPROMData.switchValues[0];
  if (val > 0 && val < 1023)
    return VALID_EEPROM_DATA;             // return 1
  else
    return INVALID_EEPROM_DATA;           // return 0
}

/*****
  Purpose: Update the version number only in EEPROM

  Parameter list:
    void

  Return value;
    void
*****/
void UpdateEEPROMVersionNumber()
{
  strcpy(EEPROMData.versionSettings, VERSION);   // Copy the latest version to EEPROM
}

/*****
  Purpose: Does the SD card have any data on it?

  Parameter list:
    void

  Return value;
    int               0 = SD is untouched, 1 = has data
*****/
/*
int FirstTimeSDCard()
{
  char c = '\0';
  char temp[100];
  int index;

  File file = SD.open("SDEEPROMData.txt", FILE_READ);   // Get a file handle

  if (!file) {                                          // Can't open the file
    tft.setFontScale( (enum RA8875tsize) 1);
    tft.setTextColor(RA8875_RED, RA8875_BLACK);
    tft.setCursor(100, 240);
    tft.print("SD card cannot be opened.");
    MyDelay(2000L);                                     // Given them time to read it.
    return 0;                                           // Go home
  }
  index = 0;
  while (c != '\n') {                                   // Try to read 1st line of SD card
    c = file.read();
    temp[index++] = c;
  }
  temp[index] = '\0';                                   // Make is a string
  file.close();
  if (c != -1) {
    return 1;                                           // Could read data
  } else {
    return 0;                                           // There's no data on the card
  }
}
*/

/*****
  Purpose: Reads the SD EEPROM data and writes it to the Serial object

  Parameter list:
    void

  Return value;
    int               0 = SD is untouched, 1 = has data
*****/
void SDEEPROMDump()
{
  if (!SD.begin(chipSelect))
  {
    Serial.print("SD card cannot be initialized.");
  }
  // open the file.
  Serial.println("----- Start SD EEPROM File Dump ------");
  File dataFile = SD.open("SDEEPROMData.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  } else {
    Serial.println("error opening SDEEPROMData.txt");
  }
}

/*****
  Purpose: Clears the first 1K of emulated EEPROM to 0xff

  Parameter list:
    void

  Return value;
    void
*****/
void ClearEEPROM()
{
  int i;
  for (i = 0; i < 1000; i++) {
    EEPROM.write(i, 0xFF);
  }
}

/*****
  Purpose: Read the EEPROM from: a) EEPROM memory, b) SD card memory, or c) defaults

  Parameter list:
    void

  Return value;
    void
*****/
void EEPROMStartup()
{
  EEPROMRead();
/*
Serial.print("EEPROMData.versionSettings = |");
Serial.print(EEPROMData.versionSettings);
Serial.println("|");
Serial.print("VERSION = |");
Serial.print(VERSION);
Serial.println("|");
*/
  if (strcmp(EEPROMData.versionSettings, VERSION) == 0) {     // Up to date?
    return;                                                   // Yep.
  }
  strcpy(EEPROMData.versionSettings, VERSION);              // Update the version, but leave everything else unchanged

  EEPROMSaveDefaults();                                       // Write the defaults so at least the radio can function
  SaveAnalogSwitchValues();
  EEPROMRead();
  EEPROM.put(0, EEPROMData);
  
  CopyEEPROMToSD();
#ifdef DEBUG1
  SDEEPROMDump();
#endif
}
