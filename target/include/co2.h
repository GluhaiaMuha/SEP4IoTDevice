#include <stdint.h>

void co2_sensor_create();
void co2_sensor_measure();
uint16_t co2_sensor_get_last_reading();

void co2_task();