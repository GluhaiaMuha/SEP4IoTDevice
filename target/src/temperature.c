/*
 * temperature.c
 *
 * Responsible for the Temperature Sensor HIH8120
 *
 * Created: 5/1/2023 9:51:46 PM
 *  Author: Marius
 */ 

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>

#include <temperature.h>
#include <hih8120.h>

#define BUFFER_SIZE 10
int16_t readings[BUFFER_SIZE];

static int16_t temperatures[10];
static int indexOfLatestTemperature = 0;

TickType_t xLastWakeTime;
TickType_t xFrequency1;
TickType_t xFrequency2;
TickType_t xFrequency3;


void temperature_create(){
	hih8120_driverReturnCode_t result = hih8120_initialise();
	if(result != HIH8120_OK){
		printf("Initialization of hih8120 failed!\n");
	}
	else{
		printf("Initialization of hih8120 was successful!\n");
	}
}

void temperature_wakeup(){
	hih8120_driverReturnCode_t result = hih8120_wakeup();
	
	if (result != HIH8120_OK)
	{
		printf("Wake up of hih8120 failed!\n");
	}
	else{
		printf("Wake up of hih8120 was successful!\n");
	}
}

void temperature_measure(){
	hih8120_driverReturnCode_t result = hih8120_measure();
	
	if (result != HIH8120_OK)
	{
		printf("Measure of hih8120 failed!\n");
	}
	else{
		printf("Measure of hih8120 was successful!\n");
	}
}

int16_t temperature_getLatestTemperature(){
	int16_t measuredTemperature =  hih8120_getTemperature_x10();
	printf("Latest temperature: %d\n", measuredTemperature);
	
	return measuredTemperature;
}

int16_t humidity_getLatestHumidity()
{
	int16_t measureHumidity = hih8120_getHumidityPercent_x10();
	printf("Latest Humidity Measured: %d\n", measureHumidity);
	
	return measureHumidity;
}

void store_data_in_buffer(int16_t reading)
{
	static int buffer_index = 0;
	if (buffer_index < BUFFER_SIZE)
	{
		readings[buffer_index] = reading;
		buffer_index++;
	}else{
		//Buffer is full, overwrite oldest reading
		for (int i = 1; i < BUFFER_SIZE; i++)
		{
			readings[i - 1] = readings[i];
		}
		readings[BUFFER_SIZE - 1] = reading;
	}
}

int16_t temperature_getAvgTemperature()
{
	int16_t sum = 0;
	int count = 0;
	
	
	for (int i = 0; i< BUFFER_SIZE; i++)
	{
		if (readings[i] != 0)
		{
			sum+= readings[i];
			count++;
		}
	}
	
	if (count == 0)
	{
		return 0;
	}
	
	printf("Latest Average Temp read: %d\n", (int16_t)(sum/count));
	return (int16_t)(sum/count);
}


//inline for performance improvement
inline void temperature_task_init(){
	xLastWakeTime = xTaskGetTickCount();
xFrequency1 = 1/portTICK_PERIOD_MS; // 1 ms
	xFrequency2 = 50/portTICK_PERIOD_MS; // 50 ms
	xFrequency3 = 30000/portTICK_PERIOD_MS; // 30000 ms

	temperature_create();
}

inline void temperature_task_run(TickType_t* xLastWakeTime, TickType_t xFrequency1,TickType_t xFrequency2,TickType_t xFrequency3){
	printf("Temperature Task started\n");
		
		temperature_wakeup();
		xTaskDelayUntil(xLastWakeTime, xFrequency2);
		
		
		temperature_measure();
		xTaskDelayUntil(xLastWakeTime, xFrequency1);
		
		temperature_getLatestTemperature();
		//wait 30 seconds for next measurement
		xTaskDelayUntil(xLastWakeTime, xFrequency3);
}


void temperature_task(void* pvParameters){
	// Remove compiler warnings
	(void)pvParameters;

	temperature_task_init();

	for (;;)
	{
		/*We pass xLastWakeTime because
		we need it for testing*/
		temperature_task_run(&xLastWakeTime, xFrequency1, xFrequency2, xFrequency3);
	}
}