#include <gtest/gtest.h>
#include "fff/fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"

extern "C"
{
    #include <temperature.h>
    #include <hih8120.h>
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
