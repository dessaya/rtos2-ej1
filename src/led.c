#include <stdlib.h>
#include <string.h>
#include "led.h"
#include "task.h"

void ledTask(void *param)
{
    ledTaskParam_t *taskParam = param;

    TickType_t lastWakeTime = xTaskGetTickCount();
    while (1) {
        gpioWrite(taskParam->led, ON);

        char *s = malloc(7);
        if (s == NULL) {
            // Out of memory?
            continue;
        }
        strcpy(s, "LED ON");
        xQueueSend(*taskParam->sink, &s, portMAX_DELAY);

        vTaskDelayUntil(&lastWakeTime, 500);

        gpioWrite(taskParam->led, OFF);

        vTaskDelayUntil(&lastWakeTime, 500);
    }
}

