//
// Created by peter on 2024.09.07..
//

#include "ultrasonic_sensor.h"


void set_ultrasonic_sensor(){

    gpio_init(2);
    gpio_init(3);
    gpio_set_dir(2,GPIO_OUT);
    gpio_set_dir(3,GPIO_IN);
}

void measure_distance(){

    gpio_put(2,1);
    sleep_us(10);
    gpio_put(2,0);

    while(gpio_get(3) == 0){
        tight_loop_contents();
    }
    absolute_time_t start_time = get_absolute_time();

    while(gpio_get(3) == 1){
        sleep_us(1);
    }

    absolute_time_t end_time = get_absolute_time();

    double cm = (double) absolute_time_diff_us(start_time,end_time);

    if(cm == 0){
        cm = 10;
    }
    else{
        cm = cm *  0.0344 / 2.0;
    }


}
