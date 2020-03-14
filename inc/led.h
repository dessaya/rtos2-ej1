#ifndef LED_H
#define LED_H

#include "msg.h"
#include "sapi.h"

typedef struct {
    gpioMap_t led;
    msgQueue_t **sink;
} ledTaskParam_t;

void ledTask(void *param);

#endif
