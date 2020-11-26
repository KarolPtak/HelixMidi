#include <ezButton.h>
#include <PololuLedStrip.h>
#include <MIDI.h>
#include "BasePage.h"
#include "globals.h"


//BUTTONS
ezButton button1(2);  // create ezButton object that attach to pin;
ezButton button2(3);  
ezButton button3(4);  
ezButton button4(5);  

int button1State = LOW;   // the current state of stomp button
int button2State = LOW;   
int button3State = LOW;   
int button4State = LOW;   

unsigned long button1Time = 0;
unsigned long button2Time = 0;
unsigned long button3Time = 0;
unsigned long button4Time = 0;

//MIDI
MIDI_CREATE_DEFAULT_INSTANCE();


//LEDSTRIP
PololuLedStrip<12> ledStrip; // Create an ledStrip object and specify the pin it will use.
rgb_color colors[LED_COUNT]; //buffer for holding the colors (3 bytes per color).

int ledHue = basicPageHue;
int ledSat = basicSat;


//OTHER
unsigned long time = 0;


//PAGES
BasicPage _basicPage;
BasicPlusTapTempoPage _basicPlusTapTempoPage;
LooperPage _looperPage;
PatchChangePage _patchChangePage;

BasePage *_page = &_basicPage;

void setup() {
  pinMode(LED_PIN, OUTPUT);   // set arduino pin to output mode

  button1.setDebounceTime(debounceTime);
  button2.setDebounceTime(debounceTime); 
  button3.setDebounceTime(debounceTime); 
  button4.setDebounceTime(debounceTime); 
  
  MIDI.begin(midiChannel);
  UpdateLedStrip();
}

void loop() 
{
  button1.loop(); // MUST call the loop() function first
  button2.loop(); 
  button3.loop(); 
  button4.loop(); 
  _page->loop();


  if(button1.isPressed())
    button1Time = millis();
  if(button2.isPressed())
    button2Time = millis();
  if(button3.isPressed())
    button3Time = millis();
  if(button4.isPressed())
    button4Time = millis();

  if(button1.isReleased())
    button1Time = 0;
  if(button2.isReleased())
    button2Time = 0;
  if(button3.isReleased())
    button3Time = 0;
  if(button4.isReleased())
    button4Time = 0;


  if(button1Time && button2Time)
  {
    time = millis();
    boolean exited = false;
    while(millis() - time < twoButtonTimeout && !exited) //we can stop waiting sooner if buttons are released
      exited = button1.getStateRaw() == HIGH || button2.getStateRaw() == HIGH;

    if(!exited) //if before twoButtonTimeout any of buttons is depressed, do not trigger two button action
    {
      //these 2 buttons switch enter to basicPlusTapTempoPage and patchChangePage pages
      switch(_page->id()){
        case BASICPLUSTAPTEMPOPAGE:
          _page = &_patchChangePage;
          break;
        case PATCHCHANGEPAGE:
          _page = &_basicPage;
          break;
        default:
          _page = &_basicPlusTapTempoPage; //if current page is basic or not from this subset, then go to first page from this subset
          break;
      }

      UpdateLedStrip();
    }

    clearTimes(); //we 'consumed' current buttons hits
  }

  if(button3Time && button4Time)
  {
    time = millis();
    boolean exited = false;
    while(millis() - time < twoButtonTimeout && !exited) //we can stop waiting faster if buttons are released
      exited = button3.getStateRaw() == HIGH || button4.getStateRaw() == HIGH;

    if(!exited) //if before twoButtonTimeout any of buttons is depressed, do not trigger two button action
    {
      switch (_page->id())
      {
        case LOOPERPAGE:
          _page = &_basicPage;
          break;
        default:
          _page = &_looperPage;
          break;
      }

      UpdateLedStrip();
    }

    clearTimes();    
  }  

  if(millis() - button1Time > singleButtonTimeout && button1Time && !button2Time && !button3Time && !button4Time) // if only first button is pressed, and is pressed for at least singleButtonTimeout miliseconds
  {
    button1State = !button1State; // toggle button's state
    _page->button1Action(button1State);
    UpdateLedStrip();
    clearTimes();
  }

  if(millis() - button2Time > singleButtonTimeout && !button1Time && button2Time && !button3Time && !button4Time) 
  {
    button2State = !button2State; // toggle button's state
    _page->button2Action(button2State);
    UpdateLedStrip();
    clearTimes();
  }
  
  if(millis() - button3Time > singleButtonTimeout && !button1Time && !button2Time && button3Time && !button4Time) 
  {
    button3State = !button3State; // toggle button's state
    _page->button3Action(button3State);
    UpdateLedStrip();
    clearTimes();
  }

  if(millis() - button4Time > singleButtonTimeout && !button1Time && !button2Time && !button3Time && button4Time) 
  {
    button4State = !button4State; // toggle button's state
    _page->button4Action(button4State);
    UpdateLedStrip();
    clearTimes();
  }      
}

void clearTimes()
{
  button1Time = 0;
  button2Time = 0;
  button3Time = 0;
  button4Time = 0;
}




void UpdateLedStrip()
{
    ledHue = _page->getHue();
    ledSat = _page->getSat();


    //led strip is temporaliry mounted upside down, so leds go in order from right to left, so need to reverse here too
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