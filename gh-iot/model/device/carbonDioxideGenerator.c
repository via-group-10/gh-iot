#include "carbonDioxideGenerator.h"
#include <stdio.h>

bool turnOn = false;

void carbonDioxideGenerator_turnOn()
{
	if (!turnOn)
	{
		turnOn = true;
		printf("Carbon Dioxide Generator: Turn on");
	}
}

void carbonDioxideGenerator_turnOff()
{
	if (turnOn)
	{
		turnOn = false;
		printf("Carbon Dioxide Generator: Turn off");
	}
}