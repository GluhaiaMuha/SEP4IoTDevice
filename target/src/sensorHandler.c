
/*
 * sensorHandler.c
 *
 * Created: 5/1/2023 9:57:43 PM
 *  Author: Marius
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

#include <dataHandler.h>
#include <sensorHandler.h>
#include <temperature.h>
#include <co2.h>

static int16_t lastTempRecorded;
static int16_t lastHumidityRecorded;
static int16_t lastAvgRecorded;
static uint16_t lastCo2Recorded;

TickType_t xLastWakeTime;
TickType_t xFrequency;

void sensorsHandler_createSensors()
{
	temperature_create();

	xTaskCreate(
		temperature_task, "temperatureTask" // A name just for humans
		,
		configMINIMAL_STACK_SIZE // This stack size can be checked & adjusted by reading the Stack Highwater
		,
		NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
		,
		NULL);

	co2_sensor_create();
	xTaskCreate(
		co2_task, "co2Task", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
}

/************************************************************************/
/* Responsible for handling sensors                                     */
/************************************************************************/
void sensorHandler_task_init()
{
	xLastWakeTime = xTaskGetTickCount();
	xFrequency = 30000 / portTICK_PERIOD_MS; // 300000 ms == 5 mins
}

void sensorHandler_task_run(TickType_t* xLastWakeTime, TickType_t xFrequency)
{
	printf("SensorHandler Task Started\n");
	xTaskDelayUntil(&xLastWakeTime, xFrequency);

	lastTempRecorded = temperature_getLatestTemperature();
	dataHandler_setTemperature(lastTempRecorded);

	lastAvgRecorded = temperature_getAvgTemperature();
	dataHandler_setAvgTemperature(lastAvgRecorded);

	lastHumidityRecorded = humidity_getLatestHumidity();
	dataHandler_setHumidity(lastHumidityRecorded);

	lastCo2Recorded = co2_sensor_get_last_reading();
	dataHandler_setCo2(lastCo2Recorded);
}

void sensorsHandler_task(void *pvParameters)
{
	// Remove compiler warnings
	(void)pvParameters;

	for (;;)
	{
		sensorHandler_task_run(&xLastWakeTime, xFrequency);
	}
}