#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/device/AC.h"
}

class ACTest : public ::testing::Test {
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

TEST(ACTest, AC_turnOnHeating) {
	AC_turnOnHeating();
	EXPECT_EQ(AC_getStateCode(), 1);
}
TEST(ACTest, AC_turnOnCooling) {
	AC_turnOnCooling();
	EXPECT_EQ(AC_getStateCode(), 0);
}
TEST(ACTest, AC_turnOff) {
	AC_turnOff();
	EXPECT_EQ(AC_getStateCode(), -1);
}
TEST(ACTest, AC_getStateCode) {
	AC_turnOnHeating();
	EXPECT_EQ(AC_getStateCode(), 1);
	AC_turnOnCooling();
	EXPECT_EQ(AC_getStateCode(), 0);
	AC_turnOff();
	EXPECT_EQ(AC_getStateCode(), -1);
}