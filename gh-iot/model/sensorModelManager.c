#include "../controller/temperatureSensorController.h"
#include "senser/temperatureSensor.h"

temperatureSensor_t temperatureSensor;

void sensorModelManager_create()
{
	temperatureSensor = temperatureSensor_create(1);
	temperatureSensorController_create(temperatureSensor);
}

void sensorModelManager_setReportInterval(float reportInterval)
{
	temperatureSensor_setReportInterval(temperatureSensor,reportInterval);
}

temperatureSensor_t sensorModelManager_getTemperatureSensor()
{
	return temperatureSensor;
}