//
// Created by 杨光 on 2019/3/5.
//
#ifndef DATA_STRUCTURE_SAMPLE_GLOBAL_VAR_H
#define DATA_STRUCTURE_SAMPLE_GLOBAL_VAR_H


#include "pool/pool.h"

#define QUEEN_COUNT 8
#define RANDOM_COUNT 20

#define EQ_INIT_MARK 'X'
#define EQ_INVALID_MARK '#'
#define EQ_QUEEN_MARK 'Q'
#define WHITE_CHAR ' '

_p_memory_pool init_mem_pool();

void destroy_mem_pool();

#endif //DATA_STRUCTURE_SAMPLE_GLOBAL_VAR_H
