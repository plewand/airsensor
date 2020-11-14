#include "Lcd.h"
#include "Debug.h"

Lcd::Lcd()
  : lcd(Pin::LcdRs, Pin::LcdEnable, Pin::LcdData4, Pin::LcdData5, Pin::LcdData6, Pin::LcdData7) {

  mode = Mode::PmAtm;
  autoChange = false;
}


void Lcd::initialize() {

  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Air quality");
  lcd.setCursor(0, 1);
  lcd.print("Sensor/Alarm");
}


void Lcd::displayCustom(const char *title, const char *message) {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.print(message);
}


void Lcd::displayMeasurement(const Measurement &measurement) {

  lcd.clear();

  switch (mode) {
    case Pm:
      displayPm(measurement);
      break;

    case PmAtm:
      displayPmAtm(measurement);
      break;

    case ConcentrationNano:
      displayConcentrationNano(measurement);
      break;

    case ConcentrationMicroLow:
      displayConcentrationMicroLow(measurement);
      break;

    case ConcentrationMicroHight:
      displayConcentrationMicroHigh(measurement);
      break;
  }

  if (autoChange) {
    mode = getNextMode();
  }
}


void Lcd::toggleAutoChange() {

  autoChange = !autoChange;
}


void Lcd::changeMode() {

  mode = getNextMode();
}


void Lcd::displayPm(const Measurement &measurement) {

  printMessage(measurement, "PM 1/2.5/10 Cv=1", [](const Measurement & measurement, char *buff) {
    sprintf(buff, "%d/%d/%d ", measurement.pm1, measurement.pm2_5, measurement.pm10);
  });
}


void Lcd::displayPmAtm(const Measurement &measurement) {

  printMessage(measurement, "PM 1/2.5/10 Atm", [](const Measurement & measurement, char *buff) {
    sprintf(buff, "%d/%d/%d ", measurement.pmAtm1, measurement.pmAtm2_5, measurement.pmAtm10);
  });
}


void Lcd::displayConcentrationNano(const Measurement &measurement) {

  printMessage(measurement, "N/0.1l: 0.3/0.5", [](const Measurement & measurement, char *buff) {
    sprintf(buff, "%d/%d", measurement.concentration0_3, measurement.concentration0_3);
  });
}


void Lcd::displayConcentrationMicroLow(const Measurement &measurement) {

  printMessage(measurement, "N/0.1l: 1/2.5", [](const Measurement & measurement, char *buff) {
    sprintf(buff, "%d/%d", measurement.concentration1, measurement.concentration2_5);
  });
}


void Lcd::displayConcentrationMicroHigh(const Measurement &measurement) {

  printMessage(measurement, "N/0.1l: 5/10", [](const Measurement & measurement, char *buff) {
    sprintf(buff, "%d/%d", measurement.concentration5, measurement.concentration10);
  });
}


void Lcd::printMessage(const Measurement &measurement, String label,
                       void (*fillMessageBuffer)(const Measurement &, char*)) {

  lcd.setCursor(0, 0);
  lcd.print(label);

  fillMessageBuffer(measurement, msg);

  lcd.setCursor(0, 1);
  lcd.print(msg);
}


Mode Lcd::getNextMode() const {

  switch (mode) {

    case Pm:
      return PmAtm;

    case PmAtm:
      return ConcentrationNano;

    case ConcentrationNano:
      return ConcentrationMicroLow;

    case ConcentrationMicroLow:
      return ConcentrationMicroHight;

    case ConcentrationMicroHight:
      return Pm;

    default:
      debugPrintLine("Unknown mode");
      return Pm;
  }
}
