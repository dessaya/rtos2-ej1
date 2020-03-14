#ifndef FREE_H
#define FREE_H

#include "FreeRTOS.h"
#include "queue.h"

typedef struct {
    QueueHandle_t *source;
} freeTaskParam_t;

void freeTask(void *param);

#endif
