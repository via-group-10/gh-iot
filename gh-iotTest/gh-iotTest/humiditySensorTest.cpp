#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/senser/humiditySensor.h"
#include "../../gh-iot/model/time/myTime.h"
#include"../../gh-iot/model/device/HumilityGenerator.h"
}
class humiditySensorTest : public ::testing::Test {
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};
TEST(humiditySensorTest,humiditySensor_create_One)
{
	humiditySensor_t create = humiditySensor_create(0);
	EXPECT_EQ(humiditySensor_getValue(create), 0);
	EXPECT_EQ(humiditySensor_getReportInterval(create), 1);
	myTime_t initTime = humiditySensor_getUpdateTime(create);
	myTime_t createTime = myTime_create();
	EXPECT_EQ(myTime_getYear(initTime), myTime_getYear(createTime));
	EXPECT_EQ(myTime_getMon(initTime), myTime_getMon(createTime));
	EXPECT_EQ(myTime_getDay(initTime), myTime_getDay(createTime));
	EXPECT_EQ(myTime_getHour(initTime), myTime_getHour(createTime));
	EXPECT_EQ(myTime_getMin(initTime), myTime_getMin(createTime));
	EXPECT_EQ(myTime_getSec(initTime), myTime_getSec(createTime));
	EXPECT_EQ(humiditySensor_getMaxValue(create), NULL);
	EXPECT_EQ(humiditySensor_getMinValue(create), NULL);
}
TEST(humiditySensorTest, humiditySensor_create_Boundary)
{
	humiditySensor_t create = humiditySensor_create(1);
	EXPECT_EQ(humiditySensor_getValue(create), 0);
	EXPECT_EQ(humiditySensor_getReportInterval(create), 1);
	myTime_t initTime = humiditySensor_getUpdateTime(create);
	myTime_t createTime = myTime_create();
	EXPECT_EQ(myTime_getYear(initTime), myTime_getYear(createTime));
	EXPECT_EQ(myTime_getMon(initTime), myTime_getMon(createTime));
	EXPECT_EQ(myTime_getDay(initTime), myTime_getDay(createTime));
	EXPECT_EQ(myTime_getHour(initTime), myTime_getHour(createTime));
	EXPECT_EQ(myTime_getMin(initTime), myTime_getMin(createTime));
	EXPECT_EQ(myTime_getSec(initTime), myTime_getSec(createTime));
	EXPECT_EQ(humiditySensor_getMaxValue(create), NULL);
	EXPECT_EQ(humiditySensor_getMinValue(create), NULL);
}
TEST(humiditySensorTest, humiditySensor_setMaxValue_One)
{
	humiditySensor_t create = humiditySensor_create(1);
	humiditySensor_setMaxValue(create, 50);
	EXPECT_EQ(humiditySensor_getMaxValue(create), 50);
	EXPECT_EQ(humiditySensor_getHumStatus(create),1);
}
TEST(humiditySensorTest, humiditySensor_setMinValue_One)
{
	humiditySensor_t create = humiditySensor_create(1);
	humiditySensor_setMinValue(create, 10);
	EXPECT_EQ(humiditySensor_getMinValue(create), 10);
	EXPECT_EQ(humiditySensor_getHumStatus(create), 1);
}

TEST(humiditySensorTest, humiditySensor_setValue_Boundary)
{
	humiditySensor_t create = humiditySensor_create(1);
	humiditySensor_setMaxValue(create, 50);
	humiditySensor_setMinValue(create, 10);
	humiditySensor_setValue(create, 60);
	EXPECT_EQ(HumilityGenerator_getStateCode(), -1);
	humiditySensor_setValue(create, 40);
	EXPECT_EQ(HumilityGenerator_getStateCode(), -1);
	humiditySensor_setValue(create, 5);
	EXPECT_EQ(HumilityGenerator_getStateCode(), 0);
}