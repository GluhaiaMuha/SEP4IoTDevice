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
void temperature_wakeup();
void temperature_measure();
int16_t temperature_getLatestTemperature();
int16_t humidity_getLatestHumidity();
void store_data_in_buffer(int16_t reading);
int16_t temperature_getAvgTemperature();
inline void temperature_task_init();
inline void temperature_task_run(void);
void temperature_task();