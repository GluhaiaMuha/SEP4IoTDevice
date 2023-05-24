#include <gtest/gtest.h>
#include "fff/fff.h"

extern "C"
{
	#include <temperature.h>
  #include <hih8120.h>

  #define BUFFER_SIZE 10
  int16_t readings[BUFFER_SIZE];
}

DEFINE_FFF_GLOBALS;
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_initialise);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_wakeup);
FAKE_VALUE_FUNC(hih8120_driverReturnCode_t, hih8120_measure);
FAKE_VALUE_FUNC(int16_t, hih8120_getTemperature_x10);
FAKE_VALUE_FUNC(uint16_t, hih8120_getHumidityPercent_x10);

// Create Test fixture and Reset all Mocks before each test
class Temperature_test : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(hih8120_initialise);
    RESET_FAKE(hih8120_wakeup);
    RESET_FAKE(hih8120_measure);
    RESET_FAKE(hih8120_getTemperature_x10);
    RESET_FAKE(hih8120_getHumidityPercent_x10);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};
 
TEST_F(Temperature_test, Should_call_hih8120_initialise_when_temperature_create_is_called){
  //Arrange
  hih8120_initialise_fake.return_val = HIH8120_OK;
  //Act
  temperature_create();
  //Assert
  EXPECT_EQ(hih8120_initialise_fake.call_count, 1);
}

TEST_F(Temperature_test, Should_call_hih8120_wakeup_when_temperature_wakeup_is_called){
  //Arrange
  hih8120_wakeup_fake.return_val = HIH8120_OK;
  //Act
  temperature_wakeup();
  //Assert
  EXPECT_EQ(hih8120_wakeup_fake.call_count, 1);
}

TEST_F(Temperature_test, Should_call_hih8120_measure_when_temperature_measure_is_called){
  //Arrange
  hih8120_measure_fake.return_val = HIH8120_OK;
  //Act
  temperature_measure();
  //Assert
  EXPECT_EQ(hih8120_measure_fake.call_count, 1);
}

TEST_F(Temperature_test, Should_return_correct_value_when_temperature_getLatestTemperature_is_called){
  //Arrange
  hih8120_getTemperature_x10_fake.return_val = 30;
  int16_t _temperature;
  //Act
  _temperature = temperature_getLatestTemperature();
  //Assert
  EXPECT_EQ(hih8120_getTemperature_x10_fake.call_count, 1);
  EXPECT_EQ(_temperature, 30);
}

TEST_F(Temperature_test, Should_return_correct_value_when_humidity_getLatestHumidity_is_called){
  //Arrange
  hih8120_getHumidityPercent_x10_fake.return_val = 5;
  uint16_t _humidity;
  //Act
  _humidity = humidity_getLatestHumidity();
  //Assert
  EXPECT_EQ(hih8120_getHumidityPercent_x10_fake.call_count, 1);
  EXPECT_EQ(_humidity, 5);
}

TEST_F(Temperature_test, Should_store_data_in_buffer){
  //clear readings
  memset(readings, 0, sizeof(readings));

  store_data_in_buffer(10);
  EXPECT_EQ(readings[0], 10);
}

TEST_F(Temperature_test, Should_return_correct_value_when_temperature_getAvgTemperature_is_called)
{
   for(int i = 0; i < BUFFER_SIZE; ++i) {
        readings[i] = i+1;  // Fill buffer with values 1 to BUFFER_SIZE
    }
    // Expected average is (1+2+...+BUFFER_SIZE) / BUFFER_SIZE
    int16_t expected_average = (BUFFER_SIZE*(BUFFER_SIZE+1))/(2*BUFFER_SIZE);
    EXPECT_EQ(temperature_getAvgTemperature(), expected_average);
}
//lololo
//vrever
//xdxdxdxd