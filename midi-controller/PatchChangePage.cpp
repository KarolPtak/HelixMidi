#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>

    const int PatchChangePage::midiCc1 = 100;
    const int PatchChangePage::midiCc2 = 101;
    const int PatchChangePage::midiCc3 = 102;
    const int PatchChangePage::midiCc4 = 103;

    int PatchChangePage::id() {
      return PATCHCHANGEPAGE;
    }
    int PatchChangePage::getHue() {
      return patchChangePageHue;
    }
    int PatchChangePage::getSat() {
      return basicSat;
    }
    void PatchChangePage::button1Action() {
      button1State = !button1State;
      digitalWrite(LED_PIN, button1State); //that's only for debugging
      MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);  
      updateLedStrip();    
    }
    void PatchChangePage::button2Action() {
      button2State = !button2State;
      MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void PatchChangePage::button3Action() {
      button3State = !button3State;
      MIDI.sendControlChange(midiCc3, button3State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void PatchChangePage::button4Action() {
      button4State = !button4State;
      MIDI.sendControlChange(midiCc4, button4State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void PatchChangePage::setup() { //setup when page is changed to this
      updateLedStrip();
    }
        
    void PatchChangePage::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(patchChangePageHue, basicSat, button4State == LOW ? ledDim : ledBright);
        colors[1] = hsvToRgb(patchChangePageHue, basicSat, button4State == LOW ? ledDim : ledBright);
        colors[2] = hsvToRgb(patchChangePageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[3] = hsvToRgb(patchChangePageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[4] = hsvToRgb(patchChangePageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(patchChangePageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(patchChangePageHue, basicSat, button1State == LOW ? ledDim : ledBright);
        colors[7] = hsvToRgb(patchChangePageHue, basicSat, button1State == LOW ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }   
