#include <stdio.h>
#include "print.h"

void printTask(void *param)
{
    printTaskParam_t *taskParam = param;
    while (1) {
        char *s;
        xQueueReceive(*taskParam->source, &s, portMAX_DELAY);
        puts(s);
        xQueueSend(*taskParam->sink, &s, portMAX_DELAY);
    }
}
