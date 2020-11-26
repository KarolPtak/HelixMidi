#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>


    void BasePage::loop(){} // Let the page do its own job, like maybe blinking the tap/tempo led?




    int BasicPage::id() {
      return BASICPAGE;
    }
    int BasicPage::getHue() {
      return basicPageHue;
    }
    int BasicPage::getSat() {
      return basicSat;
    }
    void BasicPage::button1Action(int buttonState) {
      digitalWrite(LED_PIN, buttonState); //that's only for debugging
      MIDI.sendControlChange(midiCc1, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);      
    }
    void BasicPage::button2Action(int buttonState) {
      MIDI.sendControlChange(midiCc2, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void BasicPage::button3Action(int buttonState) {
      MIDI.sendControlChange(midiCc3, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void BasicPage::button4Action(int buttonState) {
      MIDI.sendControlChange(midiCc4, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
