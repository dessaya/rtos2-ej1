#include <stdlib.h>
#include "btn.h"
#include "task.h"

void btnTask(void *param)
{
    btnTaskParam_t *taskParam = param;

    TickType_t period =  10 / portTICK_RATE_MS;
    TickType_t lastWakeTime = xTaskGetTickCount();

    while (1) {
        while (gpioRead(taskParam->btn) == TRUE)
            vTaskDelayUntil(&lastWakeTime, period);
        TickType_t start = xTaskGetTickCount();
        while (gpioRead(taskParam->btn) == FALSE)
            vTaskDelayUntil(&lastWakeTime, period);
        TickType_t end = xTaskGetTickCount();
        if (end > start) {
            TickType_t elapsed = end - start;

            char *s = malloc(15);
            if (s == NULL) {
                // Out of memory?
                continue;
            }
            snprintf(s, 15, "%s %d", taskParam->name, elapsed);
            xQueueSend(*taskParam->sink, &s, portMAX_DELAY);
        }
    }
}

