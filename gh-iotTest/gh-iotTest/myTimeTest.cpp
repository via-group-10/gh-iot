#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/time/myTime.h"
}

TEST(myTimeTest, myTime_addOneSec_zero) {
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 0);
}

TEST(myTimeTest,myTime_addOneSec_one) {
	myTime_addOneSec();
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 1);
}

TEST(myTimeTest, myTime_addOneSec_many) {
	myTime_updateNowTime(0, 0, 0, 0, 0, 0);
	myTime_addOneSec();
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 1);
	myTime_addOneSec();
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 2);
	myTime_addOneSec();
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 3);
	myTime_addOneSec();
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 4);
}

TEST(myTimeTest, myTime_addOneSec_boundary) {
	myTime_updateNowTime(0, 0, 0, 0, 0, 0);
	myTime_addOneSec();
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 1);
	for (int x = 0; x < 60; x++)
	{
		myTime_addOneSec();
	}
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 1);
	for (int x = 0; x < 60*60; x++)
	{
		myTime_addOneSec();
	}
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 1);
	for (int x = 0; x < 60 * 60*24; x++)
	{
		myTime_addOneSec();
	}
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 1);
}

TEST(myTimeTest, myTime_create_one) {
	myTime_t create = myTime_create();
	EXPECT_EQ(myTime_getYear(create), 0);
	EXPECT_EQ(myTime_getMon(create), 0);
	EXPECT_EQ(myTime_getDay(create), 0);
	EXPECT_EQ(myTime_getHour(create), 0);
	EXPECT_EQ(myTime_getMin(create), 0);
	EXPECT_EQ(myTime_getSec(create), 0);
}

TEST(myTimeTest, updateToNowTime_one) {
	myTime_t create = myTime_create();
	EXPECT_EQ(myTime_getYear(create), 0);
	EXPECT_EQ(myTime_getMon(create), 0);
	EXPECT_EQ(myTime_getDay(create), 0);
	EXPECT_EQ(myTime_getHour(create), 0);
	EXPECT_EQ(myTime_getMin(create), 0);
	EXPECT_EQ(myTime_getSec(create), 0);
	for (int x = 0; x < 1; x++)
	{
		myTime_addOneSec();
	}
	for (int x = 0; x < 60 * 2; x++)
	{
		myTime_addOneSec();
	}
	for (int x = 0; x < 60 * 60 * 3; x++)
	{
		myTime_addOneSec();
	}
	myTime_updateToNowTime(create);
	EXPECT_EQ(myTime_getYear(create), myTime_getYear(myTime_getNowTime()));
	EXPECT_EQ(myTime_getMon(create), myTime_getMon(myTime_getNowTime()));
	EXPECT_EQ(myTime_getDay(create), myTime_getDay(myTime_getNowTime()));
	EXPECT_EQ(myTime_getHour(create), myTime_getHour(myTime_getNowTime()));
	EXPECT_EQ(myTime_getMin(create), myTime_getMin(myTime_getNowTime()));
	EXPECT_EQ(myTime_getSec(create), myTime_getSec(myTime_getNowTime()));
}

TEST(myTimeTest, myTime_updateNowTime_one) {
	myTime_updateNowTime(1, 2, 3, 4, 5, 6);
	EXPECT_EQ(myTime_getYear(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getMon(myTime_getNowTime()), 2);
	EXPECT_EQ(myTime_getDay(myTime_getNowTime()), 3);
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 4);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 5);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 6);
}

TEST(myTimeTest, myTime_updateNowTime_boundary) {
	myTime_updateNowTime(1, 2, 3, -1, -1, -1);
	EXPECT_EQ(myTime_getYear(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getMon(myTime_getNowTime()), 2);
	EXPECT_EQ(myTime_getDay(myTime_getNowTime()), 3);
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 0);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 0);
	myTime_updateNowTime(1, 2, 3, 100, 100, 100);
	EXPECT_EQ(myTime_getYear(myTime_getNowTime()), 1);
	EXPECT_EQ(myTime_getMon(myTime_getNowTime()), 2);
	EXPECT_EQ(myTime_getDay(myTime_getNowTime()), 3);
	EXPECT_EQ(myTime_getHour(myTime_getNowTime()), 23);
	EXPECT_EQ(myTime_getMin(myTime_getNowTime()), 59);
	EXPECT_EQ(myTime_getSec(myTime_getNowTime()), 59);
}