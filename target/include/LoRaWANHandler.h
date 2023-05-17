#include <ATMEGA_FreeRTOS.h>

void lora_handler_task( void *pvParameters );
void lora_handler_initialise(UBaseType_t lora_handler_task_priority);
static void _lora_setup(void);
void lora_handler_task( void *pvParameters );
