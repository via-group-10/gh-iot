#pragma once
#include "../time/myTime.h"

typedef struct humiditySensor* humiditySensor_t;

humiditySensor_t humiditySensor_create(float reportInterval);
void humiditySensor_setReportInterval(humiditySensor_t self,float reportInterval);
void humiditySensor_setValue(humiditySensor_t self,float value);
float humiditySensor_getReportInterval(humiditySensor_t self);
float humiditySensor_getValue(humiditySensor_t self);
myTime_t humiditySensor_getUpdateTime(humiditySensor_t self);