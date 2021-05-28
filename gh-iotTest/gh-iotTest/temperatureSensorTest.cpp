#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/senser/temperatureSensor.h"
#include "../../gh-iot/model/time/myTime.h"
}

class temperatureSensorTest : public ::testing::Test {
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

TEST(temperatureSensorTest, temperatureSensor_create_one) {
	temperatureSensor_t create = temperatureSensor_create(1);

	EXPECT_EQ(temperatureSensor_getValue(create), 0);
	EXPECT_EQ(temperatureSensor_getReportInterval(create), 1);
	myTime_t initTime = temperatureSensor_getUpdateTime(create);
	myTime_t createTime = myTime_create();
	EXPECT_EQ(myTime_getYear(initTime), myTime_getYear(createTime));
	EXPECT_EQ(myTime_getMon(initTime), myTime_getMon(createTime));
	EXPECT_EQ(myTime_getDay(initTime), myTime_getDay(createTime));
	EXPECT_EQ(myTime_getHour(initTime), myTime_getHour(createTime));
	EXPECT_EQ(myTime_getMin(initTime), myTime_getMin(createTime));
	EXPECT_EQ(myTime_getSec(initTime), myTime_getSec(createTime));
	EXPECT_EQ(temperatureSensor_getTempstatus(create), 0);
	EXPECT_EQ(temperatureSensor_getmaxValue(create), NULL);
	EXPECT_EQ(temperatureSensor_getminValue(create), NULL);
}

TEST(temperatureSensorTest, temperatureSensor_create_boundary) {
	temperatureSensor_t create = temperatureSensor_create(0);

	EXPECT_EQ(temperatureSensor_getValue(create), 0);
	EXPECT_EQ(temperatureSensor_getReportInterval(create), 1);
	myTime_t initTime = temperatureSensor_getUpdateTime(create);
	myTime_t createTime = myTime_create();
	EXPECT_EQ(myTime_getYear(initTime), myTime_getYear(createTime));
	EXPECT_EQ(myTime_getMon(initTime), myTime_getMon(createTime));
	EXPECT_EQ(myTime_getDay(initTime), myTime_getDay(createTime));
	EXPECT_EQ(myTime_getHour(initTime), myTime_getHour(createTime));
	EXPECT_EQ(myTime_getMin(initTime), myTime_getMin(createTime));
	EXPECT_EQ(myTime_getSec(initTime), myTime_getSec(createTime));
	EXPECT_EQ(temperatureSensor_getTempstatus(create), 0);
	EXPECT_EQ(temperatureSensor_getmaxValue(create), NULL);
	EXPECT_EQ(temperatureSensor_getminValue(create), NULL);
}