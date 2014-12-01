#ifndef REMOTE_H
#define REMOTE_H
#include "Arduino.h"

#define GO_PIN 48
#define REEL_PIN 47
#define JOG_PIN_1 49
#define JOG_PIN_2 46
#define MAIN_PIN 50

class Remote
{
protected:
  boolean start;
  boolean reel;
  boolean jog_1;
  boolean jog_2;
  boolean main;
  
  boolean startlast, reellast, jog_1last, jog_2last, mainlast;
  boolean startrawlast, reelrawlast, jog_1rawlast, jog_2rawlast, mainrawlast;
public:
  Remote();
  void init();
  void check();
  boolean getStart();
  boolean getReset();
  boolean getJog1();
  boolean getJog2();
  boolean getJogAll();
  boolean getMain();
};
#endif


