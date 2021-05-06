#include "HumilityGenerator.h"
#include <stdio.h>
#include <stdbool.h>

bool hum_turnOn = false;
void HumilityGenerator_turnOn()
{
	if (!hum_turnOn)
	{
		hum_turnOn = true;
		printf("humidifier £ºTurn on");
	}
}
void HumilityGenerator_turnOff()
{
	if (hum_turnOn)
	{
		hum_turnOn = false;
		printf("humidifier : Turn off");
	}
}