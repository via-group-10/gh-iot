#pragma once
#include "../time/myTime.h"

typedef struct temperatureSensor* temperatureSensor_t; 

temperatureSensor_t temperatureSensor_create(float reportInterval);
void temperatureSensor_setReportInterval(temperatureSensor_t self,float reportInterval);
void temperatureSensor_setValue(temperatureSensor_t self,float value);