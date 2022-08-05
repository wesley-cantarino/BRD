/*******************************
Projeto para a disciplina soft embarcado 2022.1

BRD - Best robot dance

Autores: Caio e Wesley 
*******************************/

//Bibliotecas
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/ledc.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_err.h"

#include "iot_servo.h"
#include "ultrasonic.h"

//Pinoss
#define SERVO_CH0_PIN 14
#define SERVO_CH1_PIN 25
#define SERVO_CH2_PIN 26
#define SERVO_CH3_PIN 27

#define ESP32Buzzer 15

float distance;
#define MAX_DISTANCE_CM 500 // 5m max
#define TRIGGER_GPIO 17 //rx2
#define ECHO_GPIO 16    //tx2

//Canais
#define LEDC_CHANNEL_0 1
#define LEDC_CHANNEL_1 2
#define LEDC_CHANNEL_2 3
#define LEDC_CHANNEL_3 4

#define LEDC_HS_CH0_CHANNEL 5

//Os canal dos motores
#define leg_right 1
#define leg_left 2
#define foot_right 3
#define foot_left 4

servo_config_t servo_cfg = {
    .max_angle = 180,
    .min_width_us = 500,
    .max_width_us = 2500,
    .freq = 50,
    .timer_number = LEDC_TIMER_0,
    .channels = {
        .servo_pin = {
            SERVO_CH0_PIN,
            SERVO_CH1_PIN,
            SERVO_CH2_PIN,
            SERVO_CH3_PIN,
        },
        .ch = {
            LEDC_CHANNEL_0,
            LEDC_CHANNEL_1,
            LEDC_CHANNEL_2,
            LEDC_CHANNEL_3,
        },
    },
    .channel_number = 4,
} ;




/******************start_FUNCOES_BASICAS******************/
//Testar os servos
void motores_teste()
{
    int angle = 0;
    for (angle = 0; angle < 180; angle++)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, leg_right, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, leg_left, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, angle);
            
        //ESP_LOGI("INFO", "Aumentando");
        vTaskDelay(100 / portTICK_RATE_MS);
    }
    for (angle = 180; angle > 0; angle--)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, leg_right, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, leg_left, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, angle);

        //ESP_LOGI("INFO", "Diminuindo");
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

//buzzer
//A frequência sonora da nota dó é de 264Hz //39
//A frequência sonora da nota ré é de 297Hz //41
//A frequência sonora da nota mi é de 330Hz //43
//A frequência sonora da nota fá é de 352Hz
//A frequência sonora da nota sol é de 396Hz
//A frequência sonora da nota lá é de 440Hz //48
//A frequência sonora da nota si é de 495Hz

const uint16_t notes[]  = {
	0,31,33,35,37,39,41,44,46,49,52,55,58,62,65,69,73,78,82,87,93,98,104,110,117,123,131,139,147,156,165,175,185,196,208,220,
	233,247,262,277,294,311,330,349,370,392,415,440,466,494,523,554,587,622,659,698,740,784,831,880,932,988,1047,1109,1175,1245,1319,1397,1480,1568,1661,
	1760,1865,1976,2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951,4186,4435,4699,4978};

void esp32_beep(unsigned char key_num, unsigned char dur_hms)
{
	ledc_timer_config_t ledc_timer;
	ledc_channel_config_t ledc_channel;

	ledc_timer.duty_resolution = LEDC_TIMER_13_BIT;	// resolution of PWM duty
	ledc_timer.freq_hz = notes[key_num];			// frequency of PWM signal
	ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;	// timer mode
	ledc_timer.timer_num = LEDC_TIMER_1;			// timer index

	// Set configuration of timer0 for high speed channels
	ledc_timer_config(&ledc_timer);
	
	ledc_channel.channel    = LEDC_HS_CH0_CHANNEL;
	ledc_channel.duty       = 4096;
	ledc_channel.gpio_num   = ESP32Buzzer;
	ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
	ledc_channel.hpoint     = 0;
	ledc_channel.timer_sel  = LEDC_TIMER_1;

	ledc_channel_config(&ledc_channel);
	vTaskDelay(pdMS_TO_TICKS(dur_hms*50)); //estava em 100
	ledc_stop(LEDC_HIGH_SPEED_MODE,LEDC_HS_CH0_CHANNEL,0);
}

ultrasonic_sensor_t sensor = {
        .trigger_pin = TRIGGER_GPIO,
        .echo_pin = ECHO_GPIO
};

