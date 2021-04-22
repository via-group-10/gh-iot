#include "sevenSegmentDisplayController.h"
#include "../model/senser/temperatureSensor.h"
#include "../model/senser/humiditySensor.h"
#include "../model/senser/carbonDioxideSensor.h"
#include "../model/time/myTime.h"
#include "../model/sensorModelManager.h"
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <display_7seg.h>
#include <stdio.h>

float updateTime;

void sevenSegmentDisplayController_task(void *pvParameters)
{
	while(1)
	{
		//Show hh.mm on 7-segment Display
		PORTA ^= _BV(PA7);
		myTime_t nowTime = myTime_getNowTime();
		float time = myTime_getHour(nowTime)*100+myTime_getMin(nowTime);
		display_7seg_display(time/100,2);
		vTaskDelay(pdMS_TO_TICKS(updateTime*1000));
		PORTA ^= _BV(PA7);
		
		//Show temperature on 7-segment Display
		PORTA ^= _BV(PA6);
		temperatureSensor_t temperatureSensor = sensorModelManager_getTemperatureSensor();
		display_7seg_display(temperatureSensor_getValue(temperatureSensor),2);
		vTaskDelay(pdMS_TO_TICKS(updateTime*1000));
		PORTA ^= _BV(PA6);
		
		//Show humidity on 7-segment Display
		PORTA ^= _BV(PA5);
		humiditySensor_t humiditySensor = sensorModelManager_getHumiditySensor();
		display_7seg_display(humiditySensor_getValue(humiditySensor),2);
		vTaskDelay(pdMS_TO_TICKS(updateTime*1000));
		PORTA ^= _BV(PA5);
		
		//Show carbon dioxide on 7-segment Display
		PORTA ^= _BV(PA4);
		carbonDioxideSensor_t carbonDioxideSensor = sensorModelManager_getCarbonDioxideSensor();
		display_7seg_display(carbonDioxideSensor_getValue(carbonDioxideSensor),0);
		vTaskDelay(pdMS_TO_TICKS(updateTime*1000));
		PORTA ^= _BV(PA4);
	}
}

void sevenSegmentDisplayController_create(float displayUpdateTime)
{
	updateTime = displayUpdateTime;
	//Init 7-segment Display
	display_7seg_initialise(NULL);
	display_7seg_powerUp();
	
	printf("7-segment Display started!!!\n");
	xTaskCreate(sevenSegmentDisplayController_task, "7-segment Display Task", configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
}