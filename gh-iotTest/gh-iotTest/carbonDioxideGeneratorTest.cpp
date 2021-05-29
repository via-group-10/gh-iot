#include "gtest/gtest.h"
extern "C" {
#include "../../gh-iot/model/device/carbonDioxideGenerator.h"
}

class carbonDioxideGeneratorTest : public ::testing::Test {
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{

	}
};

TEST(carbonDioxideGeneratorTest, carbonDioxideGenerator_turnOnOne) {
	carbonDioxideGenerator_turnOn();
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), 0);
}

TEST(carbonDioxideGeneratorTest, carbonDioxideGenerator_turnOffOne) {
	carbonDioxideGenerator_turnOff();
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), -1);
}

TEST(carbonDioxideGeneratorTest, carbonDioxideGenerator_getStateCodeOne) {
	carbonDioxideGenerator_turnOn();
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), 0);
	carbonDioxideGenerator_turnOff();
	EXPECT_EQ(carbonDioxideGenerator_getStateCode(), -1);
}