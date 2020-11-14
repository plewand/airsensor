# Air quality sensor/alarm #

This project contains code used to handle a DIY air quality sensor/alarm for Arduino.
The intention was to have a device that allows to contantly monitor and measure air quality.
When the given pollution level (PM1/PM2.5/PM10) is exceeded the device alarms about it.

As it needs a dedicated hardware to run, you can use the code in own projects or just treat as a usage example.

## Structure

- C++ language is used (small feature set is used though)
- Compatible with C++ 11 standard
- No external libraries used beside available in Arduino IDE
- Simple structure, divided to classes handling one functionality
- No dynamic memory allocation
- Prepared to long term no reset work
- Entry point: AirQuality.ino

## IDE

Currently Arduino IDE is tested.

## Hardware used

1. Arduino Leonardo
2. Air quality sensor Plantower PMS5003
3. 16x2 LCD display JHD162A-YG
4. Potentiometer to set LCD brightness
5. Potentiometer to set alarm PM2.5 level
6. Tact switch to change display mode
7. 3.3V/5V voltage converter BSS138 (Waveshare 9127)
8. Power bank as the power source
9. Beeper to notify poor air quality

## License

The program is distributed under [MIT License](LICENSE.md).
