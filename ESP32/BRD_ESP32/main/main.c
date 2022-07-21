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

#include "iot_servo.h"

//Pinos
#define SERVO_CH0_PIN 14
#define SERVO_CH1_PIN 27
#define SERVO_CH2_PIN 26
#define SERVO_CH3_PIN 25

#define ESP32Buzzer 15

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
            
        ESP_LOGI("INFO", "Aumentando");
        vTaskDelay(100 / portTICK_RATE_MS);
    }
    for (angle = 180; angle > 0; angle--)
    {
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, leg_right, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, leg_left, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_right, angle);
        iot_servo_write_angle(LEDC_LOW_SPEED_MODE, foot_left, angle);

        ESP_LOGI("INFO", "Diminuindo");
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

//buzzer
const uint16_t notes[]  ={
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
	vTaskDelay(pdMS_TO_TICKS(dur_hms*100));
	ledc_stop(LEDC_HIGH_SPEED_MODE,LEDC_HS_CH0_CHANNEL,0);
}

void app_main(void)
{
    iot_servo_init(LEDC_LOW_SPEED_MODE, &servo_cfg);
    
    while(1)
    {
        //motores_teste();

        esp32_beep(10, 10);
        esp32_beep(50, 20);
        esp32_beep(80, 30);
        esp32_beep(100, 20);
    }
}
