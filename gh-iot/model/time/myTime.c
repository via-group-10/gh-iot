#include "myTime.h"
#include <stdlib.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <stdio.h>

typedef struct myTime{
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
} myTime;

static myTime_t nowTime;

void myTime_addOneSec()
{
	mytime_tryCreateNowTime();
	nowTime->sec = nowTime->sec += 1;
	if (nowTime->sec>=60)
	{
		nowTime->min = nowTime->min += 1;
		nowTime->sec = 0;
		if (nowTime->min>=60)
		{
			nowTime->hour = nowTime->hour += 1;
			nowTime->min = 0;
			if (nowTime->hour>=24)
			{
				nowTime->hour = 0;
				//update date from api;	
			}
		}
	}
}

void mytime_tryCreateNowTime()
{
	if (NULL == nowTime)
	{
		nowTime = calloc(sizeof(myTime), 1);
		if (NULL != nowTime)
		{
			nowTime->year = 0;
			nowTime->mon = 0;
			nowTime->day = 0;
			nowTime->hour = 0;
			nowTime->min = 0;
			nowTime->sec = 0;
		}
	}
}

myTime_t myTime_create()
{
	mytime_tryCreateNowTime();
	myTime_t newTime = calloc(sizeof(myTime), 1);	if (NULL == newTime)
	{
		return NULL;
	}
	newTime->year = 0;
	newTime->mon = 0;
	newTime->day = 0;
	newTime->hour = 0;
	newTime->min = 0;
	newTime->sec = 0;
	return newTime;
}

void myTime_updateNowTime(int year,int mon,int day,int hour,int min, int sec)
{
	mytime_tryCreateNowTime();
	nowTime->year = year;
	nowTime->mon = mon;
	nowTime->day = day;
	nowTime->hour = hour;
	nowTime->min = min;
	nowTime->sec = sec;
}

void myTime_updateToNowTime(myTime_t self)
{
	mytime_tryCreateNowTime();
	self->year = nowTime->year;
	self->mon = nowTime->mon;
	self->day = nowTime->day;
	self->hour = nowTime->hour;
	self->min = nowTime->min;
	self->sec = nowTime->sec;
}

myTime_t myTime_getNowTime()
{
	mytime_tryCreateNowTime();
	return nowTime;
}

int myTime_getYear(myTime_t self)
{
	return self->year;
}

int myTime_getMon(myTime_t self)
{
	return self->mon;
}

int myTime_getDay(myTime_t self)
{
	return self->day;
}

int myTime_getHour(myTime_t self)
{
	return self->hour;
}

int myTime_getMin(myTime_t self)
{
	return self->min;
}

int myTime_getSec(myTime_t self)
{
	return self->sec;
}

