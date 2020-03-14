#ifndef PRINT_H
#define PRINT_H

#include "msg.h"

typedef struct {
    msgQueue_t **source;
    msgQueue_t **sink;
} printTaskParam_t;

void printTask(void *param);

#endif
