#ifndef BTN_H
#define BTN_H

#include "FreeRTOS.h"
#include "queue.h"
#include "sapi.h"

typedef struct {
    gpioMap_t btn;
    char name[5];
    QueueHandle_t *sink;
} btnTaskParam_t;

void btnTask(void *param);

#endif
