#if !defined _SENSOR_HANDLER_H_
#define _SENSOR_HANDLER_H_

#include "Common.h"
#include <SoftwareSerial.h>
#include "Measurement.h"

#define HEADER_LENGTH (4)
#define FRAME_LENGTH (28)
#define FRAME_SIZE (HEADER_LENGTH + FRAME_LENGTH)
#define BAUD_RATE (9600)

class SensorHandler {

  public:

    SensorHandler();

    void initialize();

    bool measure(Measurement &measurement);

  private:

    SoftwareSerial sensorSerial;
    char frameBuffer[FRAME_SIZE];
    int readByteNumber;


    void clearFrameBuffer();

    UShort readUShort();

    byte readByte();

    UShort calcCheckSum();

    void waitForData(int expectedNum);
};

#endif
