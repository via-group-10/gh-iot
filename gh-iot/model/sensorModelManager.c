#include "../controller/sevenSegmentDisplayController.h"
#include "../controller/tempHumSensorController.h"
#include "../controller/CO2SensorController.h"
#include "senser/temperatureSensor.h"
#include "senser/humiditySensor.h"
#include "senser/carbonDioxideSensor.h"
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

temperatureSensor_t temperatureSensor;
humiditySensor_t humiditySensor;
carbonDioxideSensor_t carbonDioxideSensor;

void sensorModelManager_create()
{
	sevenSegmentDisplayController_create();
	
	//create temperature/humidity sensor controller
	temperatureSensor = temperatureSensor_create(1);
	humiditySensor = humiditySensor_create(1);
	tempHumSensorController_create(temperatureSensor,humiditySensor);
	
	//create carbon dioxide sensor controller
	carbonDioxideSensor = carbonDioxideSensor_create(1);
	CO2SensorController_create(carbonDioxideSensor);	
}

void sensorModelManager_setReportInterval(float reportInterval)
{
	temperatureSensor_setReportInterval(temperatureSensor,reportInterval);
	humiditySensor_setReportInterval(humiditySensor,reportInterval);
	carbonDioxideSensor_setReportInterval(carbonDioxideSensor,reportInterval);
}

temperatureSensor_t sensorModelManager_getTemperatureSensor()
{
	return temperatureSensor;
}

humiditySensor_t sensorModelManager_getHumiditySensor()
{
	return humiditySensor;
}

carbonDioxideSensor_t sensorModelManager_getCarbonDioxideSensor()
{
	return carbonDioxideSensor;
}
