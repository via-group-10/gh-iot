#include "HumilityGenerator.h"
#include <stdio.h>

bool turnOn = false;
void HumilityGenerator_turnOn()
{
	if (!turnOn)
	{
		turnOn = true;
		printf("humidifier ��Turn on");
	}
}
void HumilityGenerator_turnOff()
{
	if (turnOn)
	{
		turnOn = false;
		printf("humidifier : Turn off");
	}
}