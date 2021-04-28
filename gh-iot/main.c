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
#include <message_buffer.h>
#include <stream_buffer.h>
#include <semphr.h>
#include <hih8120.h>

#include <stdio_driver.h>
#include <serial.h>

// Needed for LoRaWAN
#include <lora_driver.h>
#include <status_leds.h>

#include "model/sensorModelManager.h"

// Prototype for LoRaWAN handler
void lora_handler_initialise(MessageBufferHandle_t messageBufferHandle);

static MessageBufferHandle_t downLinkMessageBufferHandle;

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
    mh_z19_initialise(ser_USART3);
	
	if ( HIH8120_OK == hih8120_initialise() )
	{
		printf("temperature/humidity sensor init!");
	}
	//BufferSizeBytes can't bigger than 14? program will stuck if it is bigger than 14. Need size: 44(22*2)
	//downLinkMessageBufferHandle = xMessageBufferCreate(sizeof(lora_driver_payload_t)*2);
	lora_driver_initialise(ser_USART1, downLinkMessageBufferHandle);
	//printf("===%d",sizeof(lora_driver_payload_t)*2);
	
}

/*-----------------------------------------------------------*/
int main(void)
{
	initialiseSystem(); // Must be done as the very first thing!!
	printf("Program Started!!!\n");
	sensorModelManager_create();	
	lora_handler_initialise(downLinkMessageBufferHandle);
	vTaskStartScheduler();
	while(1)
	{
		
	}
}

