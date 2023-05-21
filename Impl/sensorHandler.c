
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

#include "../Headers/dataHandler.h"
#include "../Headers/sensorHandler.h"
#include "../Headers/temperature.h"

static int16_t lastTempRecorded;
static int16_t lastHumidityRecorded;
static int16_t lastAvgRecorded;

void sensorsHandler_createTemperatureSensor()
{
	temperature_create();
	
	xTaskCreate(
	temperature_task
	,  "temperatureTask"  // A name just for humans
	,  configMINIMAL_STACK_SIZE  // This stack size can be checked & adjusted by reading the Stack Highwater
	,  NULL
	,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
	,  NULL );
}

/************************************************************************/
/* Responsible for handling sensors                                     */
/************************************************************************/

void sensorsHandler_task(void* pvParameters)
{
	// Remove compiler warnings
	(void)pvParameters;
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	const TickType_t xFrequency = 30000/portTICK_PERIOD_MS; // 300000 ms == 5 mins
	
	for(;;)
	{
		printf("SensorHandler Task Started\n");
		xTaskDelayUntil(&xLastWakeTime, xFrequency);
		
		lastTempRecorded = temperature_getLatestTemperature();
		dataHandler_setTemperature(lastTempRecorded);
		
		lastAvgRecorded = temperature_getAvgTemperature();
		dataHandler_setAvgTemperature(lastAvgRecorded);
		
		lastHumidityRecorded = humidity_getLatestHumidity();
		dataHandler_setHumidity(lastHumidityRecorded);
	}
}