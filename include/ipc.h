//
// Created by peter on 2024.09.07..
//

#ifndef OS_IPC_H
#define OS_IPC_H

#endif //OS_IPC_H



typedef struct{

    unsigned int memory[10];
}shared_memory;


unsigned int* access_memory();
void write_memory();
