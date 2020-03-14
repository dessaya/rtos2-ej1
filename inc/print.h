#ifndef PRINT_H
#define PRINT_H

#include "FreeRTOS.h"
#include "queue.h"

typedef struct {
    QueueHandle_t *source;
    QueueHandle_t *sink;
} printTaskParam_t;

void printTask(void *param);

#endif
