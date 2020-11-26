#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>


    int LooperPage::id() {
      return LOOPERPAGE;
    }
    int LooperPage::getHue() {
      return looperPageHue;
    }
    int LooperPage::getSat() {
      return looperPageSat;
    }
    void LooperPage::button1Action() {
      button1State = !button1State;
      digitalWrite(LED_PIN, button1State); //that's only for debugging
      MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);     
      updateLedStrip(); 
    }
    void LooperPage::button2Action() {
      button2State = !button2State;
      MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void LooperPage::button3Action() {
      button3State = !button3State;
      MIDI.sendControlChange(midiCc3, button3State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void LooperPage::button4Action() {
      button4State = !button4State;
      MIDI.sendControlChange(midiCc4, button4State == LOW ? midiLowValue : midiHighValue, midiChannel);
      updateLedStrip();
    }
    void LooperPage::setup() { //setup when page is changed to this
      updateLedStrip();
    }
        
    void LooperPage::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(looperPageHue, looperPageSat, button4State == LOW ? ledDim : ledBright);
        colors[1] = hsvToRgb(looperPageHue, looperPageSat, button4State == LOW ? ledDim : ledBright);
        colors[2] = hsvToRgb(looperPageHue, looperPageSat, button3State == LOW ? ledDim : ledBright);
        colors[3] = hsvToRgb(looperPageHue, looperPageSat, button3State == LOW ? ledDim : ledBright);
        colors[4] = hsvToRgb(looperPageHue, looperPageSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(looperPageHue, looperPageSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(looperPageHue, looperPageSat, button1State == LOW ? ledDim : ledBright);
        colors[7] = hsvToRgb(looperPageHue, looperPageSat, button1State == LOW ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }   
