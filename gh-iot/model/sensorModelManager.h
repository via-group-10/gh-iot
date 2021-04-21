#pragma once
#include "senser/temperatureSensor.h"
#include "senser/humiditySensor.h"
#include "senser/carbonDioxideSensor.h"

void sensorModelManager_create();
void sensorModelManager_setReportInterval(float reportInterval);
temperatureSensor_t sensorModelManager_getTemperatureSensor();
humiditySensor_t sensorModelManager_getHumiditySensor();
carbonDioxideSensor_t sensorModelManager_getCarbonDioxideSensor();