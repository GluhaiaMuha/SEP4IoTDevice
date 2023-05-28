#include <gtest/gtest.h>
#include "fff/fff.h"
#include "FreeRTOS_defs/FreeRTOS_FFF_MocksDeclaration.h"

extern "C"
{
	#include <servo.h>
	#include <rc_servo.h>
	#include <FreeRTOS.h>
    #include <ATMEGA_FreeRTOS.h>
    #include <task.h>
}

FAKE_VOID_FUNC(rc_servo_initialise);
FAKE_VOID_FUNC(rc_servo_setPosition, uint8_t, int8_t );
class Servo_test : public ::testing::Test
{
protected:
  void SetUp() override
  {
	RESET_FAKE(rc_servo_initialise);
	RESET_FAKE(rc_servo_setPosition);
    FFF_RESET_HISTORY();
  }
  void TearDown() override
  {
  }
};

TEST_F(Servo_test, Should_call_rc_servo_initialise_when_servo_create_is_called)
{
  // Act
  servo_create();
  // Assert
  EXPECT_EQ(rc_servo_initialise_fake.call_count, 1);
}