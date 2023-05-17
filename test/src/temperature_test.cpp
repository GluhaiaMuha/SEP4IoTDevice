#include <gtest/gtest.h>
#include "fff/fff.h"

extern "C"
{
	#include <temperature.h>
  #include <hih8120.h>
}

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);

// Create Test fixture and Reset all Mocks before each test
class Temperature_test : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(hih8120_initialise);
    RESET_FAKE(hih8120_wakeup);
    RESET_FAKE(hih8120_measure);
    RESET_FAKE(hih8120_getTemperature_x10)
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};
 
TEST_F(Temperature_test, Test_hih8120_initialise_is_called){
  //Arrange
  hih8120_initialise_fake.return_val = HIH8120_OK;
  //Act
  temperature_create();
  //Assert
  ASSERT_EQ(hih8120_initialise_fake.call_count, 1);
}

TEST_F(Temperature_test, Test_hih8120_wakeup_is_called){
  //Arrange
  hih8120_wakeup_fake.return_val = HIH8120_OK;
  //Act
  temperature_wakeup();
  //Assert
  ASSERT_EQ(hih8120_wakeup_fake.call_count, 1);
}

TEST_F(Temperature_test, Test_hih8120_measure_is_called){
  //Arrange
  hih8120_measure_fake.return_val = HIH8120_OK;
  //Act
  temperature_measure();
  //Assert
  ASSERT_EQ(hih8120_measure_fake.call_count, 1);
}

TEST_F(Temperature_test, Test_getTemperature_return_value){
  //Arrange
  hih8120_getTemperature_x10_fake.return_val = 30;
  int16_t _temperature;
  //Act
  _temperature = temperature_getLatestTemperature();
  //Assert
  ASSERT_EQ(hih8120_getTemperature_x10_fake.call_count, 1);
  ASSERT_EQ(_temperature, 30);
}

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest2, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}