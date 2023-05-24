
/*
 * servo.c
 *
 * Created: 5/21/2023 9:07:26 PM
 *  Author: Marius
 */ 

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>
#include <rc_servo.h>

#include "../Headers/servo.h"
#include "../Headers/dataHandler.h"


static int8_t position;
static uint8_t servoNo = 1;

static TickType_t xLastWakeTime;
static TickType_t xFrequency;

void servo_create(){

	rc_servo_initialise();

	printf("Initialization of servo was successful!\n");
}
void servo_turnOn()
{
	position = 100;
	rc_servo_setPosition(servoNo, position);
	printf("Servo is turned on!\n");
}
void servo_turnOff()
{
	position = 0;
	rc_servo_setPosition(servoNo, position);
	printf("Servo is turned off!\n");
}



static limitResult co2Handler_compareData(int16_t temperature, int16_t minLimit, int16_t maxLimit)
{
	limitResult result;
	if (temperature >= minLimit && temperature <= maxLimit)
	{
		result = BETWEEN;
	}
	else if (temperature < minLimit)
	{
		result = BELLOW;
	}
	else
	{
		result = ABOVE;
	}
	return result;
}


void servoHandler_Init()
{
	xLastWakeTime  = xTaskGetTickCount();
	xFrequency = pdMS_TO_TICKS(150000); // = 2.5 min
}


void servoHandler_run(void)
{
	printf("Servo Task Started\n");
	xTaskDelayUntil(&xLastWakeTime, xFrequency);
	
    int16_t tempData = dataHandler_getTempData();
	struct ServoLimits limits = dataHandler_getLimits();

	limitResult result = co2Handler_compareData(tempData, limits.minTempLimit, limits.maxTempLimit);

	if(result == ABOVE)
	{
		servo_turnOff();
	}
	else if(result == BELLOW)
	{
		servo_turnOn();
	}

}

void servo_task()
{
	xTaskCreate(
	servo_createTask
	,  "servoHandlerTask"
	,  configMINIMAL_STACK_SIZE
	,  NULL
	,  2
	,  NULL );
}

void servo_createTask(void* pvParameters)
{
	(void)pvParameters;
	
	servoHandler_Init();

	for(;;)
	{
		servoHandler_run();
	}
}