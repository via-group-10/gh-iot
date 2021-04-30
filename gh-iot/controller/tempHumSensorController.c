#include "tempHumSensorController.h"
#include "../model/senser/humiditySensor.h"
#include "../model/senser/temperatureSensor.h"
#include "../model/time/myTime.h"
#include <stdio.h>
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

float temperature = 0.0;
temperatureSensor_t temperatureSensor;
float humility = 0.0;
humiditySensor_t humiditySensor;

void tempHumSensorController_task(void *pvParameters)
{
	for(;;)
	{
		long reportInterval = (temperatureSensor_getReportInterval(temperatureSensor)+humiditySensor_getReportInterval(humiditySensor))*500;
		
		if ( HIH8120_OK != hih8120_wakeup() )
		{
			printf("Temperature sensor didn't wakeup!!!");
		}
		
		//wait sensor to wakeup
		vTaskDelay(pdMS_TO_TICKS(reportInterval/2));
		PORTA ^= _BV(PA0);
		
		if ( HIH8120_OK !=  hih8120_measure() )
		{
			printf("Temperature sensor didn't measure!!!");
		}
		
		//wait sensor to get the value
		vTaskDelay(pdMS_TO_TICKS(reportInterval/2));
		PORTA ^= _BV(PA0);
		
		//save new value
		temperature = hih8120_getTemperature();
		temperatureSensor_setValue(temperatureSensor,temperature);
		humility = hih8120_getHumidity();
		humiditySensor_setValue(humiditySensor,humility);
		//print temperature and humiditySensor (the print of float is ?, so print it as int)
		//int a = temperatureSensor_getValue(temperatureSensor);
		//int b = temperatureSensor_getValue(temperatureSensor)*10000-a*10000;
		//int c = humiditySensor_getValue(humiditySensor);
		//int d = humiditySensor_getValue(humiditySensor)*10000-c*10000;
		//printf("temperature:%d.%d,humility:%d.%d",a,b,c,d);
	}
}

void tempHumSensorController_create(temperatureSensor_t tempSensor,humiditySensor_t humSensor)
{
	temperatureSensor = tempSensor;
	humiditySensor = humSensor;
	printf("Temperature/humidity sensor started!\n");
	xTaskCreate(tempHumSensorController_task, "TempHumSensorTask", configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
	//vTaskStartScheduler();
}