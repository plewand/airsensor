#if !defined _DEBUG_H_
#define _DEBUG_H_

#include "Common.h"
#include <SoftwareSerial.h>

#if defined DEBUG_SERIAL

inline void debugPrintNum(const char* label, UShort value) {
  Serial.print(label);
  Serial.print(": ");
  Serial.println(value);
}

inline void debugPrintLine(const char* tx) {
  Serial.println(tx);
}

inline void debugPrintArray(const char* label, int elemNum, int *elems) {
  Serial.print(label);
  for (int i = 0; i < elemNum; i++) {
    Serial.print(elems[i]);
    Serial.print(" ");
  }
  Serial.println();
}

#else

inline void debugPrintNum(const char* label, UShort value) {
}

inline void debugPrintLine(const char* tx) {
}

inline void debugPrintArray(const char* label, int elemNum, int *elems) {
}

#endif


#endif
