#include <MIDI.h>
#include <PololuLedStrip.h>
#ifndef globals_h
#define globals_h



//MIDI
extern MIDI_NAMESPACE::SerialMIDI<HardwareSerial> serialMIDI;
extern MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>> MIDI; // Define the MIDI interface

extern const int midiChannel;
extern const int midiLowValue;
extern const int midiHighValue;
extern const int midiCc1;
extern const int midiCc2;
extern const int midiCc3;
extern const int midiCc4;
extern const int midiCcTapTempo; // Tap/Tempo when high value passed
extern const int midiCcFs4;
extern const int midiCcFs5;
extern const int midiCcLooperRecordOverdub;
extern const int midiCcLooperPlayStop;
extern const int midiCcLooperUndo;
extern const int midiCcTunerOnOff; // Tuner on/off

//LEDSTRIP
#define LED_COUNT 8 

extern PololuLedStrip<12> ledStrip; // Create an ledStrip object and specify the pin it will use.
extern rgb_color colors[LED_COUNT]; //buffer for holding the colors (3 bytes per color).

extern const int basicPageHue;
extern const int patchChangePageHue;
extern const int looperPageHue;
extern const int tapTempoHue;
extern const int tunerHue;
extern const int looperRecordHue;

extern const int looperRecordSat;
extern const int tapTempoSat;
extern const int tunerSat;
extern const int looperPageSat;
extern const int basicSat;

extern const int ledDim;
extern const int ledBright;

extern const int lowestTempo;

//BUTTONS
//this timeout is to wait for two buttons push before triggering single button push action
//its time will add up with debounce time however, so total time a button needs to be pushed is debounce time + single button timeout
extern const int singleButtonTimeout; 
extern const int twoButtonTimeout;  //two buttons need to be pushed together for this time before action is triggered
extern const int debounceTime; // debounce time helps eliminating false/accidental multiple button clicks


//OTHER
extern const int LED_PIN; // the number of the LED pin
extern const int eepromOffset; //some random offset ;)
extern const int eepromAddress; //some random address ;)

//PAGES
#define BASICPAGE 1
#define BASICPLUSTAPTEMPOPAGE 2
#define PATCHCHANGEPAGE 3
#define LOOPERPAGE 4
#define LOOPER2PAGE 5


extern rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v);


#endif

