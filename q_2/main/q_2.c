#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

const TickType_t xDelay1 =10000/ portTICK_PERIOD_MS;

TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;
TaskHandle_t third_task_handle;

TimerHandle_t timer_handle;

void vTimerCallback( TimerHandle_t timer_handle)
{  
    printf("Timer CallBack Function Called\n");

    const uint32_t Max= 10;
    uint32_t Count =0;
    while(1){

    Count++;
    if( Count >= Max )
    {
    xTimerStop( timer_handle, 0 );
    }
    else
    {
    vTimerSetTimerID( timer_handle, ( void * ) Count );
    printf("The Timer count %ld\n",Count);
    }
    }

}




void first_task(void *data)
{
    while(1)
    {
        printf("Task1: Started\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
        vTaskDelete(NULL);  
    }
}

void second_task(void *data)
{
    while(1)
    {
        printf("Task2: Started\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
        vTaskDelete(NULL);   
    }
}

void third_task(void *data)
{
    while(1)
    {
        printf("Task3: Started\n");

        xTimerStart(timer_handle,xDelay1);

        vTaskDelay(5000/portTICK_PERIOD_MS);

        vTaskDelete(NULL);
        
    }
}

void app_main()
{
    printf("App_main: Started\n");

    timer_handle = xTimerCreate("Software_timer",xDelay1,pdFALSE,0,vTimerCallback);

    
    
    xTaskCreate(first_task,"firsttask",2048,NULL,5,&first_task_handle);
    xTaskCreate(second_task,"secondtask",2048,NULL,6,&second_task_handle);
    xTaskCreate(third_task,"thirdtask",2048,NULL,7,&third_task_handle);
}