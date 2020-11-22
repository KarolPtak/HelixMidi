#include <ezButton.h>
#include <PololuLedStrip.h>
#include <MIDI.h>


//BUTTONS
/// constants won't change
const int BUTTON_PIN = 2; // the number of the pushbutton pin
const int LED_PIN    = 13; // the number of the LED pin

ezButton button(BUTTON_PIN);  // create ezButton object that attach to pin 7;

// variables will change:
int ledState = LOW;   // the current state of LED



//LEDSTRIP
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 8
rgb_color colors[LED_COUNT];


//MIDI
MIDI_CREATE_DEFAULT_INSTANCE();


void setup() {
//   Serial.begin(9600);         // initialize serial
  pinMode(LED_PIN, OUTPUT);   // set arduino pin to output mode
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  MIDI.begin(1);
}

void loop() {
  button.loop(); // MUST call the loop() function first

  if(button.isPressed()) {
    // Serial.println("The button is pressed");

    // toggle state of LED
    ledState = !ledState;

    // control LED arccoding to the toggleed sate
    digitalWrite(LED_PIN, ledState); 

	for(uint16_t i = 0; i < LED_COUNT; i++)
	{
		byte x = 180;
		if(ledState)
			x = 0;
		colors[i] = hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
	}	

	ledStrip.write(colors, LED_COUNT);

	int midiValue = ledState == LOW ? 0 : 127;
	MIDI.sendControlChange(100, midiValue, 1);
  }
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


