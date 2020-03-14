#include <stdlib.h>
#include "free.h"

void freeTask(void *param)
{
    freeTaskParam_t *taskParam = param;
    while (1) {
        char *s;
        xQueueReceive(*taskParam->source, &s, portMAX_DELAY);
        free(s);
    }
}

