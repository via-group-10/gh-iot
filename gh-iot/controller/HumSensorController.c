#include "HumSensorController.h"
#include "../model/senser/humiditySensor.h"
#include "../model/time/myTime.h"
#include <stdio.h>
#include <hih8120.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

float humility = 0.0;
humiditySensor_t humSensor;

void HumSensorController_task(void *pvParameters)
{
	for(;;)
	{
		if ( HIH8120_OK != hih8120_wakeup() )
		{
			printf("Temperature sensor didn't wakeup!!!");
		}
		
		//wait sensor to wakeup
		vTaskDelay(pdMS_TO_TICKS(humiditySensor_getReportInterval(humSensor)*500));
		PORTA ^= _BV(PA1);
		
		if ( HIH8120_OK !=  hih8120_measure() )
		{
			printf("Humility sensor didn't measure!!!");
		}
		
		//wait sensor to get the value
		vTaskDelay(pdMS_TO_TICKS(humiditySensor_getReportInterval(humSensor)*500));
		PORTA ^= _BV(PA1);
		
		//save new value
		humility = hih8120_getHumidity();
		humiditySensor_setValue(humSensor,humility);
		//print temperature (the print of float is ?, so print it as int)
		int a = humiditySensor_getValue(humSensor);
		int b = humiditySensor_getValue(humSensor)*10000-a*10000;
		myTime_t time = humiditySensor_getUpdateTime(humSensor);
		printf("Hum%d.%d",a,b);
	}
}

void HumSensorController_create(humiditySensor_t sensor)
{
	humSensor = sensor;
		printf("Humility sensor started!!!\n");
		xTaskCreate(HumSensorController_task, "HumSensorTask", configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
		//vTaskStartScheduler();
}