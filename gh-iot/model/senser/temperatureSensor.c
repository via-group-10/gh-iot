#include "temperatureSensor.h"
#include <stdlib.h>

typedef struct temperatureSensor{
	float reportInterval;
	float value;
} temperatureSensor;temperatureSensor_t temperatureSensor_create(float reportInterval){	temperatureSensor_t newTemperatureSensor = calloc(sizeof(temperatureSensor), 1);	if (NULL == newTemperatureSensor) 
	{ 
		return NULL;
	}		newTemperatureSensor->reportInterval = reportInterval;	newTemperatureSensor->value = 0.0;	return newTemperatureSensor;}void temperatureSensor_setReportInterval(temperatureSensor_t self,float reportInterval){	self->reportInterval = reportInterval;}void temperatureSensor_setValue(temperatureSensor_t self,float value){	self->value = value;}float temperatureSensor_getReportInterval(temperatureSensor_t self){	return self->reportInterval;}float temperatureSensor_getValue(temperatureSensor_t self){	return self->value;}