#if !defined _COMMON_H_
#define _COMMON_H_

#include <Arduino.h>

typedef unsigned short UShort;

#define LOOP_STEP_TIME (200ul)

#define DEBUG_SERIAL

enum Pin {
  LcdRs = 2,
  LcdEnable = 3,
  LcdData4 = 4,
  LcdData5 = 5,
  LcdData6 = 6,
  LcdData7 = 7,
  Buzzer = 8,
  AirSensorRx = 10,
  AirSensorTx = 11,
  Button = 13,
  SensitivityGauge = A0
};

#endif
