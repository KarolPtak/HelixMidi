#include "globals.h"
#include <PololuLedStrip.h>

//MIDI
const int midiChannel = 1;
const int midiLowValue = 0;
const int midiHighValue = 127;
const int midiCc1 = 100;
const int midiCc2 = 101;
const int midiCc3 = 102;
const int midiCc4 = 103;
const int midiCcTapTempo = 64; // Tap/Tempo when high value passed
const int midiCcFs4 = 52; // Simulates Fs4 press, any value is accepted
const int midiCcFs5 = 53; // Simulates Fs5 press, any value is accepted
const int midiCcLooperRecordOverdub = 60; // Looper record (when high)/overdub (low)
const int midiCcLooperPlayStop = 61; // Looper play (when high)/stop (low)
const int midiCcLooperUndo = 63; // Looper undo (high)
const int midiCcTunerOnOff = 68; // Tuner on/off


//LEDSTRIP
PololuLedStrip<12> ledStrip; // Create an ledStrip object and specify the pin it will use.
rgb_color colors[LED_COUNT]; //buffer for holding the colors (3 bytes per color).

const int basicPageHue = 130;
const int patchChangePageHue = 53;
const int looperPageHue = 177;
const int tapTempoHue = 0;
const int tunerHue = 0;
const int looperRecordHue = 15;

const int looperRecordSat = 250;
const int tapTempoSat = 230;
const int tunerSat = 230;
const int looperPageSat = 19;
const int basicSat = 255;

const int ledDim = 10;
const int ledBright = 110;

const int lowestTempo = 2000; //in miliseconds

//BUTTONS
//this timeout is to wait for two buttons push before triggering single button push action
//its time will add up with debounce time however, so total time a button needs to be pushed is debounce time + single button timeout
const int singleButtonTimeout = 35; 
const int twoButtonTimeout = 1000;  //two buttons need to be pushed together for this time before action is triggered
const int debounceTime = 50; // debounce time helps eliminating false/accidental multiple button clicks


//OTHER
const int LED_PIN    = 13; // the number of the LED pin
const int eepromOffset = 10; //some random offset ;) to make sure the values are correct
const int eepromAddress = 123; //some random address ;)


// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is the saturation, as a number between 0 and 255.
// v is the value, as a number between 0 and 255.
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return rgb_color(r, g, b);
}