#if !defined _ALARM_H_
#define _ALARM_H_

#include "Common.h"
#include "Measurement.h"
#include "Debug.h"


#define MAX_RAW_SENSITITY (1023ul)

#define MEASUREMENT_NUM (20)
#define ALARM_ON_THRESHOLD (15)
#define ALARM_OFF_THRESHOLD (5)
#define DEACTIVATION_MARGIN (20)
#define MEASUREMENT_UPDATE_PERIOD (1000ul)


class Alarm {

  public:

    Alarm(int alarmPmLevelMin, int alarmLevelMax);

    void initialize();

    void handleMeasurement(const Measurement &measurement);

    int normalizeSensititvity(int raw);

    int getAlarmActivationLevel() const;

    bool active() const;

  private:

    int alarmActivationLevel;
    long activationPmLevelMin;
    long activationPmLevelMax;
    int latestPmLevels[MEASUREMENT_NUM];
    int latestPmLevelsIndex;
    bool alarmEnabled;
    unsigned long lastUpdateTime;

    void checkAlarmState();
};

#endif
