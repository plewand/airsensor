#include "Alarm.h"


Alarm::Alarm(int alarmPmLevelMin, int alarmPmLevelMax) {

  activationPmLevelMin = alarmPmLevelMin;
  activationPmLevelMax = alarmPmLevelMax;

  lastUpdateTime = 0;

  for (auto level : latestPmLevels) {
    level = 0;
  }

  latestPmLevelsIndex = 0;

  alarmEnabled = false;
}


void Alarm::initialize() {

  pinMode(Pin::SensitivityGauge, INPUT);

  pinMode(Pin::Buzzer, OUTPUT);
  digitalWrite(Pin::Buzzer, HIGH);
}


void Alarm::handleMeasurement(const Measurement &measurement) {

  auto now = millis();

  // Check if the counter has overflown
  if (lastUpdateTime > now) {
    lastUpdateTime = now;
  }

  if (millis() < lastUpdateTime + MEASUREMENT_UPDATE_PERIOD) {
    return;
  }

  lastUpdateTime = now;

  int potentiomenterValue = analogRead(Pin::SensitivityGauge);

  alarmActivationLevel = normalizeSensititvity(potentiomenterValue);

  latestPmLevels[latestPmLevelsIndex] = measurement.pmAtm2_5;
  latestPmLevelsIndex = (latestPmLevelsIndex + 1) % MEASUREMENT_NUM;

  checkAlarmState();

  debugPrintArray("Alarm PM2.5 levels: ", MEASUREMENT_NUM, latestPmLevels);

  if (alarmEnabled && active())  {
    digitalWrite(Pin::Buzzer, LOW);
  } else {
    digitalWrite(Pin::Buzzer, HIGH);
  }
}


int Alarm::normalizeSensititvity(int raw) {
  
  return activationPmLevelMin + (activationPmLevelMax - activationPmLevelMin) * raw / MAX_RAW_SENSITITY;
}


int Alarm::getAlarmActivationLevel() const {
  
  return alarmActivationLevel;
}


bool Alarm::active() const {
  
  return alarmActivationLevel < activationPmLevelMax - DEACTIVATION_MARGIN;
}


void Alarm::checkAlarmState() {

  pinMode(Pin::SensitivityGauge, INPUT);

  pinMode(Pin::Buzzer, OUTPUT);
  digitalWrite(Pin::Buzzer, HIGH);

  int pmLevelsAboveThreshold = 0;

  for (auto pmLevel : latestPmLevels) {
    if (pmLevel > alarmActivationLevel) {
      pmLevelsAboveThreshold++;
    }
  }

  if (!alarmEnabled && pmLevelsAboveThreshold >= ALARM_ON_THRESHOLD) {
    alarmEnabled = true;
  } else if (alarmEnabled && pmLevelsAboveThreshold <= ALARM_OFF_THRESHOLD) {
    alarmEnabled = false;
  }
}
