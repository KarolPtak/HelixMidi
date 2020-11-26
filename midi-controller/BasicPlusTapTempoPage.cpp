#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>
#include "Arduino.h"


    int BasicPlusTapTempoPage::id() {
      return BASICPLUSTAPTEMPOPAGE;
    }
    int BasicPlusTapTempoPage::getHue() {
      return basicPageHue;
    }
    int BasicPlusTapTempoPage::getSat() {
      return basicSat;
    }
    void BasicPlusTapTempoPage::button1Action() {
      button1State = !button1State;
      digitalWrite(LED_PIN, button1State); //that's only for debugging
      MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);      
      updateLedStrip();
    }
    void BasicPlusTapTempoPage::button2Action() {
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

    void BasicPlusTapTempoPage::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(0, basicSat, ledDim);
        colors[1] = hsvToRgb(0, basicSat, ledDim);
        colors[2] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[3] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[4] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);
        colors[7] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }   
