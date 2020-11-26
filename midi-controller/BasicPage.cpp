#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>


    int BasicPage::id() {
      return BASICPAGE;
    }
    void BasicPage::button1Action() {
      button1State = !button1State;
      digitalWrite(LED_PIN, button1State); //that's only for debugging
      MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);    
      updateLedStrip();  
    }
    void BasicPage::button2Action(boolean longPress) {
      if(longPress) {
        tunerAction();
        return;
      }

      button2State = !button2State;
      MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void BasicPage::button3Action() {
      button3State = !button3State;
      MIDI.sendControlChange(midiCc3, button3State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void BasicPage::button4Action() {
      button4State = !button4State;
      MIDI.sendControlChange(midiCc4, button4State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void BasicPage::setup() { //setup when page is changed to this
      updateLedStrip();
    }
        
    void BasicPage::updateLedStrip() {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(basicPageHue, basicSat, button4State == LOW ? ledDim : ledBright);
        colors[1] = hsvToRgb(basicPageHue, basicSat, button4State == LOW ? ledDim : ledBright);
        colors[2] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[3] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[4] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(tunerHue, tunerSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);
        colors[7] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }    
