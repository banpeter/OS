//
// Created by peter on 2024.09.07..
//

#include "ipc.h"

shared_memory shrm;

unsigned int* access_memory(){

    return shrm.memory;
}


