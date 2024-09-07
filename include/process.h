//
// Created by peter on 2024.08.14..
//

#ifndef OS_PROCESS_H
#define OS_PROCESS_H

#endif //OS_PROCESS_H

#define STACK_SIZE 256
#define PENDSVANDSYSTICKPRIO   _u(0xc0b00000)


typedef void (*process_function)(void);

typedef struct{

    volatile unsigned int sp;
    unsigned int stack[STACK_SIZE];
    void (*function)(void);
    int status;


} process_context;



typedef struct{

    //linked list?
    process_context tasks[10];

    unsigned int task_stacks[5][STACK_SIZE];
    unsigned int *stacks[5];

    unsigned  int task_count;
    unsigned  int current_task;

}process_table;

//void setPSP(unsigned int *stack);
unsigned int setPSP(unsigned int *stack);

void done();

/***
 *
 *
 * @param n
 */
void os_systick_config(unsigned int n);


/***
 *
 * @param stack
 * @param pointer_to_task_function
 * @return
 */
unsigned int *initialize_stack(unsigned int *stack,  void (*pointer_to_task_function)(void));

/***
 *
 * @param pointer_to_task_function
 * @return
 */
int create_task(void (*pointer_to_task_function)(void));


/***
 *
 */
void os_init();

/***
 *
 * @param stack
 * @return
 */
unsigned int * kernel_to_process(unsigned int *stack);


/***
 *
 * @param stack
 */
void os_task_init_stack(unsigned int *stack);

/***
 *
 */
void os_task_init(void);

/***
 *
 */
void os_start();

void blink_test();
void blink_test2();
void blink_test3();

void print_test();
void print_test2();
