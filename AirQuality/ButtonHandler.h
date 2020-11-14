#if !defined _BUTTON_HANDLER_H_
#define _BUTTON_HANDLER_H_

#include "Common.h"

#define LONG_PRESS_MIN_TIME (2000ul)
#define CLICK_MAX_TIME (1500ul)
#define EVENT_ACTIVITY_MAX_TIME (500ul)

class ButtonHandler {
  public:
    ButtonHandler();
    
    void initialize();
    
    void checkStatus();
    
    bool consumeClick();
    
    bool consumeLongPress();

  private:
    unsigned long pressTime;
    unsigned long releaseTime;
    bool pressed;
    bool clicked;
    bool longPressed;

    void clearEvents();
};

#endif
