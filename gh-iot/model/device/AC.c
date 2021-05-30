#include "AC.h"
#include <stdio.h>
#include <stdbool.h>
#include "rcServo.h"

static bool ac_turnOn = false;
static int ac_turnOnStatue = -1;

void AC_turnOnHeating()
{
	if (!ac_turnOn||ac_turnOnStatue!=1)
	{
		ac_turnOn = true;
		ac_turnOnStatue = 1;
		printf("AC £ºTurn on heating");
		rcServo_turnLeft(0,50);
	}
}

void AC_turnOnCooling()
{
	if (!ac_turnOn||ac_turnOnStatue!=0)
	{
		ac_turnOn = true;
		ac_turnOnStatue = 0;
		printf("AC £ºTurn on cooling");
		rcServo_turnRight(0,50);
	}
}

void AC_turnOff()
{
	if (ac_turnOn)
	{
		ac_turnOn = false;
		printf("AC : Turn off");
		rcServo_backToZero(0);
	}
}

int AC_getStateCode()
{
	if (ac_turnOn)
	{
		return ac_turnOnStatue;
	}
	else
	{
		return -1;
	}
}