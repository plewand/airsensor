#if !defined _LCD_H_
#define _LCD_H_

#include "Common.h"
#include <LiquidCrystal.h>
#include "Measurement.h"


enum Mode {
  Pm,
  PmAtm,
  ConcentrationNano,
  ConcentrationMicroLow,
  ConcentrationMicroHight,
};


class Lcd {

  public:

    Lcd();

    void initialize();

    void displayCustom(const char *title, const char *message);

    void displayMeasurement(const Measurement &measurement);

    void toggleAutoChange();

    void changeMode();

  private:

    LiquidCrystal lcd;
    Mode mode;
    char msg[32];
    bool autoChange;

    void displayPm(const Measurement &measurement);

    void displayPmAtm(const Measurement &measurement);

    void displayConcentrationNano(const Measurement &measurement);

    void displayConcentrationMicroLow(const Measurement &measurement);

    void displayConcentrationMicroHigh(const Measurement &measurement);

    void printMessage(const Measurement &measurement, String label,
                      void (*fillMessageBuffer)(const Measurement &, char*));

    Mode getNextMode() const;
};

#endif
