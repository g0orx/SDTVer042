#ifndef BEENHERE
#include "SDT.h"
#endif

#ifdef G0ORX_CAT
// Kenwood TS2000 CAT Interface - Minimal support for WDSP-X
// John Melton G0ORX

#define DEBUG_CAT

#ifdef DEBUG_CAT
// For help debugging as serial port used for CAT
extern void MorseCharacterDisplay(char currentLetter);
#endif

//bool catTX=false;
static char catCommand[128];
static int catCommandIndex=0;
static char outputBuffer[256];

void IFResponse() {
  int mode;
  if (xmtMode == CW_MODE) {
    mode=3;
  } else {
    switch(bands[currentBand].mode) {
      case DEMOD_LSB:
        mode=1; // LSB
        break;
      case DEMOD_USB:
        mode=2; // USB
        break;
      case DEMOD_AM:
      case DEMOD_SAM:
        mode=5; // AM
        break;
      default:
        mode=1; // LSB
        break;
    }
  }
  sprintf(outputBuffer,
                  "IF%011ld%04d%+06d%d%d%d%02d%d%d%d%d%d%d%02d%d;",
                  currentFreqA,
                  freqIncrement<10000?freqIncrement:1000,
                  0, // rit
                  0, // rit enabled
                  0, // xit enabled
                  0,0, // Channel bank
                  my_ptt==LOW?1:0, // RX/TX
                  mode, // operating mode (SSB)
                  0, // RX VFO
                  0, // Scan Status
                  0, // split,
                  0, // CTCSS enabled
                  0, // CTCSS
                  0);
}

