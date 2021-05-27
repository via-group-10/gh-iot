#pragma once

typedef struct myTime* myTime_t; 

void myTime_addOneSec();
myTime_t myTime_create();
void myTime_updateToNowTime(myTime_t self);
void myTime_updateNowTime(int year,int mon,int day,int hour,int min, int sec);
myTime_t myTime_getNowTime();
int myTime_getYear(myTime_t self);
int myTime_getMon(myTime_t self);
int myTime_getDay(myTime_t self);
int myTime_getHour(myTime_t self);
int myTime_getMin(myTime_t self);
int myTime_getSec(myTime_t self);