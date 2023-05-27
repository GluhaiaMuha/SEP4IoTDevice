
/*
 * dataHandler.c
 *
 * Created: 5/1/2023 9:42:59 PM
 *  Author: Marius
 */ 

#include <stdio.h>
#include <stdint.h>
#include <dataHandler.h>

static int16_t dataHandlerTemperature;
static int16_t dataHandlerHumidity;
static int16_t dataHandlerAvgTemperature;
static uint16_t dataHandlerCo2;
//For Temperature
int16_t dataHandler_getTempData()
{
	return dataHandlerTemperature;
}


void dataHandler_setTemperature(int16_t sensorTemperature)
{
	dataHandlerTemperature = sensorTemperature;
}


void dataHandler_setAvgTemperature(int16_t sensorAvgTemperature)
{
	dataHandlerAvgTemperature = sensorAvgTemperature;
}


int16_t dataHandler_getAvgTempeature()
{
	return dataHandlerAvgTemperature;
}

//For Humidity
void dataHandler_setHumidity(int16_t sensorHumidity)
{
	dataHandlerHumidity = sensorHumidity;
}

int16_t dataHandler_getHumData()
{
	return dataHandlerHumidity;
}

void dataHandler_setCo2(uint16_t co2)
{
	dataHandlerCo2 = co2;
}