#include "model/sensorModelManager.h"
#include "model/senser/temperatureSensor.h"
#include "model/senser/humiditySensor.h"
#include "model/senser/carbonDioxideSensor.h"
#include <stddef.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>

#include <lora_driver.h>
#include <status_leds.h>

// Parameters for OTAA join - You have got these in a mail from IHA
#define LORA_appEUI "9C2D2B085519EB77"
#define LORA_appKEY "2DC29091123D1EA9C2EBA88B19181B2F"

static char _out_buf[100];

void lora_handler_task( void *pvParameters );

static lora_driver_payload_t _uplink_payload;
static lora_driver_payload_t downlinkPayload;
static MessageBufferHandle_t downLinkBufferHandle;
static char devEui[17]; // It is static to avoid it to occupy stack space in the task

static void _lora_setup(void)
{
	lora_driver_returnCode_t rc;
	status_leds_slowBlink(led_ST2); // OPTIONAL: Led the green led blink slowly while we are setting up LoRa

	// Factory reset the transceiver
	printf("FactoryReset >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_rn2483FactoryReset()));
	
	// Configure to EU868 LoRaWAN standards
	printf("Configure to EU868 >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_configureToEu868()));

	// Get the transceivers HW EUI
	rc = lora_driver_getRn2483Hweui(_out_buf);
	printf("Get HWEUI >%s<: %s\n",lora_driver_mapReturnCodeToText(rc), _out_buf);

	// Set the HWEUI as DevEUI in the LoRaWAN software stack in the transceiver
	printf("Set DevEUI: %s >%s<\n", _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setDeviceIdentifier(_out_buf)));

	// Set Over The Air Activation parameters to be ready to join the LoRaWAN
	printf("Set OTAA Identity appEUI:%s appKEY:%s devEUI:%s >%s<\n", LORA_appEUI, LORA_appKEY, _out_buf, lora_driver_mapReturnCodeToText(lora_driver_setOtaaIdentity(LORA_appEUI,LORA_appKEY,_out_buf)));

	// Save all the MAC settings in the transceiver
	printf("Save mac >%s<\n",lora_driver_mapReturnCodeToText(lora_driver_saveMac()));

	// Enable Adaptive Data Rate
	printf("Set Adaptive Data Rate: ON >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_setAdaptiveDataRate(LORA_ON)));

	// Set receiver window1 delay to 500 ms - this is needed if down-link messages will be used
	printf("Set Receiver Delay: %d ms >%s<\n", 500, lora_driver_mapReturnCodeToText(lora_driver_setReceiveDelay(500)));

	// Join the LoRaWAN
	uint8_t maxJoinTriesLeft = 10;
	
	do {
		rc = lora_driver_join(LORA_OTAA);
		printf("Join Network TriesLeft:%d >%s<\n", maxJoinTriesLeft, lora_driver_mapReturnCodeToText(rc));

		if ( rc != LORA_ACCEPTED)
		{
			// Make the red led pulse to tell something went wrong
			status_leds_longPuls(led_ST1); // OPTIONAL
			// Wait 5 sec and lets try again
			vTaskDelay(pdMS_TO_TICKS(5000UL));
		}
		else
		{
			break;
		}
	} while (--maxJoinTriesLeft);

	if (rc == LORA_ACCEPTED)
	{
		// Connected to LoRaWAN :-)
		// Make the green led steady
		status_leds_ledOn(led_ST2); // OPTIONAL
	}
	else
	{
		// Something went wrong
		// Turn off the green led
		status_leds_ledOff(led_ST2); // OPTIONAL
		// Make the red led blink fast to tell something went wrong
		status_leds_fastBlink(led_ST1); // OPTIONAL

		// Lets stay here
		while (1)
		{
			taskYIELD();
		}
	}
}

void lora_handler_downlink()
{
	int16_t hum;
	int16_t temp;
	
	//xMessageBufferReceive(downLinkMessageBufferHandle, &downlinkPayload, 2, portMAX_DELAY);
	printf("DOWN LINK: from port: %d with %d bytes received!", downlinkPayload.portNo, downlinkPayload.len); // Just for Debug
	if (4 == downlinkPayload.len) // Check that we have got the expected 4 bytes
	{
       // decode the payload into our variales
       temp = (downlinkPayload.bytes[0] << 8) + downlinkPayload.bytes[1];
       hum = (downlinkPayload.bytes[2] << 8) + downlinkPayload.bytes[3];
	   
	}
}

void lora_handler_decodeUplink(lora_driver_payload_t load)
{
	int16_t temp;
	int16_t hum;
	int16_t carbon;
	temp = (load.bytes[0] << 8) + load.bytes[1];
    hum = (load.bytes[2] << 8) + load.bytes[3];
	carbon = (load.bytes[4] << 8) + load.bytes[5];
	printf("|%d_%d_%d|",temp,hum,carbon);
}

void lora_handler_decodeDownlink(lora_driver_payload_t load)
{
	int16_t minTemp;
	int16_t maxTemp;
	int16_t minHum;
	int16_t maxHum;
	int16_t minCO2;
	int16_t maxCO2;
	int16_t status;
	int16_t tempStatus; //off=0,on=1
	int16_t humStatus; //off=0,on=1
	int16_t CO2Status; //off=0,on=1
	
	minTemp = (load.bytes[0] << 8) + load.bytes[1];
	maxTemp = (load.bytes[2] << 8) + load.bytes[3];
	minHum = (load.bytes[4] << 8) + load.bytes[5];
	maxHum = (load.bytes[6] << 8) + load.bytes[7];
	minCO2 = (load.bytes[8] << 8) + load.bytes[9];
	maxCO2 = (load.bytes[10] << 8) + load.bytes[11];
	status = (load.bytes[12] << 8) + load.bytes[13];
	tempStatus = status-status/10*10;
	humStatus = status-status/100*100-tempStatus;
	CO2Status = (status-humStatus-tempStatus)/100;
	printf("|%d_%d_%d_%d_%d_%d_%d_%d_%d|",minTemp,maxTemp,minHum,maxHum,minCO2,maxCO2,tempStatus,humStatus,CO2Status);
}

/*-----------------------------------------------------------*/
void lora_handler_task( void *pvParameters )
{
	// Hardware reset of LoRaWAN transceiver
	lora_driver_resetRn2483(1);
	vTaskDelay(2);
	lora_driver_resetRn2483(0);
	// Give it a chance to wakeup
	vTaskDelay(150);

	//lora_driver_flushBuffers(); // get rid of first version string from module after reset!

	_lora_setup();

	_uplink_payload.len = 6;
	_uplink_payload.portNo = 2;
	
	for(;;)
	{
		
		int16_t temp = temperatureSensor_getValue(sensorModelManager_getTemperatureSensor());
		int16_t hum = humiditySensor_getValue(sensorModelManager_getHumiditySensor());
		int16_t co2_ppm = carbonDioxideSensor_getValue(sensorModelManager_getCarbonDioxideSensor());
		
		_uplink_payload.bytes[0] = temp >> 8;
		_uplink_payload.bytes[1] = temp & 0xFF;
		_uplink_payload.bytes[2] = hum >> 8;
		_uplink_payload.bytes[3] = hum & 0xFF;
		_uplink_payload.bytes[4] = co2_ppm >> 8;
		_uplink_payload.bytes[5] = co2_ppm & 0xFF;

		status_leds_shortPuls(led_ST4);  // OPTIONAL
		PORTA ^= _BV(PA3);
		char *result = lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload));
		printf("Upload Message >%s<\n", result);
		if (result=="MAC_RX"||result=="OK")
		{
			downlinkPayload.portNo = 1;
			downlinkPayload.len = 14;
			xMessageBufferReceive(downLinkBufferHandle, &downlinkPayload, sizeof(lora_driver_payload_t), portMAX_DELAY);
			PORTA ^= _BV(PA3);
			printf("DOWN LINK: from port: %d with %d bytes received!", downlinkPayload.portNo, downlinkPayload.len); // Just for Debug
			lora_handler_decodeDownlink(downlinkPayload);
			//example:0002000a00030014006403840065
			lora_driver_payload_t testPayload;
			testPayload.portNo = 1;
			testPayload.len = 14;
			testPayload.bytes[0] = 2 >> 8;
			testPayload.bytes[1] = 2 & 0xFF;
			testPayload.bytes[2] = 10 >> 8;
			testPayload.bytes[3] = 10 & 0xFF;
			testPayload.bytes[4] = 3 >> 8;
			testPayload.bytes[5] = 3 & 0xFF;
			testPayload.bytes[6] = 20 >> 8;
			testPayload.bytes[7] = 20 & 0xFF;
			testPayload.bytes[8] = 100 >> 8;
			testPayload.bytes[9] = 100 & 0xFF;
			testPayload.bytes[10] = 900 >> 8;
			testPayload.bytes[11] = 900 & 0xFF;
			testPayload.bytes[12] = 101 >> 8;
			testPayload.bytes[13] = 101 & 0xFF;
			//lora_handler_decodeDownlink(testPayload);
		}
		else if (result!="MAC_TX_OK"&&result!="OK")
		{
			// Hardware reset of LoRaWAN transceiver
			lora_driver_resetRn2483(1);
			vTaskDelay(2);
			lora_driver_resetRn2483(0);
			// Give it a chance to wakeup
			vTaskDelay(150);
			printf("Rejoin Network TriesLeft:>%s<\n", lora_driver_mapReturnCodeToText(lora_driver_join(LORA_OTAA)));
			printf("Upload Message >%s<\n", lora_driver_mapReturnCodeToText(lora_driver_sendUploadMessage(false, &_uplink_payload)));
		}
		PORTA ^= _BV(PA3);
		lora_handler_decodeUplink(_uplink_payload);
		//wait 1 min
		vTaskDelay(pdMS_TO_TICKS(6000));
		//lora_handler_downlink();
	}
}

void lora_handler_initialise(MessageBufferHandle_t messageBufferHandle)
{
	downLinkBufferHandle = messageBufferHandle;
	xTaskCreate(lora_handler_task,"LRHand",configMINIMAL_STACK_SIZE,(void*)1,tskIDLE_PRIORITY + 2,NULL);
	//xTaskCreate(lora_handler_downlinkTask,"LRDownlink",configMINIMAL_STACK_SIZE,(void*)1,tskIDLE_PRIORITY + 2,NULL);
}

