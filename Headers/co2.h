
/*
 * co2.h
 *
 * Created: 5/9/2023 9:56:04 PM
 *  Author: Marius
 */ 

#include <stdint.h>

void CO2_create();
int16_t CO2_getValue();
void CO2_task();
uint16_t CO2_sensor_get_last_reading();
