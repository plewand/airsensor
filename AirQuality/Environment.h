#if !defined _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "Common.h"
#include "Measurement.h"
#include "SensorHandler.h"
#include "Lcd.h"
#include "Alarm.h"
#include "ButtonHandler.h"

#define DISPLAY_UPDATE_TIME (2000ul)
#define ALARM_CHECK_TIME (2000ul)
#define ALARM_DISPLAY_THESHOLD (2)
#define WELCOME_SCREEN_DISPLAY_TIME (3000ul)
#define ALARM_MIN_LEVEL (20)
#define ALARM_MAX_LEVEL (300)

class Environment {
  
  public:
  
    Environment();
    
    void initialize();
    
    void loopIteration();
  
  private:
  
    unsigned long lastLoopStepTime;
    unsigned long lastDisplayTime;
    int lastAlarmActivationLevel;
    bool showWelcomeScreen;
    bool processMeasurement;
    
    Measurement measurement;  

    Alarm alarm;
    SensorHandler sensorHandler;
    Lcd lcd;    
    ButtonHandler buttonHandler;
    
    void printDebugInfo(const Measurement &measurement);

    
};

#endif
