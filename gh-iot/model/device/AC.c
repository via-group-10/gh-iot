#include "AC.h"
#include <stdio.h>

bool turnOn = false;
void AC_turnOn()
{
	if (!turnOn)
	{
		turnOn = true;
		printf("AC £ºTurn on");
	}
}
void AC_turnOff()
{
	if (turnOn)
	{
		turnOn = false;
		printf("AC : Turn off");
	}
}