#ifndef MSG_H
#define MSG_H

#include "FreeRTOS.h"
#include "queue.h"

#define QUEUE_LENGTH 10

typedef struct {
    QueueHandle_t *queue;
} msgQueue_t;

msgQueue_t *msgQueue_create();
bool msgQueue_send(msgQueue_t *msgQueue, const char *msg);
void msgQueue_receive(msgQueue_t *msgQueue, char msg[], size_t size);
void msgQueue_destroy(msgQueue_t *msgQueue);

#endif
