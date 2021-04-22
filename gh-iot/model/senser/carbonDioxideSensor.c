#include "carbonDioxideSensor.h"
#include "../time/myTime.h"
#include <stdlib.h>
#include <ATMEGA_FreeRTOS.h>
#include <semphr.h>

typedef struct carbonDioxideSensor{
	float reportInterval;
	int value;
	SemaphoreHandle_t readWriteSemaphore;
	myTime_t updateTime;
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
