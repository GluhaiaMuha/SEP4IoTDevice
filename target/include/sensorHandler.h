
/*
 * sensorHandler.h
 *
 * Created: 5/1/2023 9:57:35 PM
 *  Author: Marius
 */ 

#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <ATMEGA_FreeRTOS.h>
#include <task.h>


void sensorsHandler_createSensors();
void sensorHandler_init();
void sensorHandler_run(TickType_t* xLastWakeTime, TickType_t xFrequency);
void sensorsHandler_task(void *pvParameters);