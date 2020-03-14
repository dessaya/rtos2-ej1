#include "btn.h"
#include "led.h"
#include "print.h"
#include "free.h"

#include "task.h"

#define QUEUE_LENGTH 10

/*
    btnTask1 \
    btnTask2 ---> q1 --> printTask --> freeTask
    ledTask  /
*/

static QueueHandle_t q1;
static QueueHandle_t q2;
static btnTaskParam_t btnTaskParam1 = {.btn = TEC1, .name = "TEC1", .sink = &q1};
static btnTaskParam_t btnTaskParam2 = {.btn = TEC2, .name = "TEC2", .sink = &q1};
static ledTaskParam_t ledTaskParam = {.led = LED1, .sink = &q1};
static printTaskParam_t printTaskParam = {.source = &q1, .sink = &q2};
static freeTaskParam_t freeTaskParam = {.source = &q2};

int main(void)
{
    boardInit();

    q1 = xQueueCreate(QUEUE_LENGTH, sizeof(char *));
    if (q1 == NULL) goto error;

    q2 = xQueueCreate(QUEUE_LENGTH, sizeof(char *));
    if (q2 == NULL) goto error;

    if (xTaskCreate(btnTask, "btnTask1", configMINIMAL_STACK_SIZE * 2, &btnTaskParam1, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(btnTask, "btnTask2", configMINIMAL_STACK_SIZE * 2, &btnTaskParam2, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE * 2, &ledTaskParam, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(printTask, "printTask", configMINIMAL_STACK_SIZE * 2, &printTaskParam, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(freeTask, "freeTask", configMINIMAL_STACK_SIZE * 2, &freeTaskParam, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    vTaskStartScheduler();

    error:
    while( true )
        ;

    return 0;
}
