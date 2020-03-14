#include "btn.h"
#include "led.h"
#include "print.h"
#include "dummy.h"

#include "task.h"

/*
    btnTask1 \
    btnTask2 ---> m1 --> printTask --> m2 --> dummyTask
    ledTask  /
*/

static msgQueue_t *m1;
static msgQueue_t *m2;

static btnTaskParam_t btnTaskParam1 = {
    .btn = TEC1,
    .name = "TEC1",
    .sink = &m1,
};
static btnTaskParam_t btnTaskParam2 = {
    .btn = TEC2,
    .name = "TEC2",
    .sink = &m1,
};
static ledTaskParam_t ledTaskParam = {
    .led = LED1,
    .sink = &m1,
};
static printTaskParam_t printTaskParam = {
    .source = &m1,
    .sink = &m2,
};
static dummyTaskParam_t dummyTaskParam = {
    .source = &m2,
};

int main(void)
{
    boardInit();

    m1 = msgQueue_create();
    if (m1 == NULL) goto error;

    m2 = msgQueue_create();
    if (m2 == NULL) goto error;

    if (xTaskCreate(btnTask, "btnTask1", configMINIMAL_STACK_SIZE * 2, &btnTaskParam1, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(btnTask, "btnTask2", configMINIMAL_STACK_SIZE * 2, &btnTaskParam2, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(ledTask, "ledTask", configMINIMAL_STACK_SIZE * 2, &ledTaskParam, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(printTask, "printTask", configMINIMAL_STACK_SIZE * 2, &printTaskParam, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    if (xTaskCreate(dummyTask, "dummyTask", configMINIMAL_STACK_SIZE * 2, &dummyTaskParam, tskIDLE_PRIORITY + 1, 0) != pdPASS)
        goto error;

    vTaskStartScheduler();

    error:
    while( true )
        ;

    return 0;
}