void ultrasonic ()
{
    esp_err_t res = ultrasonic_measure(&sensor, MAX_DISTANCE_CM, &distance);
    if (res != ESP_OK)
    {
        printf("Error %d: ", res);
        switch (res)
        {
            case ESP_ERR_ULTRASONIC_PING:
                printf("Cannot ping (device is in invalid state)\n");
                break;
            case ESP_ERR_ULTRASONIC_PING_TIMEOUT:
                printf("Ping timeout (no device found)\n");
                break;
            case ESP_ERR_ULTRASONIC_ECHO_TIMEOUT:
                printf("Echo timeout (i.e. distance too big)\n");
                break;
            default:
                printf("%s\n", esp_err_to_name(res));
        }
    }
    else
        printf("Distance: %0.04f m\n", distance);
}

/******************END_FUNCOES_BASICAS******************/


void alongamento ()
{
    //subir
    printf("Subir\n");
    for (float ang = 83; ang < 160; ang = ang + 0.5)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
        vTaskDelay(50 / portTICK_RATE_MS);
    }

    //descer
    printf("Descer\n");
    for (float ang = 160; ang > 83; ang = ang - 0.5)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
        vTaskDelay(50 / portTICK_RATE_MS);
    }

    //subir
    printf("Subir\n");
    for (float ang = 83; ang > 20; ang = ang - 0.5)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
        vTaskDelay(50 / portTICK_RATE_MS);
    }

    //descer
    printf("Descer\n");
    for (float ang = 20; ang < 83; ang = ang + 0.5)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
        vTaskDelay(50 / portTICK_RATE_MS);
    }
}


#define BLINK_GPIO 2
#define BUTTON_GPIO 0

void task_alonga(void *pvParameters);
void task_sonzim(void *pvParameters);

QueueHandle_t alongaQ;


void app_main(void)
{
    iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);

    esp32_beep(39, 2);
    esp32_beep(43, 2);
    esp32_beep(50, 1);
    esp32_beep(55, 1);

    ultrasonic_init(&sensor);


    gpio_pad_select_gpio(BLINK_GPIO); // Configura o pino como IO
    gpio_set_direction(BLINK_GPIO,GPIO_MODE_OUTPUT); // Configura o IO como saida

    gpio_pad_select_gpio(BUTTON_GPIO); // Configura o pino como IO
    gpio_set_direction(BUTTON_GPIO,GPIO_MODE_INPUT); // Configura o IO como entrada

    alongaQ = xQueueCreate(2, sizeof(int));


    xTaskCreate(task_alonga,"Task alongamento",1024,NULL,1,NULL);
    xTaskCreate(task_sonzim,"Task buzer",1024,NULL,1,NULL);


}

void task_alonga(void *pvParameters)
{
    int i=0;
	
    for(;;)
    {
        xQueueReceive(alongaQ,&i,portMAX_DELAY);
		
        if(i==1)
        {
            printf("Alongando pra esquerda!!\r\n");
            for (float ang = 83; ang < 160; ang = ang + 0.5)
            {
                printf("ang ++\r\n");
                //iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
                //iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
                vTaskDelay(50 / portTICK_RATE_MS);
            }

            //descer
            printf("Descer\n");
            for (float ang = 160; ang > 83; ang = ang - 0.5)
            {
                printf("ang --\r\n");
                //iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
                //iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
                vTaskDelay(50 / portTICK_RATE_MS);
            }
        }
        /*
        else
        {
            printf("Alongando pra direita\n\r");

            //subir
            printf("Subir\n");
            for (float ang = 83; ang > 20; ang = ang - 0.5)
            {
        //         iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
        //         iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
                vTaskDelay(50 / portTICK_RATE_MS);
            }

        //     //descer
            printf("Descer\n");
            for (float ang = 20; ang < 83; ang = ang + 0.5)
            {
                //iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, ang);
                //iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, ang);
                vTaskDelay(50 / portTICK_RATE_MS);
            }
        }*/
		
        vTaskDelay(1);
    }
}

void task_sonzim(void *pvParameters)
{
    int i = 0;
    for(;;)
    {
        //while(gpio_get_level(BUTTON_GPIO) == 0){}

        printf("Som on!\r\n");
			
        i = rand()%2;
        
        //printf("val i is %d \n", i);

        xQueueSendToFront(alongaQ, &i,0);

        vTaskDelay(10);
        
    }
}
