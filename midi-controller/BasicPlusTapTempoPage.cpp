#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>


    int BasicPlusTapTempoPage::getHue() {
      return basicPlusTapTempoPageHue;
    }
    int BasicPlusTapTempoPage::getSat() {
      return basicSat;
    }
    void BasicPlusTapTempoPage::button1Action(int buttonState) {
      digitalWrite(LED_PIN, buttonState); //that's only for debugging
      MIDI.sendControlChange(midiCc1, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);      
    }
    void BasicPlusTapTempoPage::button2Action(int buttonState) {
      MIDI.sendControlChange(midiCc2, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void BasicPlusTapTempoPage::button3Action(int buttonState) {
      MIDI.sendControlChange(midiCc3, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void BasicPlusTapTempoPage::button4Action(int buttonState) {
      MIDI.sendControlChange(midiCc4, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
