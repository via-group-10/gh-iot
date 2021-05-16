#include "carbonDioxideGenerator.h"
#include <stdio.h>
#include <stdbool.h>

bool co2_turnOn = false;

void carbonDioxideGenerator_turnOn()
{
	if (!co2_turnOn)
	{
		co2_turnOn = true;
		printf("Carbon Dioxide Generator: Turn on");
	}
}

void carbonDioxideGenerator_turnOff()
{
	if (co2_turnOn)
	{
		co2_turnOn = false;
		printf("Carbon Dioxide Generator: Turn off");
	}
}

int carbonDioxideGenerator_getStateCode()
{
	if (co2_turnOn)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}