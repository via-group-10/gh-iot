/*
* main.c
* Author : IHA
*
* Example main file including LoRaWAN setup
* Just for inspiration :)
*/
#include <stdio.h>
#include <avr/io.h>

#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <stdio_driver.h>
#include <serial.h>

// Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

#include "model/sensorModelManager.h"

void initialiseSystem()
{
	// Set output ports for leds used in the example
	// A0 for temperature sensor
	// A1 for humidity sensor
	// A2 for carbon dioxide sensor
	DDRA |= _BV(DDA0) | _BV(DDA1) | _BV(DDA2) | _BV(DDA7);

	// Make it possible to use stdio on COM port 0 (USB) on Arduino board - Setting 57600,8,N,1
	stdio_initialise(ser_USART0);
}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!!\n");
	sensorModelManager_create();
	
	while (1)
	{
	}
}

