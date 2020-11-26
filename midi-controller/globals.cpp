#include "globals.h"

//MIDI
const int midiChannel = 1;
const int midiCc1 = 100;
const int midiCc2 = 101;
const int midiCc3 = 102;
const int midiCc4 = 103;

const int midiLowValue = 0;
const int midiHighValue = 127;

//LEDSTRIP
const int basicPageHue = 130;
const int basicPlusTapTempoPageHue = 200;
const int patchChangePageHue = 53;
const int looperPageHue = 177;

const int looperPageSat = 19;
const int basicSat = 255;

const int ledDim = 10;
const int ledBright = 110;

//BUTTONS
//this timeout is to wait for two buttons push before triggering single button push action
//its time will add up with debounce time however, so total time a button needs to be pushed is debounce time + single button timeout
const int singleButtonTimeout = 35; 
const int twoButtonTimeout = 1000;  //two buttons need to be pushed together for this time before action is triggered
const int debounceTime = 50; // debounce time helps eliminating false/accidental multiple button clicks


//OTHER
const int LED_PIN    = 13; // the number of the LED pin

