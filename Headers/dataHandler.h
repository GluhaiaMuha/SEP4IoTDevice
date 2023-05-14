
/*
 * dataHandler.h
 *
 * Created: 5/1/2023 9:43:08 PM
 *  Author: Marius
 */ 

int16_t dataHandler_getTempData();
void dataHandler_setTemperature(int16_t sensorTemperature);

void dataHandler_setAvgTemperature(int16_t sensorAvgTemperature);
int16_t dataHandler_getAvgTempeature();

void dataHandler_setHumidity(int16_t sensorHumidity);
int16_t dataHandler_getHumData();

void dataHandler_setCo2(uint16_t sensorCo2);
uint16_t dataHandler_getCo2Data();
