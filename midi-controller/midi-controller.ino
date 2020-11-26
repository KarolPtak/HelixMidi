#include <ezButton.h>
#include <PololuLedStrip.h>
#include <MIDI.h>
#include "BasePage.h"
#include "globals.h"
#include "PagePersister.h"


//BUTTONS
ezButton button1(2);  // create ezButton object that attach to pin;
ezButton button2(3);  
ezButton button3(4);  
ezButton button4(5);  

unsigned long button1Time = 0;
unsigned long button2Time = 0;
unsigned long button3Time = 0;
unsigned long button4Time = 0;

//MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

//OTHER
unsigned long time = 0;


//PAGES
BasicPage _basicPage;
BasicPlusTapTempoPage _basicPlusTapTempoPage;
PatchChangePage _patchChangePage;
SnapshotChangePage _snapshotChangePage;
LooperPage _looperPage;
Looper2Page _looper2Page;

BasePage *_page;

PagePersister pagePersister;

void setup() {
  pinMode(LED_PIN, OUTPUT);   // set arduino pin to output mode

  button1.setDebounceTime(debounceTime);
  button2.setDebounceTime(debounceTime); 
  button3.setDebounceTime(debounceTime); 
  button4.setDebounceTime(debounceTime); 
  
  MIDI.begin(midiChannel);
  pagePersister.init();
  _page = getPage(pagePersister.get());

  _page->setup();
}

void loop() {
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


  if(button1Time && button2Time) {
    time = millis();
    boolean exited = false;
    while(millis() - time < twoButtonTimeout && !exited) //we can stop waiting sooner if buttons are released
      exited = button1.getStateRaw() == HIGH || button2.getStateRaw() == HIGH;

    if(!exited) { //if before twoButtonTimeout any of buttons is depressed, do not trigger two button action
      //these 2 buttons switch enter to basicPlusTapTempoPage and patchChangePage pages
      switch(_page->id()){
        case BASICPLUSTAPTEMPOPAGE:
          _page = &_patchChangePage;
          break;
        case PATCHCHANGEPAGE:
          _page = &_snapshotChangePage;
          break;
        case SNAPSHOTCHANGEPAGE:
          _page = &_basicPage;
          break;
        default:
          _page = &_basicPlusTapTempoPage; //if current page is basic or not from this subset, then go to first page from this subset
          break;
      }

      pagePersister.update(_page->id());
      _page->setup();
    }

    clearTimes(); //we 'consumed' current buttons hits
  }

  if(button3Time && button4Time) {
    time = millis();
    boolean exited = false; //will such a local variable cause memory allocation and memory leak in over a time? I'm asking, 'cause I'm a C# programmer on daily basis ;).
    while(millis() - time < twoButtonTimeout && !exited) //we can stop waiting faster if buttons are released
      exited = button3.getStateRaw() == HIGH || button4.getStateRaw() == HIGH;

    if(!exited) { //if before twoButtonTimeout any of buttons is depressed, do not trigger two button action
      switch (_page->id()) {
        case LOOPERPAGE:
          _page = &_looper2Page;
          break;
        case LOOPER2PAGE:
          _page = &_basicPage;
          break;
        default:
          _page = &_looperPage;
          break;
      }

      pagePersister.update(_page->id());
      _page->setup();
    }

    clearTimes();    
  }  

  if(millis() - button1Time > singleButtonTimeout && button1Time && !button2Time && !button3Time && !button4Time) { // if only first button is pressed, and is pressed for at least singleButtonTimeout miliseconds
    _page->button1Action();
    clearTimes();
  }

  if(millis() - button2Time > singleButtonTimeout && !button1Time && button2Time && !button3Time && !button4Time) {
    time = millis();
    boolean exited = false; //will such a local variable cause memory allocation and memory leak in over a time? I'm asking, 'cause I'm a C# programmer on daily basis ;).
    while(millis() - time < twoButtonTimeout && !exited)
      exited = button2.getStateRaw() == HIGH;    

    _page->button2Action(!exited);
    clearTimes();
  }
  
  if(millis() - button3Time > singleButtonTimeout && !button1Time && !button2Time && button3Time && !button4Time) {
    _page->button3Action();
    clearTimes();
  }

  if(millis() - button4Time > singleButtonTimeout && !button1Time && !button2Time && !button3Time && button4Time) {
    _page->button4Action();
    clearTimes();
  }      
}

void clearTimes() {
  button1Time = 0;
  button2Time = 0;
  button3Time = 0;
  button4Time = 0;
}

BasePage* getPage(int pageId) {
  switch (pageId) {
  case BASICPAGE:
    return &_basicPage;
  case BASICPLUSTAPTEMPOPAGE:
    return &_basicPlusTapTempoPage;
  case PATCHCHANGEPAGE:
    return &_patchChangePage;
  case SNAPSHOTCHANGEPAGE:
    return &_snapshotChangePage;
  case LOOPERPAGE:
    return &_looperPage;
  case LOOPER2PAGE:
    return &_looper2Page;
  default:
    return &_basicPage;
  }
}
