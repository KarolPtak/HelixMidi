#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>

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
      MIDI.sendControlChange(midiCcFs4, midiHighValue, midiChannel);  
    }
    void PatchChangePage::button2Action() {
      button2State = !button2State;
      MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void PatchChangePage::button3Action() {
      MIDI.sendControlChange(midiCcFs5, midiHighValue, midiChannel);
      updateLedStrip();
    }
    void PatchChangePage::button4Action() {
      MIDI.sendControlChange(midiCcTapTempo, midiHighValue, midiChannel);
    }
    void PatchChangePage::setup() { //setup when page is changed to this
      updateLedStrip();
    }
        
    void PatchChangePage::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(0, basicSat, ledDim);
        colors[1] = hsvToRgb(0, basicSat, ledDim);        
        colors[2] = hsvToRgb(patchChangePageHue, basicSat, ledDim);
        colors[3] = hsvToRgb(patchChangePageHue, basicSat, ledDim );
        colors[4] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(patchChangePageHue, basicSat, ledDim);
        colors[7] = hsvToRgb(patchChangePageHue, basicSat, ledDim);

        ledStrip.write(colors, LED_COUNT);  
    }   
