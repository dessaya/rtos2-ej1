#ifndef LED_H
#define LED_H

#include "FreeRTOS.h"
#include "queue.h"
#include "sapi.h"

typedef struct {
    gpioMap_t led;
    QueueHandle_t *sink;
} ledTaskParam_t;

void ledTask(void *param);

#endif
