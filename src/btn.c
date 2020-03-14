#include <stdlib.h>
#include "btn.h"
#include "task.h"

#define MSG_SIZE 15

void btnTask(void *param)
{
    btnTaskParam_t *taskParam = param;

    TickType_t period =  10 / portTICK_RATE_MS;
    TickType_t lastWakeTime = xTaskGetTickCount();

    char *msg = malloc(MSG_SIZE);
    if (!msg) {
        return;
    }

    while (1) {
        while (gpioRead(taskParam->btn) == TRUE)
            vTaskDelayUntil(&lastWakeTime, period);
        TickType_t start = xTaskGetTickCount();
        while (gpioRead(taskParam->btn) == FALSE)
            vTaskDelayUntil(&lastWakeTime, period);
        TickType_t end = xTaskGetTickCount();
        if (end > start) {
            TickType_t elapsed = end - start;

            snprintf(msg, MSG_SIZE, "%s %d", taskParam->name, elapsed);
            msgQueue_send(*taskParam->sink, msg);
        }
    }
}

