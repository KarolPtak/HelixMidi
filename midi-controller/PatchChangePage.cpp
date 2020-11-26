#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>

    int PatchChangePage::id() {
      return PATCHCHANGEPAGE;
    }
    void PatchChangePage::button1Action() {
      button1State = !button1State;
      digitalWrite(LED_PIN, button1State); //that's only for debugging
      MIDI.sendControlChange(midiCcFs4, midiHighValue, midiChannel);  
    }
    void PatchChangePage::button2Action(boolean longPress) {
      if(longPress){
        tunerAction();
        return;
      }

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
        colors[0] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);
        colors[1] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);        
        colors[2] = hsvToRgb(patchChangePageHue, basicSat, ledDim);
        colors[3] = hsvToRgb(patchChangePageHue, basicSat, ledDim ); //TODO: Turn off one, to make it more readable that this is patch change, not an ordinary footswitch
        colors[4] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(tunerHue, tunerSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(patchChangePageHue, basicSat, ledDim);
        colors[7] = hsvToRgb(patchChangePageHue, basicSat, ledDim); //TODO: Turn off one, to make it more readable that this is patch change, not an ordinary footswitch

        ledStrip.write(colors, LED_COUNT);  
    }   
