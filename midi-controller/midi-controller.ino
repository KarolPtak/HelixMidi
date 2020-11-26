#include <ezButton.h>
#include <PololuLedStrip.h>
#include <MIDI.h>


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

//this timeout is to wait for two buttons push before triggering single button push action
//its time will add up with debounce time however, so total time a button needs to be pushed is debounce time + single button timeout
const int singleButtonTimeout = 35; 
const int twoButtonTimeout = 1000;  //two buttons need to be pushed together for this time before action is triggered
const int debounceTime = 50; // debounce time helps eliminating false/accidental multiple button clicks


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
#define LED_COUNT 8 

PololuLedStrip<12> ledStrip; // Create an ledStrip object and specify the pin it will use.
rgb_color colors[LED_COUNT]; //buffer for holding the colors (3 bytes per color).

const int basicPageHue = 130;
const int basicPlusTapTempoPageHue = 200;
const int patchChangePageHue = 53;
const int looperPageHue = 177;
const int looperPageSat = 19;
const int basicSat = 255;


int ledHue = basicPageHue;
int ledSat = basicSat;
const int ledDim = 10;
const int ledBright = 110;


//OTHER
const int LED_PIN    = 13; // the number of the LED pin
unsigned long time = 0;

const int basicPage = 1;
const int basicPlusTapTempoPage = 2;
const int looperPage = 3;
const int patchChangePage = 4;

int page = basicPage;


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
  button2.loop(); // MUST call the loop() function first
  button3.loop(); // MUST call the loop() function first
  button4.loop(); // MUST call the loop() function first


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
    while(millis() - time < twoButtonTimeout && !exited) //we can stop waiting faster if buttons are released
      exited = button1.getStateRaw() == HIGH || button2.getStateRaw() == HIGH;

    if(!exited) //if before twoButtonTimeout any of buttons is depressed, do not trigger two button action
    {
      //these 2 buttons switch enter to basicPlusTapTempoPage and patchChangePage pages
      switch(page){
        case basicPlusTapTempoPage:
          page = patchChangePage;
          break;
        case patchChangePage:
          page = basicPage;
          break;
        default:
          page = basicPlusTapTempoPage; //if current page is basic or not from this subset, then go to first page from this subset
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
      switch (page)
      {
        case looperPage:
          page = basicPage;
          break;
        default:
          page = looperPage;
          break;
      }

      UpdateLedStrip();
    }

    clearTimes();    
  }  

  if(millis() - button1Time > singleButtonTimeout && button1Time && !button2Time && !button3Time && !button4Time) // if only first button is pressed, and is pressed for at least singleButtonTimeout miliseconds
  {
    button1State = !button1State; // toggle button's state
    digitalWrite(LED_PIN, button1State); //that's only for debugging
    MIDI.sendControlChange(midiCc1, button1State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
    clearTimes();
  }

  if(millis() - button2Time > singleButtonTimeout && !button1Time && button2Time && !button3Time && !button4Time) 
  {
    button2State = !button2State; // toggle button's state
    MIDI.sendControlChange(midiCc2, button2State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
    clearTimes();
  }
  
  if(millis() - button3Time > singleButtonTimeout && !button1Time && !button2Time && button3Time && !button4Time) 
  {
    button3State = !button3State; // toggle button's state
    MIDI.sendControlChange(midiCc3, button3State == LOW ? midiLowValue : midiHighValue, midiChannel);
    UpdateLedStrip();
    clearTimes();
  }

  if(millis() - button4Time > singleButtonTimeout && !button1Time && !button2Time && !button3Time && button4Time) 
  {
    button4State = !button4State; // toggle button's state
    MIDI.sendControlChange(midiCc4, button4State == LOW ? midiLowValue : midiHighValue, midiChannel);
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
    switch (page)
    {
      case basicPage:
        ledHue = basicPageHue;
        ledSat = basicSat;
        break;
      case basicPlusTapTempoPage:
        ledHue = basicPlusTapTempoPageHue;
        ledSat = basicSat;
        break;
      case looperPage:
        ledHue = looperPageHue;
        ledSat = looperPageSat;
        break;
      case patchChangePage:
        ledHue = patchChangePageHue;
        ledSat = basicSat;
        break;
    
      default:
        break;
    }


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
