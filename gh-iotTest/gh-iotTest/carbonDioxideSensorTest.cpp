#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/senser/carbonDioxideSensor.h"
#include "../../gh-iot/model/time/myTime.h"
#include"../../gh-iot/model/device/carbonDioxideGenerator.h"
}
class carbonDioxideSensorTest : public ::testing::Test {
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};
TEST(carbonDioxideSensorTest, carbonDioxideSensor_create_One)
{
	carbonDioxideSensor_t create = carbonDioxideSensor_create(0);
	EXPECT_EQ(carbonDioxideSensor_getValue(create), 0);
	EXPECT_EQ(carbonDioxideSensor_getReportInterval(create), 1);
	EXPECT_EQ(carbonDioxideSensor_getMaxValue(create), NULL);
	EXPECT_EQ(carbonDioxideSensor_getMinValue(create), NULL);
}
TEST(carbonDioxideSensorTest, carbonDioxideSensor_create_Boundary)
{
	carbonDioxideSensor_t create = carbonDioxideSensor_create(1);
	EXPECT_EQ(carbonDioxideSensor_getValue(create), 0);
	EXPECT_EQ(carbonDioxideSensor_getReportInterval(create), 1);
	EXPECT_EQ(carbonDioxideSensor_getMaxValue(create), NULL);
	EXPECT_EQ(carbonDioxideSensor_getMinValue(create), NULL);
}
TEST(carbonDioxideSensorTest, carbonDioxideSensor_setMaxValue)
{
	carbonDioxideSensor_t create = carbonDioxideSensor_create(1);
	carbonDioxideSensor_setMaxCo2Value(create, 2000);
	EXPECT_EQ(carbonDioxideSensor_getMaxValue(create), 2000);
	EXPECT_EQ(carbonDioxideSensor_getCo2Status(create), 1);
}
TEST(carbonDioxideSensorTest, carbonDioxideSensor_setMinValue)
{
	carbonDioxideSensor_t create = carbonDioxideSensor_create(1);
	carbonDioxideSensor_setMinCo2Value(create, 1000);
	EXPECT_EQ(carbonDioxideSensor_getMinValue(create), 1000);
	EXPECT_EQ(carbonDioxideSensor_getCo2Status(create), 1);
}
TEST(carbonDioxideSensorTest, carbonDioxideSensor_setValue_Boundary)
{
	carbonDioxideSensor_t create = carbonDioxideSensor_create(1);
	carbonDioxideSensor_setMaxCo2Value(create, 2000);
	carbonDioxideSensor_setMinCo2Value(create, 1000);
	carbonDioxideSensor_setValue(create, 3000);
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), -1);
	carbonDioxideSensor_setValue(create, 1500);
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), -1);
	carbonDioxideSensor_setValue(create, 500);
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), 0);
}