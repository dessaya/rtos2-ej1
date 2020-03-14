#include <stdlib.h>
#include "dummy.h"

#define MSG_SIZE 20

void dummyTask(void *param)
{
    dummyTaskParam_t *taskParam = param;
    char *msg = malloc(MSG_SIZE);
    if (!msg) {
        return;
    }
    while (1) {
        msgQueue_receive(*taskParam->source, msg, MSG_SIZE);
    }
}

