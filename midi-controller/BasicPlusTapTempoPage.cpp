#include "BasePage.h"
#include "globals.h"
#include <MIDI.h>
#include "Arduino.h"

    const int BasicPlusTapTempoPage::midiCc1 = 100;
    const int BasicPlusTapTempoPage::midiCc2 = 101;
    const int BasicPlusTapTempoPage::midiCc3 = 102;
    const int BasicPlusTapTempoPage::midiCcTapTempo = 64; // Tap/Tempo when high value passed

    BasicPlusTapTempoPage::BasicPlusTapTempoPage(){
      lastTapTime = 0;
      tempo = 1000; // this is in miliseconds
      lastBlinkTime = 0;      
    }

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
      updateLedStrip();

      static boolean blink = false;
      if(millis() - lastTapTime < lowestTempo)
      {
        blink = !blink;
        digitalWrite(LED_PIN, blink); //that's only for debugging

        tempo = millis() - lastTapTime;
        lastBlinkTime = millis();
        loop();
      }

      lastTapTime = millis();
    }

    void BasicPlusTapTempoPage::setup() { //setup when page is changed to this
      switchTempoLeds(LOW);
      updateLedStrip();
    }

    void BasicPlusTapTempoPage::loop()
    {
      int elapsedTime = millis() - lastBlinkTime;
      switchTempoLeds(elapsedTime < (tempo/2) ? HIGH : LOW);
        
      if(elapsedTime >= tempo)
        lastBlinkTime = millis();
    }

    void BasicPlusTapTempoPage::switchTempoLeds(int state){
      colors[0] = hsvToRgb(0, basicSat, state == LOW ? 0 : ledBright);
      colors[1] = hsvToRgb(0, basicSat, state == LOW ? 0 : ledBright);      
      ledStrip.write(colors, LED_COUNT);  
    }
        
    void BasicPlusTapTempoPage::updateLedStrip()
    {
        //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
        // colors[0] = hsvToRgb(basicPlusTapTempoPageHue, basicSat, button4State == LOW ? ledDim : ledBright);
        // colors[1] = hsvToRgb(basicPlusTapTempoPageHue, basicSat, button4State == LOW ? ledDim : ledBright);
        colors[2] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[3] = hsvToRgb(basicPageHue, basicSat, button3State == LOW ? ledDim : ledBright);
        colors[4] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[5] = hsvToRgb(basicPageHue, basicSat, button2State == LOW ? ledDim : ledBright);
        colors[6] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);
        colors[7] = hsvToRgb(basicPageHue, basicSat, button1State == LOW ? ledDim : ledBright);

        ledStrip.write(colors, LED_COUNT);  
    }   
