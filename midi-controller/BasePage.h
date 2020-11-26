#ifndef basepage_h
#define basepage_h
#include <MIDI.h>


class BasePage {
  public:
    virtual int getHue() = 0;
    virtual int getSat() = 0;
    virtual void button1Action(int buttonState) = 0;
    virtual void button2Action(int buttonState) = 0;
    virtual void button3Action(int buttonState) = 0;
    virtual void button4Action(int buttonState) = 0;
    virtual void loop(); // Let the page do its own job, like maybe blinking the tap/tempo led?
};

class BasicPage : public BasePage {
  public:
    virtual int getHue();
    virtual int getSat();
    virtual void button1Action(int buttonState);
    virtual void button2Action(int buttonState);
    virtual void button3Action(int buttonState);
    virtual void button4Action(int buttonState);
};

class BasicPlusTapTempoPage : public BasePage {
  public:
    virtual int getHue();
    virtual int getSat();
    virtual void button1Action(int buttonState);
    virtual void button2Action(int buttonState);
    virtual void button3Action(int buttonState);
    virtual void button4Action(int buttonState);
};

class LooperPage : public BasePage {
  public:
    virtual int getHue();
    virtual int getSat();
    virtual void button1Action(int buttonState);
    virtual void button2Action(int buttonState);
    virtual void button3Action(int buttonState);
    virtual void button4Action(int buttonState);
};

class PatchChangePage : public BasePage {
  public:
    virtual int getHue();
    virtual int getSat();
    virtual void button1Action(int buttonState);
    virtual void button2Action(int buttonState);
    virtual void button3Action(int buttonState);
    virtual void button4Action(int buttonState);
};



#endif