#include <stdlib.h>
#include <string.h>
#include "msg.h"

msgQueue_t *msgQueue_create() {
    msgQueue_t *m = malloc(sizeof(msgQueue_t));
    if (!m) {
        return NULL;
    }

    m->queue = xQueueCreate(QUEUE_LENGTH, sizeof(char *));
    if (!m->queue) {
        free(m);
        return NULL;
    }

    return m;
}

bool msgQueue_send(msgQueue_t *m, const char *msg) {
    char *buf = malloc(strlen(msg) + 1);
    if (!buf) return false;
    strcpy(buf, msg);
    xQueueSend(m->queue, &buf, portMAX_DELAY);
    return true;
}

void msgQueue_receive(msgQueue_t *m, char msg[], size_t size) {
    char *buf;
    if (xQueueReceive(m->queue, &buf, portMAX_DELAY) != pdPASS) {
        msg[0] = '\0';
        return;
    }
    strncpy(msg, buf, size);
    msg[size - 1] = '\0'; // just in case buf is larger than msg
    free(buf);
}

void msgQueue_destroy(msgQueue_t *m) {
    vQueueDelete(m->queue);
    free(m);
}