void processCATCommand() {
  char p1;
  bool xmtMode_changed= false;
  
#if defined(DEBUG_CAT) && defined(G0ORX_FRONTPANEL)
  FrontPanelSetLed(0, 1);
#endif

  outputBuffer[0]='\0';

  switch(catCommand[0]) {
    case 'A':
      switch(catCommand[1]) {
        case 'G':  // Set/Read AF Gain 0..255
          p1=catCommand[2];  // 0=Main, 1=Sub IGNORED
          if(catCommand[3]==';') {
            sprintf(outputBuffer,"AG%c%03d;",p1,(int)(((double)audioVolume*255.0)/100.0));
          } else if(catCommand[6]==';') {
            audioVolume=(int)(((double)atoi(&catCommand[3])*100.0)/255.0);
            if(audioVolume>100) audioVolume=100;
            if(audioVolume<0) audioVolume=0;
            volumeChangeFlag = true;
          } else {
          }
          break;
        case 'I':  // Set/Read Auto Information
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"AI0;");
          } else {
            // process AI command
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'B':
      switch(catCommand[1]) {
        case 'D': // Band down
          if(catCommand[2]==';') {
            ExecuteButtonPress(BAND_DN);            
          }            
          break;
        case 'U': // Band up
          if(catCommand[2]==';') {
            ExecuteButtonPress(BAND_UP);
          }            
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'F':
      switch(catCommand[1]) {
        case 'A':  // Set/Read VFO A
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"FA%011ld;",currentFreqA);
          } else if(catCommand[13]==';') {
            long f=atol(&catCommand[2]);            
            if (activeVFO == VFO_A) {
              NCOFreq = 0;              
              lastFrequencies[currentBand][VFO_A] = currentFreq;
              currentBand =  currentBandA = ChangeBand(f, true);
              lastFrequencies[currentBand][VFO_A] = f;
              centerFreq = TxRxFreq = currentFreq = lastFrequencies[currentBand][VFO_A] + NCOFreq;
              EraseSpectrumDisplayContainer();
              DrawSpectrumDisplayContainer();
              DrawFrequencyBarValue();
              SetBand();
              SetFreq();
              ShowFrequency();
              ShowSpectrumdBScale();
              MyDelay(1L);
              AudioInterrupts();
            } else if(activeVFO == VFO_B) {
              lastFrequencies[currentBand]
              [VFO_A] = currentFreqA;
              currentBandB =  ChangeBand(f, false);
              lastFrequencies[currentBandB][VFO_A] = f;
              currentFreqA = f;
              tft.fillRect(FILTER_PARAMETERS_X + 180, FILTER_PARAMETERS_Y, 150, 20, RA8875_BLACK);
              ShowFrequency();
            }
          }                  
          break;
        case 'B': // Set/Read VFO B
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"FB%011ld;",currentFreqB);
          } else if(catCommand[13]==';') {
            long f=atol(&catCommand[2]);
            if (activeVFO == VFO_B) {
              NCOFreq = 0;              
              lastFrequencies[currentBand][VFO_B] = currentFreq;
              currentBand = currentBandB = ChangeBand(f, true);
              lastFrequencies[currentBand][VFO_B] = f;
              centerFreq = TxRxFreq = currentFreq = lastFrequencies[currentBand][VFO_B] + NCOFreq;
              EraseSpectrumDisplayContainer();
              DrawSpectrumDisplayContainer();
              DrawFrequencyBarValue();
              SetBand();
              SetFreq();
              ShowFrequency();
              ShowSpectrumdBScale();
              MyDelay(1L);
              AudioInterrupts();
            } else if(activeVFO == VFO_A) {
              lastFrequencies[currentBand][VFO_B] = currentFreqA;
              currentBand =  ChangeBand(f, false);
              lastFrequencies[currentBand][VFO_B] = f;
              currentFreqA = f;
              tft.fillRect(FILTER_PARAMETERS_X + 180, FILTER_PARAMETERS_Y, 150, 20, RA8875_BLACK);
              ShowFrequency();
            }
          }                   
          break;
        case 'R':  // Set/Read Receiver VFO
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"FR0;");
          } else {
            // process VFO
          }
          break;
        case 'T':  // Set/Read Transmitter VFO
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"FT0;");
          } else {
              // process VFO
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'I':
      switch(catCommand[1]) {
        case 'D':
          sprintf(outputBuffer,"ID019;"); // Kenwood TS-2000
          break;
        case 'F':
          IFResponse();
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'M':
      switch(catCommand[1]) {
        case 'D':
          if(catCommand[2]==';') {
            if (xmtMode == CW_MODE) {
              p1=3;
            } else {
              switch(bands[currentBand].mode) {
                case DEMOD_LSB:
                  p1=1; // LSB
                  break;
                case DEMOD_USB:
                  p1=2; // USB
                  break;
                case DEMOD_AM:
                case DEMOD_SAM:
                  p1=5; // AM
                  break;
                default:
                  p1=1; // LSB
                  break;
              }
            }
            sprintf(outputBuffer,"MD%d;",p1);
          } else {
            p1=atoi(&catCommand[2]);
            switch(p1) {
              case 1: // LSB
                bands[currentBand].mode = DEMOD_LSB;
                if(xmtMode != SSB_MODE) {
                  xmtMode = SSB_MODE;
                  xmtMode_changed= true;
                }
                break;
              case 2: // USB
                bands[currentBand].mode = DEMOD_USB;
                if(xmtMode != SSB_MODE) {
                  xmtMode = SSB_MODE;
                  xmtMode_changed= true;
                }
                break;
              case 3: // CW
                xmtMode = CW_MODE;
                if(bands[currentBand].mode != DEMOD_LSB && bands[currentBand].mode != DEMOD_USB) {
                  if(currentBand < BAND_20M) {
                    bands[currentBand].mode = DEMOD_LSB;
                  } else {
                    bands[currentBand].mode = DEMOD_USB;
                  }
                }
                xmtMode_changed= true;
                break;
              case 5: // AM
                bands[currentBand].mode = DEMOD_SAM; // default to SAM rather than AM
                break;
              default:
                bands[currentBand].mode = DEMOD_LSB;
                break;
            }
            if(xmtMode_changed) {
              tft.fillWindow();
              DrawSpectrumDisplayContainer();
              DrawFrequencyBarValue();
              DrawInfoWindowFrame();
              UpdateIncrementField();
              AGCPrep();
              UpdateAGCField();
              EncoderVolume();
              UpdateInfoWindow();
              ControlFilterF();
              BandInformation();
              FilterBandwidth();
              DrawSMeterContainer();
              DrawAudioSpectContainer();
              SpectralNoiseReductionInit();
              UpdateNoiseField();
              DrawBandWidthIndicatorBar();
              ShowName();
              ShowSpectrumdBScale();
              ShowTransmitReceiveStatus();
              ShowFrequency();
            } else {
              //AudioNoInterrupts();
              DrawBandWidthIndicatorBar();
              BandInformation();
              SetupMode(bands[currentBand].mode);
              ShowFrequency();
              ControlFilterF();
              FilterBandwidth();
              DrawSMeterContainer();
              ShowAnalogGain();
              AudioInterrupts();
            }
          }
          break;
        case 'G':  // Microphone Gain
          if(catCommand[2]==';') {
            // convert from -40 .. 30 to 0..100
            int g = (int)((double)(currentMicGain+40)*100.0/70.0);  
            sprintf(outputBuffer,"MG%03d;", g);
          } else {
            int g = atoi(&catCommand[2]);
            // convert from 0..100 to -40..30
            g=(int)(((double)g*70.0/100.0)-40.0);
            currentMicGain=g;
            EEPROMData.currentMicGain = currentMicGain;
            EEPROMWrite();          
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'N':
      switch(catCommand[1]) {
        case 'R': // Set/Read Noise Reduction
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"NR%d;",nrOptionSelect);
          } else if(catCommand[3]==';') {
            if(catCommand[2]=='0') {
              nrOptionSelect=0;
            } else {
              nrOptionSelect=atoi(&catCommand[2]);      
            }
            NROptions();
            UpdateNoiseField();
          }
          break;
        case 'T': // Set/Read Auto Notch
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"NT%d;",ANR_notchOn);
          } else if(catCommand[3]==';') {
            ANR_notchOn=atoi(&catCommand[2]);
            UpdateNotchField();
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'P':
      switch(catCommand[1]) {
        case 'C': // Output Power in watts
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"PC010;");
          } else {
            // process
          }
          break;
        case 'S': // Power Status
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"PS0;");
          } else {
            // process
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'R':
      switch(catCommand[1]) {
        case 'X': // Receiver Function (0: Main, 1: Sub)
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"RX0;");
            //catTX=false;
            my_ptt=HIGH;
          } else {
            // process
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'S':
      switch(catCommand[1]) {
        case 'A':
          if(catCommand[2]==';') {
            sprintf(outputBuffer,"SA0000000;");
          } else {
            // process
          }
          break;
        case 'M':
          if(catCommand[3]==';') {
            int i=atoi(&catCommand[2]);
            int s=((int)dbm + 127)/3;
            if(s<0) s=0;
            if(s>30) s=0;
            sprintf(outputBuffer,"SM%d%04d;",i,s);
          } else {
            // process
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    case 'T':
      switch(catCommand[1]) {
        case 'X':
          if(catCommand[2]==';') {            
            // should not happen
            sprintf(outputBuffer,"TX;");
            my_ptt=LOW;
          } else if(catCommand[3]==';') {
            int i=atol(&catCommand[2]);
            switch(i) {
              case 0: // TX On Main
              case 1: // TX On Sub
                sprintf(outputBuffer,"TX%d;",i);
                my_ptt=LOW;
                break;
              
            }
          }
          break;
        default:
          sprintf(outputBuffer,"?;");
          break;
      }
      break;
    default:
      sprintf(outputBuffer,"?;");
      break;      
  }

  if(outputBuffer[0]=='\0') {
    sprintf(outputBuffer,"?;");
  }
  int i=0;
  while(outputBuffer[i]!='\0') {
    if(Serial.availableForWrite()>0) {
#if defined(DEBUG_CAT) && defined(G0ORX_FRONTPANEL)
      FrontPanelSetLed(1, 0);
#endif
      Serial.print(outputBuffer[i]);
      i++;
    } else {
#if defined(DEBUG_CAT) && defined(G0ORX_FRONTPANEL)
      FrontPanelSetLed(1, 1);
#endif
      Serial.send_now();
    }
  }
  Serial.send_now();
  
#if defined(DEBUG_CAT) && defined(G0ORX_FRONTPANEL)
  FrontPanelSetLed(0, 0);
#endif
}

void CATSerialEvent() {
  char c;
  while(Serial.available()) {
    c=(char)Serial.read();
    catCommand[catCommandIndex]=c;
#ifdef DEBUG_CAT
    MorseCharacterDisplay(catCommand[catCommandIndex]); // DEBUG output to bottom line of display
#endif
    if(catCommand[catCommandIndex]==';') {
      processCATCommand();
      catCommandIndex=0;
      break;
    } else {
      catCommandIndex++;
      if(catCommandIndex>=128) catCommandIndex=0;
    }
  }
}
#endif