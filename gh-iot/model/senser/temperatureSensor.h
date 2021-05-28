#pragma once
#include "../time/myTime.h"

typedef struct temperatureSensor* temperatureSensor_t; 

temperatureSensor_t temperatureSensor_create(float reportInterval);
void temperatureSensor_setReportInterval(temperatureSensor_t self,float reportInterval);
void temperatureSensor_setValue(temperatureSensor_t self,float value);float temperatureSensor_getReportInterval(temperatureSensor_t self);float temperatureSensor_getValue(temperatureSensor_t self);myTime_t temperatureSensor_getUpdateTime(temperatureSensor_t self);//getter&settervoid temperatureSensor_setmaxValue(temperatureSensor_t self,float value);void temperatureSensor_setminValue(temperatureSensor_t self,float value);void temperatureSensor_setTempstatus(temperatureSensor_t self,float value);float temperatureSensor_getmaxValue(temperatureSensor_t self);float temperatureSensor_getminValue(temperatureSensor_t self);int temperatureSensor_getTempstatus(temperatureSensor_t self);