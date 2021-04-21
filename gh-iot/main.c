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
	// A3 for LoRaWAN
	// A4 means 7-segment Display is showing carbon dioxide
	// A5 means 7-segment Display is showing humidity
	// A6 means 7-segment Display is showing temperature
	// A7 means 7-segment Display is showing time(hh.mm)
	DDRA |= _BV(DDA0) | _BV(DDA1) | _BV(DDA2) | _BV(DDA3) | _BV(DDA4) | _BV(DDA5) | _BV(DDA6) | _BV(DDA7);
	//Turn off all led
	PORTA ^= _BV(PA0);
	PORTA ^= _BV(PA1);
	PORTA ^= _BV(PA2);
	PORTA ^= _BV(PA3);
	PORTA ^= _BV(PA4);
	PORTA ^= _BV(PA5);
	PORTA ^= _BV(PA6);
	PORTA ^= _BV(PA7);
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
