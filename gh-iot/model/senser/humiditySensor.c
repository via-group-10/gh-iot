#include "humiditySensor.h"
#include "../time/myTime.h"
#include <stdlib.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

typedef struct humiditySensor{
	float reportInterval;
	float value;
	SemaphoreHandle_t readWriteSemaphore;
	myTime_t updateTime;
	float maxhum;
	float minhum;
	int humstatus;
} humiditySensor;

humiditySensor_t humiditySensor_create(float reportInterval)
{
	humiditySensor_t newhumiditySensor = calloc(sizeof(humiditySensor), 1);
	if (NULL == newhumiditySensor)
	{
		return NULL;
	}
	newhumiditySensor->reportInterval = reportInterval;
	newhumiditySensor->value = 0.0;
	newhumiditySensor->humstatus = 0;
	newhumiditySensor->updateTime = myTime_create();
	newhumiditySensor->readWriteSemaphore = xSemaphoreCreateBinary();
	
	xSemaphoreGive(newhumiditySensor->readWriteSemaphore);
	return newhumiditySensor;
}

void humiditySensor_setReportInterval(humiditySensor_t self,float reportInterval)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->reportInterval = reportInterval;
	xSemaphoreGive(self->readWriteSemaphore);
}
void humiditySensor_setMaxValue(humiditySensor_t self,float value)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->maxhum = value;
	self->humstatus = 1;
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}
void humiditySensor_setMinValue(humiditySensor_t self,float value)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->minhum = value;
	self->humstatus = 1;
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}
void humiditySensor_setHumStatus(humiditySensor_t self,float value)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->humstatus = value;
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}
void humiditySensor_setValue(humiditySensor_t self,float value)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	self->value = value;
	if (self->humstatus==1)
	{
		if (self->maxhum<self->value)
		{
			
		}
		else if (self->maxhum>=self->value&&self->minhum<=self->value)
		{
			
		}
		else
		{
			
		}
	}
	myTime_updateToNowTime(self->updateTime);
	xSemaphoreGive(self->readWriteSemaphore);
}

float humiditySensor_getReportInterval(humiditySensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	float result = self->reportInterval;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

float humiditySensor_getValue(humiditySensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	float result = self->value;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}
float humiditySensor_getMaxValue(humiditySensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	float result = self->maxhum;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}
float humiditySensor_getMinValue(humiditySensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	float result = self->minhum;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}
float humiditySensor_getHumStatus(humiditySensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	float result = self->humstatus;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}

myTime_t humiditySensor_getUpdateTime(humiditySensor_t self)
{
	xSemaphoreTake(self->readWriteSemaphore, portMAX_DELAY);
	myTime_t result = self->updateTime;
	xSemaphoreGive(self->readWriteSemaphore);
	return result;
}
