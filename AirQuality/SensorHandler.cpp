#include "SensorHandler.h"
#include "Debug.h"


SensorHandler::SensorHandler()
  : sensorSerial(Pin::AirSensorRx, AirSensorTx) {
  
  readByteNumber = 0;
}


void SensorHandler::initialize() {
  
  sensorSerial.begin(BAUD_RATE);
}


bool SensorHandler::measure(Measurement &measurement) {  

  if(sensorSerial.available() < 1) {
    return false;
  }

  clearFrameBuffer();

  char headerSignature0 = readByte();
  if (headerSignature0 != 0x42) {
    debugPrintNum("Corrupted header 0", headerSignature0);
    return false;
  }

  waitForData(1);
  
  char headerSignature1 = readByte();
  if (headerSignature1 != 0x4d) {
    debugPrintNum("Corrupted header 0", headerSignature1);
    return false;
  }

  waitForData(2);

  int len = readUShort();
  if (len != 28) {
    debugPrintNum("Corrupted length", len);
    return false;
  }

  waitForData(len);  


  measurement.pm1 = readUShort();
  measurement.pm2_5 = readUShort();
  measurement.pm10 = readUShort();

  measurement.pmAtm1 = readUShort();
  measurement.pmAtm2_5 = readUShort();
  measurement.pmAtm10 = readUShort();


  measurement.concentration0_3 = readUShort();
  measurement.concentration0_5 = readUShort();
  measurement.concentration1 = readUShort();

  measurement.concentration2_5 = readUShort();
  measurement.concentration5 = readUShort();
  measurement.concentration10 = readUShort();

  measurement.reserved = readUShort();
  measurement.checksum = readUShort();
  measurement.checksumValid = calcCheckSum() == measurement.checksum;
  
  return true;
}


void SensorHandler::clearFrameBuffer() {
  
  readByteNumber = 0;
}


UShort SensorHandler::readUShort() {
  
  byte high = sensorSerial.read();
  byte low = sensorSerial.read();
  
  frameBuffer[readByteNumber++] = high;
  frameBuffer[readByteNumber++] = low;
  
  return (high << 8) | low;
}


byte SensorHandler::readByte() {
  
  byte data = sensorSerial.read();
  
  frameBuffer[readByteNumber++] = data;
  
  return data;
}


UShort SensorHandler::calcCheckSum() {

  UShort sum = 0;

  for (int i = 0; i < FRAME_SIZE - 2; i++) {
    sum += (UShort)(frameBuffer[i]) & 0xff;
  }

  return sum;
}


void SensorHandler::waitForData(int expectedNum) {
  
  while (sensorSerial.available() < expectedNum) {
  }
}
