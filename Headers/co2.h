
/*
 * co2.h
 *
 * Created: 5/9/2023 9:56:04 PM
 *  Author: Marius
 */ 

#pragma once
#include <stdint.h>

void co2_create();
int16_t co2_getValue();
void co2_task();
int16_t co2_getLatestValue();