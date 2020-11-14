#if !defined _MEASUREMENT_H_
#define _MEASUREMENT_H_

#include "Common.h"

struct Measurement {
  UShort pm1;
  UShort pm2_5;
  UShort pm10;
  
  UShort pmAtm1;
  UShort pmAtm2_5;
  UShort pmAtm10;
 
  UShort concentration0_3;
  UShort concentration0_5;
  UShort concentration1;
  
  UShort concentration2_5;
  UShort concentration5;
  UShort concentration10;

  UShort reserved;
  UShort checksum;
  bool checksumValid;
};

#endif
