
/*
 * dataHandler.h
 *
 * Created: 5/1/2023 9:43:08 PM
 *  Author: Marius
 */ 

int16_t dataHandler_getTempData();
void dataHandler_setTemperature(int16_t sensorTemperature);

void dataHandler_setHumidity(int16_t sensorHumidity);
int16_t dataHandler_getHumData();
