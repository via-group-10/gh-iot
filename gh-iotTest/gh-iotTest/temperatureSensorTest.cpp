#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/senser/temperatureSensor.h"
}

TEST(temperatureSensorTest, temperatureSensor_create_one) {
	temperatureSensor_t create = temperatureSensor_create(1);

	EXPECT_EQ(temperatureSensor_getValue(create), 0);
	//EXPECT_EQ(temperatureSensor_getReportInterval(create), 1);
	//EXPECT_EQ(temperatureSensor_getUpdateTime(create), myTime_create());
	//EXPECT_EQ(temperatureSensor_getTempstatus(create), 0);
	//EXPECT_EQ(temperatureSensor_getmaxValue(create), NULL);
	//EXPECT_EQ(temperatureSensor_getminValue(create), NULL);
}