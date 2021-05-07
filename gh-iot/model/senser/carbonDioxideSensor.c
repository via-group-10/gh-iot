#include "carbonDioxideSensor.h"
#include "../time/myTime.h"
#include "../device/carbonDioxideGenerator.h"
#include <stdlib.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

typedef struct carbonDioxideSensor{
	float reportInterval;
	int value;
	SemaphoreHandle_t readWriteSemaphore;
	myTime_t updateTime;
	int maxco2;
	int minco2;
	int co2status;
} carbonDioxideSensor;

carbonDioxideSensor_t carbonDioxideSensor_create(float reportInterval)
{
	carbonDioxideSensor_t newcarbonDioxideSensor = calloc(sizeof(carbonDioxideSensor), 1);
	if (NULL == newcarbonDioxideSensor)
	{
		return NULL;
	}
	newcarbonDioxideSensor->reportInterval = reportInterval;
	newcarbonDioxideSensor->value = 0;
	newcarbonDioxideSensor->co2status = 0;
	newcarbonDioxideSensor->updateTime = myTime_create();
	newcarbonDioxideSensor->readWriteSemaphore = xSemaphoreCreateBinary();
	
	xSemaphoreGive(newcarbonDioxideSensor->readWriteSemaphore);
	return newcarbonDioxideSensor;
}

void carbonDioxideSensor_setReportInterval(carbonDioxideSensor_t self,float reportInterval)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->reportInterval = reportInterval;
	xSemaphoreGive(self->readWriteSemaphore);
}

void carbonDioxideSensor_setValue(carbonDioxideSensor_t self,int value)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->value = value;
	if (self->co2status==1)
	{
		if (self->maxco2<self->value)
		{
			carbonDioxideGenerator_turnOff();
		}
		else if (self->maxco2>=self->value&&self->minco2<=self->value)
		{
			
		}
		else
		{
			carbonDioxideGenerator_turnOn();
		}
	}
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}

float carbonDioxideSensor_getReportInterval(carbonDioxideSensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	float result = self->reportInterval;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

int carbonDioxideSensor_getValue(carbonDioxideSensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	int result = self->value;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

myTime_t carbonDioxideSensor_getUpdateTime(carbonDioxideSensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	myTime_t result = self->updateTime;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

void carbonDioxideSensor_setMaxCo2Value(carbonDioxideSensor_t self, int value)
{
	xSemaphoreTake(self->readWriteSemaphore,portMAX_DELAY);
	self->maxco2 = value;
	self->co2status = 1;
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}

void carbonDioxideSensor_setMinCo2Value(carbonDioxideSensor_t self, int value)
{
	xSemaphoreTake(self->readWriteSemaphore,portMAX_DELAY);
	self->minco2 = value;
	self->co2status = 1;
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}

void carbonDioxideSensor_setCo2SensorStatus(carbonDioxideSensor_t self, int value)
{
	xSemaphoreTake(self->readWriteSemaphore,portMAX_DELAY);
	self->co2status = value;
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}

int carbonDioxideSensor_getMaxValue(carbonDioxideSensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	int result = self->maxco2;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

int carbonDioxideSensor_getMinValue(carbonDioxideSensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	int result = self->minco2;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

int carbonDioxideSensor_getCo2Status(carbonDioxideSensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	int result = self->co2status;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}