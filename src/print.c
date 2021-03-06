#include <stdlib.h>
#include <stdio.h>
#include "print.h"

#define MSG_SIZE 20

void printTask(void *param)
{
    printTaskParam_t *taskParam = param;
    char *msg = malloc(MSG_SIZE);
    if (!msg) {
        return;
    }
    while (1) {
        msgQueue_receive(*taskParam->source, msg, MSG_SIZE);
        puts(msg);
        msgQueue_send(*taskParam->sink, msg);
    }
}
