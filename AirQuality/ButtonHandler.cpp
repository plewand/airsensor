#include "ButtonHandler.h"
#include "Debug.h"

ButtonHandler::ButtonHandler() {
  
  pressTime = 0;
  releaseTime = 0;
  pressed = false;
  
  clearEvents();
}


void ButtonHandler::initialize() {
  
  pinMode(Pin::Button, INPUT); 
}


void ButtonHandler::checkStatus() {
  
  int buttonState = digitalRead(Pin::Button);

  if (buttonState == HIGH) {
    if (!pressed) {
      debugPrintLine("Button pressed");
      pressTime = millis();
      pressed = true;
      clearEvents();
    }
  } else if (buttonState == LOW) {
    if (pressed) {
      debugPrintLine("Button released");
      pressed = false;

      releaseTime = millis();

      if (releaseTime < pressTime + CLICK_MAX_TIME) {        
        clicked = true;
      } else if (releaseTime > pressTime + LONG_PRESS_MIN_TIME) {        
        longPressed = true;
      }
    }
  }

  if ((longPressed || clicked) && millis() > releaseTime + EVENT_ACTIVITY_MAX_TIME) {
    clearEvents();
    pressed = false;
  }
}


bool ButtonHandler::consumeClick() {
  
  if (clicked) {
    debugPrintLine("Click detected");
  }

  bool ret = clicked;
  clicked = false;
  return ret;
}


bool ButtonHandler::consumeLongPress() {

  if (longPressed) {
    debugPrintLine("Long press detected");
  }

  bool ret = longPressed;
  longPressed = false;
  return ret;
}


void ButtonHandler::clearEvents() {
  
  longPressed = false;
  clicked = false;  
}
