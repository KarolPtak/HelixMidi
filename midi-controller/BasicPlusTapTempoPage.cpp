#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>
#include "Arduino.h"


    int BasicPlusTapTempoPage::id() {
      return BASICPLUSTAPTEMPOPAGE;
    }
    void BasicPlusTapTempoPage::button1Action() {
      button1State = !button1State;
      digitalWrite(LED_PIN, button1State); //that's only for debugging
      MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);      
      updateLedStrip();
    }
    void BasicPlusTapTempoPage::button2Action(boolean longPress) {
      if(longPress) {
        tunerAction();
        return;
      }
      
      button2State = !button2State;
      MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void BasicPlusTapTempoPage::button3Action() {
      button3State = !button3State;
      MIDI.sendControlChange(midiCc3, button3State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void BasicPlusTapTempoPage::button4Action() {
      MIDI.sendControlChange(midiCcTapTempo, midiHighValue, midiChannel);
    }

    void BasicPlusTapTempoPage::setup() { //setup when page is changed to this
      updateLedStrip();
    }

    void BasicPlusTapTempoPage::updateLedStrip() {
        colors[0] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);
        colors[1] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);
        colors[2] = hsvToRgb(tunerHue, tunerSat, button2State == LOW ? ledDim : ledBright);
        colors[3] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[4] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);
        colors[7] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);

        ledStrip.write(colors, LED_COUNT);  
    }   
