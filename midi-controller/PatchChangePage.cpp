#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>


    int PatchChangePage::getHue() {
      return patchChangePageHue;
    }
    int PatchChangePage::getSat() {
      return basicSat;
    }
    void PatchChangePage::button1Action(int buttonState) {
      digitalWrite(LED_PIN, buttonState); //that's only for debugging
      MIDI.sendControlChange(midiCc1, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);      
    }
    void PatchChangePage::button2Action(int buttonState) {
      MIDI.sendControlChange(midiCc2, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void PatchChangePage::button3Action(int buttonState) {
      MIDI.sendControlChange(midiCc3, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
    void PatchChangePage::button4Action(int buttonState) {
      MIDI.sendControlChange(midiCc4, buttonState == LOW ? midiLowValue : midiHighValue, midiChannel);
    }
