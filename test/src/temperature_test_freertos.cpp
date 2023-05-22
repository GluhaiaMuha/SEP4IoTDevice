#include <gtest/gtest.h>
#include "fff/fff.h"
#include "FreeRTOS_defs/FreeRTOS_FFF_MocksDeclaration.h"

extern "C"
{
    #include <temperature.h>
    #include <hih8120.h>
    #include <FreeRTOS.h>
    #include <ATMEGA_FreeRTOS.h>
    #include <task.h>
}

FAKE_VOID_FUNC(temperature_task_run);
FAKE_VOID_FUNC(temperature_task_init);

class Temperature_freertos_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        RESET_FAKE(temperature_task_run);
        RESET_FAKE(temperature_task_init);
        RESET_FAKE(xTaskCreate);
		RESET_FAKE(xSemaphoreTake);
		RESET_FAKE(xSemaphoreGive);
		RESET_FAKE(xTaskGetTickCount);
		RESET_FAKE(xTaskDelayUntil);
		FFF_RESET_HISTORY();
    }
    void TearDown() override
    {}
};
/*
TEST_F(Temperature_freertos_test, temperature_task_init_is_called){
    temperature_task_init();

    ASSERT_EQ(temperature_create_fake.call_count, 1);
}*/
/*
TEST_F(Temperature_freertos_test, xTaskDelayUntil_is_called){
    //Arrange
    TickType_t xLastWakeTime = 0/portTICK_PERIOD_MS;
	TickType_t xFrequency1 = 1/portTICK_PERIOD_MS; // 1 ms
	TickType_t xFrequency2 = 50/portTICK_PERIOD_MS; // 50 ms
	TickType_t xFrequency3 = 30000/portTICK_PERIOD_MS; // 30000 ms
    //Act
    temperature_task_init();
    temperature_task_run();
    //Assert
    ASSERT_EQ(3, xTaskDelayUntil_fake.call_count);
    //first delay call
    ASSERT_EQ(xLastWakeTime, *xTaskDelayUntil_fake.arg0_val);
    ASSERT_EQ(xFrequency2, xTaskDelayUntil_fake.arg1_val);
    //*second delay call
    ASSERT_EQ(xLastWakeTime, *xTaskDelayUntil_fake.arg0_history[1]);
    ASSERT_EQ(xFrequency1, xTaskDelayUntil_fake.arg1_history[1]);
    //third delay call
    ASSERT_EQ(xLastWakeTime, *xTaskDelayUntil_fake.arg0_history[2]);
    ASSERT_EQ(xFrequency3, xTaskDelayUntil_fake.arg1_history[2]);
}
*/
