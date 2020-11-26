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
    void LooperPage::button1Action(int buttonState) {
      digitalWrite(LED_PIN, buttonState); //that's only for debugging
      MIDI.sendControlChange(midiCc1, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);      
    }
    void LooperPage::button2Action(int buttonState) {
      MIDI.sendControlChange(midiCc2, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void LooperPage::button3Action(int buttonState) {
      MIDI.sendControlChange(midiCc3, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void LooperPage::button4Action(int buttonState) {
      MIDI.sendControlChange(midiCc4, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
