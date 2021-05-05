#include "temperatureSensor.h"
#include "../time/myTime.h"
#include <stdlib.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

typedef struct temperatureSensor{
	float reportInterval;
	float value;
	SemaphoreHandle_t readWriteSemaphore;
	myTime_t updateTime;
	float maxTemp;
	float minTemp;
	int tempstatus;
} temperatureSensor;temperatureSensor_t temperatureSensor_create(float reportInterval){	temperatureSensor_t newTemperatureSensor = calloc(sizeof(temperatureSensor), 1);	if (NULL == newTemperatureSensor)
	{ 
		return NULL;
	}	newTemperatureSensor->reportInterval = reportInterval;	newTemperatureSensor->value = 0.0;	newTemperatureSensor->tempstatus = 0;	newTemperatureSensor->updateTime = myTime_create();	newTemperatureSensor->readWriteSemaphore = xSemaphoreCreateBinary();		xSemaphoreGive(newTemperatureSensor->readWriteSemaphore);	return newTemperatureSensor;}void temperatureSensor_setReportInterval(temperatureSensor_t self,float reportInterval){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	self->reportInterval = reportInterval;	xSemaphoreGive(self->readWriteSemaphore);}void temperatureSensor_setValue(temperatureSensor_t self,float value){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	self->value = value;	if (self->tempstatus==1)
	{
		if (self->maxTemp<self->value)
		{
			AC_turnOn;
		}
		else if (self->maxTemp>=self->value&&self->minTemp<=self->value)
		{
			
		}
		else
		{
			AC_turnOff();
		}
	}	myTime_updateToNowTime(self->updateTime);	xSemaphoreGive(self->readWriteSemaphore);}void temperatureSensor_setmaxValue(temperatureSensor_t self,float value){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	self->maxTemp = value;	self->tempstatus = 1;	myTime_updateToNowTime(self->updateTime);	xSemaphoreGive(self->readWriteSemaphore);}void temperatureSensor_setminValue(temperatureSensor_t self,float value){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	self->minTemp = value;	self->tempstatus = 1;	myTime_updateToNowTime(self->updateTime);	xSemaphoreGive(self->readWriteSemaphore);}void temperatureSensor_setTempstatus(temperatureSensor_t self,float value){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	self->tempstatus = value;	myTime_updateToNowTime(self->updateTime);	xSemaphoreGive(self->readWriteSemaphore);}float temperatureSensor_getReportInterval(temperatureSensor_t self){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	float result = self->reportInterval;	xSemaphoreGive(self->readWriteSemaphore);	return result;}float temperatureSensor_getValue(temperatureSensor_t self){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	float result = self->value;	xSemaphoreGive(self->readWriteSemaphore);	return result;}float temperatureSensor_getmaxValue(temperatureSensor_t self){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	float result = self->maxTemp;	xSemaphoreGive(self->readWriteSemaphore);	return result;}float temperatureSensor_getminValue(temperatureSensor_t self){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	float result = self->minTemp;	xSemaphoreGive(self->readWriteSemaphore);	return result;}float temperatureSensor_getTempstatus(temperatureSensor_t self){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	float result = self->tempstatus;	xSemaphoreGive(self->readWriteSemaphore);	return result;}myTime_t temperatureSensor_getUpdateTime(temperatureSensor_t self){	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);	myTime_t result = self->updateTime;	xSemaphoreGive(self->readWriteSemaphore);	return result;}