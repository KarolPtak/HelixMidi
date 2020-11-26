#include <MIDI.h>
#ifndef globals_h
#define globals_h



//MIDI
extern MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialMIDI;
extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI; // Define the MIDI interface

extern const int midiChannel;
extern const int midiCc1;
extern const int midiCc2;
extern const int midiCc3;
extern const int midiCc4;

extern const int midiLowValue;
extern const int midiHighValue;

//LEDSTRIP
#define LED_COUNT 8 

extern const int basicPageHue;
extern const int basicPlusTapTempoPageHue;
extern const int patchChangePageHue;
extern const int looperPageHue;

extern const int looperPageSat;
extern const int basicSat;

extern const int ledDim;
extern const int ledBright;


//BUTTONS
//this timeout is to wait for two buttons push before triggering single button push action
//its time will add up with debounce time however, so total time a button needs to be pushed is debounce time + single button timeout
extern const int singleButtonTimeout; 
extern const int twoButtonTimeout;  //two buttons need to be pushed together for this time before action is triggered
extern const int debounceTime; // debounce time helps eliminating false/accidental multiple button clicks


//OTHER
extern const int LED_PIN; // the number of the LED pin

// //PAGES
#define BASICPAGE 1
#define BASICPLUSTAPTEMPOPAGE 2
#define LOOPERPAGE 3
#define PATCHCHANGEPAGE 4

#endif

