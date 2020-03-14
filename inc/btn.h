#ifndef BTN_H
#define BTN_H

#include "msg.h"
#include "sapi.h"

typedef struct {
    gpioMap_t btn;
    char name[5];
    msgQueue_t **sink;
} btnTaskParam_t;

void btnTask(void *param);

#endif
