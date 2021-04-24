#include "temperatureSensorController.h"
#include "../model/senser/temperatureSensor.h"
#include "../model/time/myTime.h"
#include <stdio.h>
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

float temperature = 0.0;
temperatureSensor_t temSensor;

void temperatureSensorController_task(void *pvParameters)
{
	for(;;)
	{
		if ( HIH8120_OK != hih8120_wakeup() )
		{
			printf("Temperature sensor didn't wakeup!!!");
		}
		
		//wait sensor to wakeup
		vTaskDelay(pdMS_TO_TICKS(temperatureSensor_getReportInterval(temSensor)*500));
		PORTA ^= _BV(PA0);
		
		if ( HIH8120_OK !=  hih8120_measure() )
		{
			printf("Temperature sensor didn't measure!!!");
		}
		
		//wait sensor to get the value
		vTaskDelay(pdMS_TO_TICKS(temperatureSensor_getReportInterval(temSensor)*500));
		PORTA ^= _BV(PA0);
		
		//save new value
		temperature = hih8120_getTemperature();
		temperatureSensor_setValue(temSensor,temperature);
		//print temperature (the print of float is ?, so print it as int)
		int a = temperatureSensor_getValue(temSensor);
		int b = temperatureSensor_getValue(temSensor)*10000-a*10000;
		myTime_t time = temperatureSensor_getUpdateTime(temSensor);
		//printf("temperature:%d.%d",a,b);
	}
}

void temperatureSensorController_create(temperatureSensor_t sensor)
{
	temSensor = sensor;
	printf("Temperature sensor started!!!\n");
	xTaskCreate(temperatureSensorController_task, "TemperatureSensorTask", configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
	//vTaskStartScheduler();
}