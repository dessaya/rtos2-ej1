#include "led.h"
#include "task.h"

void ledTask(void *param)
{
    ledTaskParam_t *taskParam = param;

    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        gpioWrite(taskParam->led, ON);
        msgQueue_send(*taskParam->sink, "LED ON");
        vTaskDelayUntil(&lastWakeTime, 500);
        gpioWrite(taskParam->led, OFF);
        vTaskDelayUntil(&lastWakeTime, 500);
    }
}

