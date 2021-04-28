#pragma once
#include "../time/myTime.h"

typedef struct carbonDioxideSensor* carbonDioxideSensor_t;

carbonDioxideSensor_t carbonDioxideSensor_create(float reportInterval);
void carbonDioxideSensor_setReportInterval(carbonDioxideSensor_t self,float reportInterval);
void carbonDioxideSensor_setValue(carbonDioxideSensor_t self,int value);
float carbonDioxideSensor_getReportInterval(carbonDioxideSensor_t self);
int carbonDioxideSensor_getValue(carbonDioxideSensor_t self);
myTime_t carbonDioxideSensor_getUpdateTime(carbonDioxideSensor_t self);
//getter&setter
void carbonDioxideSensor_setMaxCo2Value(carbonDioxideSensor_t self, int value);
void carbonDioxideSensor_setMinCo2Value(carbonDioxideSensor_t self, int value);
void carbonDioxideSensor_setCo2SensorStatus(carbonDioxideSensor_t self, int value);
int carbonDioxideSensor_getMaxValue(carbonDioxideSensor_t self);
int carbonDioxideSensor_getMinValue(carbonDioxideSensor_t self);
int carbonDioxideSensor_getCo2Status(carbonDioxideSensor_t self);