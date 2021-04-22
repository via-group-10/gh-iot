#include "../controller/sevenSegmentDisplayController.h"
#include "../controller/temperatureSensorController.h"
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
	sevenSegmentDisplayController_create(0.5);
	
	//create temperature sensor controller
	temperatureSensor = temperatureSensor_create(1);
	temperatureSensorController_create(temperatureSensor);
	
	//create humidity sensor controller
	humiditySensor = humiditySensor_create(1);
	HumSensorController_create(humiditySensor);
	
	//create carbon dioxide sensor controller
	carbonDioxideSensor = carbonDioxideSensor_create(1);
	CO2SensorController_create(carbonDioxideSensor);
	vTaskStartScheduler();
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
