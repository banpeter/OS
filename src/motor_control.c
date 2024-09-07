//
// Created by peter on 2024.09.06..
//



#include "motor_control.h"



void setup_motor_controll_gpio(){


    gpio_init(0);
    gpio_init(28);

    gpio_init(4);
    gpio_init(5);
    gpio_init(27);
    gpio_init(26);

    gpio_init(17);
    gpio_init(15);

    gpio_init(16);
    gpio_init(18);
    gpio_init(14);
    gpio_init(13);


    gpio_set_function(0,GPIO_FUNC_PWM);
    gpio_set_function(28,GPIO_FUNC_PWM);
    gpio_set_function(17,GPIO_FUNC_PWM);
    gpio_set_function(15,GPIO_FUNC_PWM);

    gpio_set_dir(4, GPIO_OUT);
    gpio_set_dir(5, GPIO_OUT);
    gpio_set_dir(27, GPIO_OUT);
    gpio_set_dir(26, GPIO_OUT);



    gpio_set_dir(16, GPIO_OUT);
    gpio_set_dir(18, GPIO_OUT);
    gpio_set_dir(14, GPIO_OUT);
    gpio_set_dir(13, GPIO_OUT);

}


void forward(int second){



    gpio_put(4,0);
    gpio_put(5,1);

    gpio_put(27,1);
    gpio_put(26,0);

    gpio_put(16,0);
    gpio_put(18,1);

    gpio_put(14,1);
    gpio_put(13,0);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_numFrontA = pwm_gpio_to_slice_num(0);
    // Set period of 100 cycles (0 to 99 inclusive)
    pwm_set_wrap(slice_numFrontA, 99);
    // Set channel A output high for 30 cycle before dropping
    pwm_set_chan_level(slice_numFrontA, PWM_CHAN_A, 15);//30
    // Set the PWM running
    pwm_set_enabled(slice_numFrontA, true);


    uint slice_numFrontB = pwm_gpio_to_slice_num(28);
    pwm_set_wrap(slice_numFrontB, 99);
    pwm_set_chan_level(slice_numFrontB, PWM_CHAN_A, 15);
    pwm_set_enabled(slice_numFrontB, true);

    uint slice_numRearA = pwm_gpio_to_slice_num(17);
    pwm_set_wrap(slice_numRearA, 99);
    pwm_set_chan_level(slice_numRearA, PWM_CHAN_B, 15);
    pwm_set_enabled(slice_numRearA, true);

    uint slice_numRearB = pwm_gpio_to_slice_num(15);
    pwm_set_wrap(slice_numRearB, 99);
    pwm_set_chan_level(slice_numRearB, PWM_CHAN_B, 15);
    pwm_set_enabled(slice_numRearB, true);

    //1 sec = robot length

    sleep_ms(1000);//1000
    pwm_set_enabled(slice_numFrontA, false);
    pwm_set_enabled(slice_numFrontB, false);
    pwm_set_enabled(slice_numRearA, false);
    pwm_set_enabled(slice_numRearB, false);

    gpio_put(4,0);
    gpio_put(5,0);
    gpio_put(27,0);
    gpio_put(26,0);
    gpio_put(16,0);
    gpio_put(18,0);
    gpio_put(14,0);
    gpio_put(13,0);

    //multicore_fifo_push_blocking(1);
}

void turn_right(){

    gpio_put(4,1);
    gpio_put(5,0);

    gpio_put(27,1);
    gpio_put(26,0);

    gpio_put(16,0);
    gpio_put(18,1);

    gpio_put(14,0);
    gpio_put(13,1);


    uint slice_numFrontA = pwm_gpio_to_slice_num(0);
    pwm_set_wrap(slice_numFrontA, 2);
    pwm_set_chan_level(slice_numFrontA, PWM_CHAN_A, 3);
    pwm_set_enabled(slice_numFrontA, true);


    uint slice_numFrontB = pwm_gpio_to_slice_num(28);
    pwm_set_wrap(slice_numFrontB, 2);
    pwm_set_chan_level(slice_numFrontB, PWM_CHAN_A, 3);
    pwm_set_enabled(slice_numFrontB, true);

    uint slice_numRearA = pwm_gpio_to_slice_num(17);
    pwm_set_wrap(slice_numRearA, 2);
    pwm_set_chan_level(slice_numRearA, PWM_CHAN_B, 3);
    pwm_set_enabled(slice_numRearA, true);


    uint slice_numRearB = pwm_gpio_to_slice_num(15);
    pwm_set_wrap(slice_numRearB, 2);
    pwm_set_chan_level(slice_numRearB, PWM_CHAN_B, 3);
    pwm_set_enabled(slice_numRearB, true);

    sleep_ms(1200);
    pwm_set_enabled(slice_numFrontA, false);
    pwm_set_enabled(slice_numFrontB, false);
    pwm_set_enabled(slice_numRearA, false);
    pwm_set_enabled(slice_numRearB, false);

    gpio_put(4,0);
    gpio_put(5,0);
    gpio_put(27,0);
    gpio_put(26,0);
    gpio_put(16,0);
    gpio_put(18,0);
    gpio_put(14,0);
    gpio_put(13,0);


}

