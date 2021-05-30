#include "rcServo.h"
#include <rc_servo.h>

void rcServo_init()
{
	rc_servo_initialise();
}

void rcServo_turnLeft(int servoId,int leftPercent)
{
	if (leftPercent<0)
	{
		leftPercent = -leftPercent;
	}
	rc_servo_setPosition(servoId,-leftPercent);
}

void rcServo_turnRight(int servoId,int rightPercent)
{
	if (rightPercent<0)
	{
		rightPercent = -rightPercent;
	}
	rc_servo_setPosition(servoId,rightPercent);
}

void rcServo_backToZero(int servoId)
{
	rc_servo_setPosition(servoId,0);
}