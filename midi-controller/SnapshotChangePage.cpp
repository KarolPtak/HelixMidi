#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>
#include "Arduino.h"


    SnapshotChangePage::SnapshotChangePage() {
      currentSnapshot = 0;
    }
    int SnapshotChangePage::id() {
      return SNAPSHOTCHANGEPAGE;
    }
    void SnapshotChangePage::button1Action() {
      currentSnapshot = 1;
      MIDI.sendControlChange(midiCcSnapshotSelect, midiSnapshot1Value, midiChannel);      
      updateLedStrip();
    }
    void SnapshotChangePage::button2Action(boolean longPress) {
      if(longPress) {
        tunerAction();
        return;
      }
      
      currentSnapshot = 2;
      MIDI.sendControlChange(midiCcSnapshotSelect, midiSnapshot2Value, midiChannel);
      updateLedStrip();
    }
    void SnapshotChangePage::button3Action() {
      currentSnapshot = 3;
      MIDI.sendControlChange(midiCcSnapshotSelect, midiSnapshot3Value, midiChannel);
      updateLedStrip();
    }
    void SnapshotChangePage::button4Action() {
      MIDI.sendControlChange(midiCcTapTempo, midiHighValue, midiChannel);
    }

    void SnapshotChangePage::setup() { //setup when page is changed to this
      updateLedStrip();
    }

    void SnapshotChangePage::updateLedStrip() {
        colors[0] = hsvToRgb(snapshotChangePageHue, basicSat, currentSnapshot == 1 ? ledBright : ledDim);
        colors[1] = hsvToRgb(snapshotChangePageHue, basicSat, currentSnapshot == 1 ? ledBright : ledDim);
        colors[2] = hsvToRgb(tunerHue,              tunerSat, currentSnapshot == 2 ? ledBright : ledDim);
        colors[3] = hsvToRgb(snapshotChangePageHue, basicSat, currentSnapshot == 2 ? ledBright : ledDim);
        colors[4] = hsvToRgb(snapshotChangePageHue, basicSat, currentSnapshot == 3 ? ledBright : ledDim);
        colors[5] = hsvToRgb(snapshotChangePageHue, basicSat, currentSnapshot == 3 ? ledBright : ledDim);
        colors[6] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);
        colors[7] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);

        ledStrip.write(colors, LED_COUNT);  
    }   
