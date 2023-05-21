
/*
 * co2.c
 *
 * Created: 5/9/2023 9:55:56 PM
 *  Author: Marius
 */ 
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <ATMEGA_FreeRTOS.h>
#include <mh_z19.h>

#include "../Headers/co2.h"

uint16_t ppm;


void co2_create()
{
	mh_z19_initialise(ser_USART3);

	printf("Initialization of mh_z19 (CO2 sensor) - success!\n");
}
/*

void co2_measure(){
	
	if (rc != MHZ19_OK)
	{
		printf("Measure of mh_z19 (CO2 sensor) - failed!\n");
	}
	else{
		printf("Measure of mh_z19 (CO2 sensor) - success!\n");
	}
}
*/

int16_t co2_getValue()
{
	return 1;
}

void co2_task()
{
	printf("To implement");
}

int16_t co2_getLatestValue()
{
	return 1;
}
