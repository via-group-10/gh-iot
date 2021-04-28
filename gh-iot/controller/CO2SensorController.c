#include "CO2SensorController.h"
#include "../model/senser/carbonDioxideSensor.h"
#include "../model/time/myTime.h"
#include <stdio.h>
#include <mh_z19.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include 
uint16_t appm;
mh_z19_returnCode_t rc;
carbonDioxideSensor_t carbon;
uint16_t co2max;
uint16_t co2min;
void carbonDioxideController_task(void *pvParmeters)
{
	//mh_z19_setAutoCalibration(false);
	//mh_z19_injectCallBack(myCo2CallBack(appm));
	for(;;)
	{
	
	if (rc != MHZ19_OK)
	{
		printf("CO2 sensor does not OK\n");
	}
	rc = mh_z19_takeMeassuring();	
	vTaskDelay(pdMS_TO_TICKS(carbonDioxideSensor_getReportInterval(carbon)*500));
	PORTA ^= _BV(PA2);
	vTaskDelay(pdMS_TO_TICKS(carbonDioxideSensor_getReportInterval(carbon)*500));
	//
	PORTA ^= _BV(PA2);
	mh_z19_getCo2Ppm(&appm);
	int u = appm;
	
	//printf("Carbon:%d\n",u);
	carbonDioxideSensor_setValue(carbon,u);
	myTime_t time = carbonDioxideSensor_getUpdateTime(carbon);
	}
}
void CO2SensorController_create(carbonDioxideSensor_t co2)
{
		carbon = co2;
		printf("CO2 sensor started!!!\n");
		xTaskCreate(carbonDioxideController_task,"COXTask",configMINIMAL_STACK_SIZE, (void*)1, tskIDLE_PRIORITY + 1, NULL);
		//vTaskStartScheduler();
}
void myCo2CallBack(uint16_t cppm)
{
	cppm = appm;
}