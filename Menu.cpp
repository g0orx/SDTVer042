#ifndef BEENHERE
#include "SDT.h"
#endif
/*
const char *topMenus[]      = {"CW Options", "Spectrum Set", "AGC",      "NR Set",   "IQ Manual",
                               "EQ Rec Set", "EQ Xmt Set",   "Mic Comp", "Calibrate Freq", "Noise Floor",
                               "RF Set",     "VFO Select",   "EEPROM",   
                              };

int (*functionPtr[])()      = {&CWOptions, &SpectrumOptions, &AGCOptions, &NROptions, &IQOptions,
                               &EqualizerRecOptions, &EqualizerXmtOptions, &MicOptions, &CalibrateFrequency, &ButtonSetNoiseFloor,
                               &RFOptions, &VFOSelect, &EEPROMOptions
                              };
*/
/*****
  Purpose: void ShowMenu()

  Parameter list:
    char *menuItem          pointers to the menu
    int where               0 is a primary menu, 1 is a secondary menu

  Return value;
    void
*****/
void ShowMenu(const char *menu[], int where)
{
  tft.setFontScale( (enum RA8875tsize) 1);  

  if (menuStatus == NO_MENUS_ACTIVE)                                        // No menu selected??
     NoActiveMenu();
     
  if (where == PRIMARY_MENU) {                                              // Should print on left edge of top line
    tft.fillRect(PRIMARY_MENU_X, MENUS_Y, 300, CHAR_HEIGHT, RA8875_BLUE);   // Top-left of display
    tft.setCursor(5, 0);
    tft.setTextColor(RA8875_WHITE);
    tft.print(*menu);                                                       // Primary Menu
  } else {
    tft.fillRect(SECONDARY_MENU_X, MENUS_Y, 300, CHAR_HEIGHT, RA8875_GREEN);// Right of primary display
    tft.setCursor(35, 0);
    tft.setTextColor(RA8875_WHITE);
    tft.print(*menu);                                                       // Secondary Menu
  }
  return;
}
