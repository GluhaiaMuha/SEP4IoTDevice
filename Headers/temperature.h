
/*
 * temperature.h
 *
 * Created: 5/1/2023 9:51:31 PM
 *  Author: Marius
 */ 


#pragma once
#include <stdlib.h>
#include <stdint.h>

void temperature_create();
int16_t temperature_getLatestTemperature();
void temperature_task();
