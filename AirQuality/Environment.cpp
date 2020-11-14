#include "Environment.h"
#include "Debug.h"

Environment::Environment() :
  alarm(ALARM_MIN_LEVEL, ALARM_MAX_LEVEL) {
    
  lastLoopStepTime = 0;
  lastDisplayTime = 0;
  lastAlarmActivationLevel = 0;
  showWelcomeScreen = true;  
}


void Environment::initialize() {

  alarm.initialize();

  sensorHandler.initialize();

  lcd.initialize();

  buttonHandler.initialize();  
}



void Environment::loopIteration() {

  auto now = millis();

  Measurement pendingMeasurement;

  if (sensorHandler.measure(pendingMeasurement)) {
    processMeasurement = true;
    measurement = pendingMeasurement;
  }

  if (showWelcomeScreen) {
    if (now > lastDisplayTime + WELCOME_SCREEN_DISPLAY_TIME) {
      showWelcomeScreen = false;
    } else {
      return;
    }
  }

  // Check if the counter has overflown
  if (lastLoopStepTime > now) {
    lastLoopStepTime = now;
  }

  buttonHandler.checkStatus();

  if (now > lastLoopStepTime + LOOP_STEP_TIME) {

    bool nextDisplay;
    if (now > lastDisplayTime + DISPLAY_UPDATE_TIME) {
      nextDisplay = true;
      lastDisplayTime = now;
    } else {
      nextDisplay = false;
    }

    if (nextDisplay) {
      printDebugInfo(measurement);
    }

    if (buttonHandler.consumeLongPress()) {
      lcd.toggleAutoChange();
      nextDisplay = true;
      lastDisplayTime = now;
    } else if (buttonHandler.consumeClick()) {
      lcd.changeMode();
      nextDisplay = true;
      lastDisplayTime = now;
    }

    if (processMeasurement && measurement.checksumValid) {

      alarm.handleMeasurement(measurement);

      if (lastAlarmActivationLevel > 0 && abs(alarm.getAlarmActivationLevel() - lastAlarmActivationLevel) > ALARM_DISPLAY_THESHOLD) {
        if (alarm.active()) {
          char msg[32];
          sprintf(msg, "%d", alarm.getAlarmActivationLevel());
          lcd.displayCustom("PM2.5 alarm", msg);
          lastDisplayTime = now;
        } else {
          lcd.displayCustom("PM2.5 alarm", "Deactivated");
          lastDisplayTime = now;
        }
      } else if (nextDisplay) {
        lcd.displayMeasurement(measurement);
        lastDisplayTime = now;
      }

      lastAlarmActivationLevel = alarm.getAlarmActivationLevel();
    }

    lastLoopStepTime = now;
  }
}


void Environment::printDebugInfo(const Measurement &measurement) {

  debugPrintLine("");

  debugPrintNum("PM1.0 (cv=1)", measurement.pm1);
  debugPrintNum("PM2.5 (cv=1)", measurement.pm2_5);
  debugPrintNum("PM10  (cv=1)", measurement.pm10);

  debugPrintNum("PM1.0 (atm)", measurement.pmAtm1);
  debugPrintNum("PM2.5 (atm)", measurement.pmAtm2_5);
  debugPrintNum("PM10  (atm)", measurement.pmAtm10);

  debugPrintNum("Concentration 0.3", measurement.concentration0_3);
  debugPrintNum("Concentration 0.5", measurement.concentration0_5);
  debugPrintNum("Concentration 1  ", measurement.concentration1);
  debugPrintNum("Concentration 2.5", measurement.concentration2_5);
  debugPrintNum("Concentration 5  ", measurement.concentration5);
  debugPrintNum("Concentration 10 ", measurement.concentration10);

  debugPrintNum("Reserved", measurement.reserved);
  debugPrintNum("checksum", measurement.checksum);
  debugPrintNum("checksum valid", measurement.checksumValid);
}
