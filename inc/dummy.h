#ifndef DUMMY_H
#define DUMMY_H

#include "msg.h"

typedef struct {
    msgQueue_t **source;
} dummyTaskParam_t;

void dummyTask(void *param);

#endif
