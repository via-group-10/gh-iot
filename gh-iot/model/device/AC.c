#include "AC.h"
#include <stdio.h>
#include <stdbool.h>

static bool ac_turnOn = false;
static int ac_turnOnStatue;

void AC_turnOnHeating()
{
	if (!ac_turnOn||ac_turnOnStatue!=1)
	{
		ac_turnOn = true;
		ac_turnOnStatue = 1;
		printf("AC £ºTurn on heating");
	}
}

void AC_turnOnCooling()
{
	if (!ac_turnOn||ac_turnOnStatue!=0)
	{
		ac_turnOn = true;
		ac_turnOnStatue = 0;
		printf("AC £ºTurn on Cooling");
	}
}

void AC_turnOff()
{
	if (ac_turnOn)
	{
		ac_turnOn = false;
		printf("AC : Turn off");
	}
}