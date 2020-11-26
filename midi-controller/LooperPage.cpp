#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>

    LooperPage::LooperPage(){
      active = false;
      recording = false;
    }

    int LooperPage::id() {
      return LOOPERPAGE;
    }
    void LooperPage::button1Action() {
      digitalWrite(LED_PIN, active); //that's only for debugging

      if(active) {
        if(recording){
          recording = false;
          MIDI.sendControlChange(midiCcLooperPlayStop, midiHighValue, midiChannel); //Send play signal, stop recording
        }
        else{
          active = false;
          MIDI.sendControlChange(midiCcLooperPlayStop, midiLowValue, midiChannel); //Send stop signal, stop recording
        }
      }
      else {
        active = true;
        MIDI.sendControlChange(midiCcLooperPlayStop, midiHighValue, midiChannel); //Send play signal, if there is something recorded previously - that's a bit unknown, only stomp knows the truth
      }

      updateLedStrip(); 
    }
    void LooperPage::button2Action(boolean longPress) {
      if(longPress){
        tunerAction();
        return;
      }
      
      //undo/redo has a bit more complex behaviour, so it may cause the state of active/recording, and the state of looper in the stomp to be not in sync
      MIDI.sendControlChange(midiCcLooperUndo, midiHighValue, midiChannel);
    }
    void LooperPage::button3Action() {

      if(active == false){
        active = true;
        recording = true;
        MIDI.sendControlChange(midiCcLooperRecordOverdub, midiHighValue, midiChannel); //Send record signal, turn on looper and start recording
      }
      else {
        recording = true;
        MIDI.sendControlChange(midiCcLooperRecordOverdub, midiLowValue, midiChannel); //Send overdub signal, start overdubbing
      }

      updateLedStrip();
    }
    void LooperPage::button4Action() {
      MIDI.sendControlChange(midiCcTapTempo, midiHighValue, midiChannel);
    }
    void LooperPage::setup() { //setup when page is changed to this
      updateLedStrip();
    }
        
    void LooperPage::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim);
        colors[1] = hsvToRgb(tapTempoHue, tapTempoSat, ledDim); 
        colors[2] = hsvToRgb(looperRecordHue, looperRecordSat, recording == false ? ledDim : ledBright);
        colors[3] = hsvToRgb(looperRecordHue, looperRecordSat, recording == false ? ledDim : ledBright);
        colors[4] = hsvToRgb(looperPageHue, looperPageSat, ledDim);
        colors[5] = hsvToRgb(looperPageHue, looperPageSat, ledDim);
        colors[6] = hsvToRgb(looperPageHue, looperPageSat, active == false ? ledDim : ledBright);
        colors[7] = hsvToRgb(looperPageHue, looperPageSat, active == false ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }   
