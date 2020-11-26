#ifndef basepage_h
#define basepage_h
#include <MIDI.h>


class BasePage {
    protected:
    int button1State = LOW;   // the current state of stomp button
    int button2State = LOW;   
    int button3State = LOW;   
    int button4State = LOW;  
    virtual void updateLedStrip();
  public:
    virtual int id() = 0;
    virtual void button1Action() = 0;
    virtual void button2Action() = 0;
    virtual void button3Action() = 0;
    virtual void button4Action() = 0;
    virtual void loop(); // Let the page do its own job, like maybe blinking the tap/tempo led?
    virtual void setup();
};

class BasicPage : public BasePage {
  protected:
    virtual void updateLedStrip(); //do all these inherited method need to be repeated here?
  public:
    virtual int id();
    virtual void button1Action();
    virtual void button2Action();
    virtual void button3Action();
    virtual void button4Action();
    virtual void setup();
};

class BasicPlusTapTempoPage : public BasePage {
  protected:
    virtual void updateLedStrip();
  public:
    virtual int id();
    virtual void button1Action();
    virtual void button2Action();
    virtual void button3Action();
    virtual void button4Action();
    virtual void setup();
};

class LooperPage : public BasePage {
  private:
    boolean active;
    boolean recording;
  protected:
    virtual void updateLedStrip();  
  public:
    virtual int id();
    virtual void button1Action();
    virtual void button2Action();
    virtual void button3Action();
    virtual void button4Action();
    virtual void setup();
    LooperPage();
};

class Looper2Page : public BasePage {
  private:
    boolean active;
    boolean recording;
  protected:
    virtual void updateLedStrip();  
  public:
    virtual int id();
    virtual void button1Action();
    virtual void button2Action();
    virtual void button3Action();
    virtual void button4Action();
    virtual void setup();
    Looper2Page();
};

class PatchChangePage : public BasePage {
  protected:
    virtual void updateLedStrip();  
  public:
    virtual int id();
    virtual void button1Action();
    virtual void button2Action();
    virtual void button3Action();
    virtual void button4Action();
    virtual void setup();
};



#endif