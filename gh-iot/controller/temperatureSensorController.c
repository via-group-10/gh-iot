#include "temperatureSensorController.h"
#include "../model/senser/temperatureSensor.h"
#include <stdio.h>
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

float temperature = 0.0;
temperatureSensor_t sensor;

void task(void *pvParameters)
{
	for(;;)
	{
		if ( HIH8120_OK !=  hih8120_measure() )
		{
			printf("something wrong on temperature sensor");
			// Something went wrong
			// Investigate the return code further
		}
		
		//wait sensor to get the value
		vTaskDelay(pdMS_TO_TICKS(temperatureSensor_getReportInterval(sensor)*1000));
		PORTA ^= _BV(PA0);
		
		//save new value
		temperature = hih8120_getTemperature();
		temperatureSensor_setValue(sensor,temperature);
		//print temperature (the print of float is ?, so print it as int)
		int a = temperatureSensor_getValue(sensor)*1000;
		printf("temperature:%d",a);
	}
}

void temperatureSensorController_create(temperatureSensor_t temperatureSensor)
{
	if ( HIH8120_OK == hih8120_initialise() )
	{
		sensor = temperatureSensor;
		printf("Temperature sensor started!!!\n");
		xTaskCreate(task, "TemperatureSensorTask", configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
		vTaskStartScheduler();
	}
}