#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>

    void BasePage::loop(){} // Let the page do its own job, like maybe blinking the tap/tempo led?
    void BasePage::tunerAction() {
      MIDI.sendControlChange(midiCcTunerOnOff, midiHighValue, midiChannel);    
    }