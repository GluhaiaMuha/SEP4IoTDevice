#include <gtest/gtest.h>
#include "fff/fff.h"

extern "C"
{
	#include <co2.h>
	#include <mh_z19.h>
}

FAKE_VOID_FUNC(mh_z19_initialise, serial_comPort_t);
FAKE_VALUE_FUNC(mh_z19_returnCode_t, mh_z19_takeMeassuring);

// Create Test fixture and Reset all Mocks before each test
class CO2_test : public ::testing::Test
{
protected:
	void SetUp() override
	{
		RESET_FAKE(mh_z19_initialise);
		RESET_FAKE(mh_z19_takeMeassuring);
		FFF_RESET_HISTORY();
	}
	void TearDown() override
	{}
};

TEST_F(CO2_test, Should_call_mh_z19_initialise_when_co2_sensor_create_is_called)
{
	// Arrange
//	mh_z19_initialise_fake.custom_fake = [](int arg) {
//		// Custom behavior for the mock function
//		EXPECT_EQ(arg, ser_USART3); // Check the argument passed to the mock function
//	};

	// Act
	co2_sensor_create();

	// Assert
	EXPECT_EQ(mh_z19_initialise_fake.call_count, 1);
} 

TEST_F(CO2_test, Should_call_mh_z19_takeMeassuring_when_co2_sensor_measure_is_called)
{
    // Arrange
    mh_z19_takeMeassuring_fake.return_val = MHZ19_OK;

    // Act
    co2_sensor_measure();

    // Assert
    EXPECT_EQ(mh_z19_takeMeassuring_fake.call_count, 1);
}


TEST_F(CO2_test, Should_return_last_reading_when_co2_sensor_get_last_reading_is_called)
{
    // Arrange
    int8_t lastCo2Recorded = 123;

    // Act
    uint16_t result = co2_sensor_get_last_reading();

    // Assert
    EXPECT_EQ(result, 123);
}
