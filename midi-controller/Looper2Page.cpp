#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>

    Looper2Page::Looper2Page(){
      active = false;
      recording = false;
    }

    int Looper2Page::id() {
      return LOOPER2PAGE;
    }
    void Looper2Page::button1Action() {
        digitalWrite(LED_PIN, active); //that's only for debugging

        active = false;
        recording = false;
        MIDI.sendControlChange(midiCcLooperPlayStop, midiLowValue, midiChannel); //Send stop signal, stop recording
        
        updateLedStrip(); 
    }
    void Looper2Page::button2Action() {
      //undo/redo has a bit more complex behaviour, so it may cause the state of active/recording, and the state of looper in the stomp to be not in sync
      MIDI.sendControlChange(midiCcLooperUndo, midiHighValue, midiChannel); 
    }
    void Looper2Page::button3Action() {
        active = true;
        recording = false;
        MIDI.sendControlChange(midiCcLooperPlayStop, midiHighValue, midiChannel); //Send play signal, turn on looper or stop recording

        updateLedStrip();
    }
    void Looper2Page::button4Action() {
        if (!active){
            active = true;
            recording = true;
            MIDI.sendControlChange(midiCcLooperRecordOverdub, midiHighValue, midiChannel); //Send record signal, turn on looper and start recording
        }
        else{
            recording = true;
            MIDI.sendControlChange(midiCcLooperRecordOverdub, midiLowValue, midiChannel); //Send overdub signal, start overdubbing
        }
        updateLedStrip();
    }
    void Looper2Page::setup() { //setup when page is changed to this
      updateLedStrip();
    }
        
    void Looper2Page::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        colors[0] = hsvToRgb(looperRecordHue, looperRecordSat, recording == false ? ledDim : ledBright);
        colors[1] = hsvToRgb(looperRecordHue, looperRecordSat, recording == false ? ledDim : ledBright);
        colors[2] = hsvToRgb(looperPageHue, looperPageSat, active == false ? ledDim : ledBright);
        colors[3] = hsvToRgb(looperPageHue, looperPageSat, active == false ? ledDim : ledBright);
        colors[4] = hsvToRgb(looperPageHue, looperPageSat, ledDim);
        colors[5] = hsvToRgb(looperPageHue, looperPageSat, ledDim);
        colors[6] = hsvToRgb(looperPageHue, looperPageSat, active == false ? ledDim : ledBright);
        colors[7] = hsvToRgb(looperPageHue, looperPageSat, active == false ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }   
