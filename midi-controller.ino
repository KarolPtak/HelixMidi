#include <ezButton.h>
#include <PololuLedStrip.h>
#include <MIDI.h>


//BUTTONS
/// constants won't change
const int LED_PIN    = 13; // the number of the LED pin

ezButton button1(2);  // create ezButton object that attach to pin;
ezButton button2(3);  // create ezButton object that attach to pin;
ezButton button3(4);  // create ezButton object that attach to pin;
ezButton button4(5);  // create ezButton object that attach to pin;

// variables will change:
int button1State = LOW;   // the current state of stomp button
int button2State = LOW;   // the current state of stomp button
int button3State = LOW;   // the current state of stomp button
int button4State = LOW;   // the current state of stomp button


//MIDI
MIDI_CREATE_DEFAULT_INSTANCE();
const int midiChannel = 1;
const int midiCc1 = 100;
const int midiCc2 = 101;
const int midiCc3 = 102;
const int midiCc4 = 103;

const int midiLowValue = 0;
const int midiHighValue = 127;


//LEDSTRIP
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

#define LED_COUNT 8 
rgb_color colors[LED_COUNT]; //buffer for holding the colors (3 bytes per color).
const int ledHue = 130;
const int ledSat = 255;
const int ledDim = 10;
const int ledBright = 110;



void setup() {
  pinMode(LED_PIN, OUTPUT);   // set arduino pin to output mode

  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50); // set debounce time to 50 milliseconds
  button3.setDebounceTime(50); // set debounce time to 50 milliseconds
  button4.setDebounceTime(50); // set debounce time to 50 milliseconds
  
  MIDI.begin(midiChannel);
  UpdateLedStrip();
}

void loop() 
{
  button1.loop(); // MUST call the loop() function first
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first
  button4.loop(); // MUST call the loop() function first

  if(button1.isPressed()) 
  {
    button1State = !button1State; // toggle state of LED
    digitalWrite(LED_PIN, button1State); //that's only for debugging
    MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
  }

  if(button2.isPressed()) 
  {
    button2State = !button2State; // toggle state of LED
    MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
  }
  
  if(button3.isPressed()) 
  {
    button3State = !button3State; // toggle state of LED
    MIDI.sendControlChange(midiCc3, button3State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
  }

  if(button4.isPressed()) 
  {
    button4State = !button4State; // toggle state of LED
    MIDI.sendControlChange(midiCc4, button4State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
  }      
}




void UpdateLedStrip()
{
    //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse order here too
    colors[0] = hsvToRgb(ledHue, ledSat, button4State == LOW ? ledDim : ledBright);
    colors[1] = hsvToRgb(ledHue, ledSat, button4State == LOW ? ledDim : ledBright);
    colors[2] = hsvToRgb(ledHue, ledSat, button3State == LOW ? ledDim : ledBright);
    colors[3] = hsvToRgb(ledHue, ledSat, button3State == LOW ? ledDim : ledBright);
    colors[4] = hsvToRgb(ledHue, ledSat, button2State == LOW ? ledDim : ledBright);
    colors[5] = hsvToRgb(ledHue, ledSat, button2State == LOW ? ledDim : ledBright);
    colors[6] = hsvToRgb(ledHue, ledSat, button1State == LOW ? ledDim : ledBright);
    colors[7] = hsvToRgb(ledHue, ledSat, button1State == LOW ? ledDim : ledBright);

    ledStrip.write(colors, LED_COUNT);  
}

// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is the saturation, as a number between 0 and 255.
// v is the value, as a number between 0 and 255.
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
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
