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
} temperatureSensor;
	{ 
		return NULL;
	}