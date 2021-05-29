#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/device/HumilityGenerator.h"
}

class HumilityGeneratorTest : public ::testing::Test {
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

TEST(HumilityGeneratorTest, HumilityDioxideGenerator_turnOnOne) {
	HumilityGenerator_turnOn();
	EXPECT_EQ(HumilityGenerator_getStateCode(), 0);
}

TEST(HumilityGeneratorTest, HumilityDioxideGenerator_turnOffOne) {
	HumilityGenerator_turnOff();
	EXPECT_EQ(HumilityGenerator_getStateCode(), -1);
}

TEST(HumilityGeneratorTest, HumilityDioxideGenerator_getStateCodeOne) {
	HumilityGenerator_turnOn();
	EXPECT_EQ(HumilityGenerator_getStateCode(), 0);
	HumilityGenerator_turnOff();
	EXPECT_EQ(HumilityGenerator_getStateCode(), -1);
}

