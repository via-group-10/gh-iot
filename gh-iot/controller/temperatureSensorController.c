#include "temperatureSensorController.h"
#include "../model/senser/temperatureSensor.h"
#include "../model/time/myTime.h"
#include <stdio.h>
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

float temperature = 0.0;
temperatureSensor_t sensor;

void temperatureSensorController_task(void *pvParameters)
{
	for(;;)
	{
		if ( HIH8120_OK != hih8120_wakeup() )
		{
			printf("Temperature sensor didn't wakeup!!!");
		}
		
		//wait sensor to wakeup
		vTaskDelay(pdMS_TO_TICKS(temperatureSensor_getReportInterval(sensor)*500));
		PORTA ^= _BV(PA0);
		
		if ( HIH8120_OK !=  hih8120_measure() )
		{
			printf("Temperature sensor didn't measure!!!");
		}
		
		//wait sensor to get the value
		vTaskDelay(pdMS_TO_TICKS(temperatureSensor_getReportInterval(sensor)*500));
		PORTA ^= _BV(PA0);
		
		//save new value
		temperature = hih8120_getTemperature();
		temperatureSensor_setValue(sensor,temperature);
		//print temperature (the print of float is ?, so print it as int)
		int a = temperatureSensor_getValue(sensor);
		int b = temperatureSensor_getValue(sensor)*10000-a*10000;
		myTime_t time = temperatureSensor_getUpdateTime(sensor);
		printf("temperature(%d.%d.%d %d:%d:%d):%d.%d",myTime_getYear(time), myTime_getMon(time), myTime_getDay(time), myTime_getHour(time), myTime_getMin(time), myTime_getSec(time),a,b);
	}
}

void temperatureSensorController_create(temperatureSensor_t temperatureSensor)
{
	if ( HIH8120_OK == hih8120_initialise() )
	{
		sensor = temperatureSensor;
		printf("Temperature sensor started!!!\n");
		xTaskCreate(temperatureSensorController_task, "TemperatureSensorTask", configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
		//vTaskStartScheduler();
	}
}