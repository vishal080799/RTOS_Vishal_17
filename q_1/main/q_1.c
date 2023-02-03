#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

const TickType_t xDelay1 =1000/ portTICK_PERIOD_MS;

static int taskcore=1;
TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;
TaskHandle_t third_task_handle;
TaskHandle_t fourth_task_handle;
TaskHandle_t fifth_task_handle;

QueueHandle_t message_queue_handle;

UBaseType_t msg_size=64, queue_size=4;

void first_task(void *data)
{

        printf("Task1: Started\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
        vTaskDelete(NULL);
        
    

}

void second_task(void *data)
{
   
        printf("Task2: Started\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
        vTaskDelete(NULL);
}
  

void third_task(void *data)
{

        printf("Task3: Started\n");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        vTaskDelete(NULL);
        
    
}

void fourth_task(void *data)
{
    printf("Task4: Started\n");
    static int count =0;
while(1)
   {
    count++;
    xQueueSend(message_queue_handle,&count,xDelay1);
   vTaskDelay(xDelay1);
   }
   vTaskDelete(NULL);
}

void fifth_task(void *data)
{
    int buffer=0;
    int count=0;

     printf("Task5: Started\n");
    while(1)
    {
        xQueueReceive(message_queue_handle,&buffer,xDelay1);
        printf("Task5:received data:%d\n",buffer);
    
    count++;
    if(count>50)
    {
        count=0;
        
        vTaskDelay(xDelay1);
    }
    }
   vTaskDelete(NULL);

    
        
    }





void app_main()
{
    printf("App_main: Started\n");

     message_queue_handle = xQueueCreate(queue_size,msg_size);

    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,5,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,6,&second_task_handle,taskcore);
    xTaskCreatePinnedToCore(third_task,"thirdtask",2048,NULL,7,&third_task_handle,taskcore);
    xTaskCreatePinnedToCore(fourth_task,"fourthdtask",2048,NULL,8,&fourth_task_handle,taskcore);
    xTaskCreatePinnedToCore(fifth_task,"fifthtask",2048,NULL,9,&fifth_task_handle,taskcore);
}
