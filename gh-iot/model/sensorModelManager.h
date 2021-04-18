#pragma once
#include "senser/temperatureSensor.h"

void sensorModelManager_create();
void sensorModelManager_setReportInterval(float reportInterval);
temperatureSensor_t sensorModelManager_getTemperatureSensor();