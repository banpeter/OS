//
// Created by peter on 2024.08.12..
//

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include "process.h"

#include "pico/cyw43_arch.h"

#include "hardware/structs/systick.h"
#include "hardware/sync.h"
#include "ipc.h"

process_table pcb;
//volatile process_context *current_task;
//volatile process_context *next_task;


volatile unsigned int **current_task_ptr;

volatile unsigned int *current_task;
volatile unsigned int *next_task;






void os_systick_config(unsigned int n) {

    /* Stop systick and cancel it if it is pending */
    systick_hw->csr = 0;    // Disable timer and IRQ
    __dsb();                // make sure systick is disabled
    __isb();                // and it is really off

    // clear the systick exception pending bit if it got set
    hw_set_bits  ((io_rw_32 *)(PPB_BASE + M0PLUS_ICSR_OFFSET),M0PLUS_ICSR_PENDSTCLR_BITS);

    systick_hw->rvr = (n) - 1UL;    // set the reload value
    systick_hw->cvr = 0;    // clear counter to force reload
    systick_hw->csr = 0x03; // arm IRQ, start counter with 1 usec clock


}

void done(){
    printf("Done\n");
}


unsigned int *initialize_stack(unsigned int *stack,  void (*pointer_to_task_function)(void)){

    /*
    Exception frame saved by the NVIC hardware onto stack:
    +------+
    |      | <- SP before interrupt (orig. SP)
    | xPSR |
    |  PC  |
    |  LR  |
    |  R12 |
    |  R3  |
    |  R2  |
    |  R1  |
    |  R0  | <- SP after entering interrupt (orig. SP + 32 bytes)
    +------+

    Registers saved by the software (PendSV_Handler):
    +------+
    |  R7  |
    |  R6  |
    |  R5  |
    |  R4  |
    |  R11 |
    |  R10 |
    |  R9  |
    |  R8  | <- Saved SP (orig. SP + 64 bytes)
    +------+
    */

    stack += STACK_SIZE - 16;
    stack[15] = (unsigned int) 0x01000000;
    stack[14] = (unsigned int) pointer_to_task_function;
    stack[13] = (unsigned int) &done; //Default value of xPSR (Thumb mode, no interrupt)

    printf("Task created with address : 0x%08lx\n",  stack);
    return stack;

}

int create_task(void (*pointer_to_task_function)(void)){

    if(pcb.task_count >= 5){
        return -1;
    }

    pcb.stacks[pcb.task_count] = initialize_stack(pcb.task_stacks[pcb.task_count],pointer_to_task_function);
    pcb.tasks[pcb.task_count].function = pointer_to_task_function;

    pcb.task_count++;
    return pcb.task_count - 1;

}

void os_init() {
    pcb.task_count = 0;
    stdio_init_all();

    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_SHPR2_OFFSET), M0PLUS_SHPR2_BITS);
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_SHPR3_OFFSET), PENDSVANDSYSTICKPRIO);

}


void isr_systick();

void isr_systick(){
    systick_hw->csr = 0;



    printf("Systick\n");
    pcb.current_task++;

    if (pcb.current_task >= pcb.task_count){
        pcb.current_task = 0;
    }

    next_task = pcb.stacks[pcb.current_task];
    systick_hw->csr = 0x03;
    hw_set_bits((io_rw_32 *)(PPB_BASE + M0PLUS_ICSR_OFFSET), M0PLUS_ICSR_PENDSVSET_BITS);




}



void os_start() {

    printf("Start...\n");
    sleep_ms(500);

    pcb.current_task  = 0;


    while (1) {
        os_systick_config(2500000);
        printf("Systick done\n");
        sleep_ms(500);


        unsigned  int a = setPSP(pcb.stacks[pcb.current_task] + 16);
        printf("setPSP done 0x%08lx\n",a);
        pcb.tasks[pcb.current_task].function();


        printf("Kernel\n");





    }

}


int main() {



    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(1000);

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(1000);

    os_init();
    printf("\ninit done\n");//check
    create_task(&blink_test);
    printf("Task one created\n");
    create_task(&blink_test3);
    printf("Task two created\n");
    create_task(&print_test);
    printf("Task three created\n");
    create_task(&print_test2);
    printf("Task four created\n");
    os_start();


}


void print_test(){


    unsigned int* shr = access_memory();
    shr[0] = 5;

    while(true){
        shr = access_memory();
        printf("Test 1 %d\n",shr[0]);
        sleep_ms(1000);
    }
}


void print_test2(){
    unsigned int* shr;
    while(true){
        shr = access_memory();
        printf("TEst2 %d\n",shr[0]);
        //printf("test2\n");
        sleep_ms(1000);
    }
}





void blink_test(){
    printf("blink_test \n") ;
    int i = 0;
    while(true){

        i++;
        //printf("blink_test CSR: 0x%08lx, RVR: %lu, CVR: %lu\n",systick_hw->csr, systick_hw->rvr, systick_hw->cvr);
        //printf("test1: %d\n",i);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(1000);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1000);


    }
}

void blink_test2(){
    printf("blink_test2 \n") ;
    int i = 0     ;
    while(true){
        i++;
        printf("test2: %d\n",i);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }
}


void blink_test3(){
    printf("blink_test3 \n") ;
    int i = 0     ;
    while(true){
        i++;
        printf("test2: %d\n",i);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
    }
}


