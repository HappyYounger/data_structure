//
// Created by 杨光 on 2019/3/5.
//

#include "pool/pool.h"

int count = 0;
_p_memory_pool p_memory_pool;

_p_memory_pool init_memory_pool() {

    p_memory_pool = init_pool();

    return p_memory_pool;
}

void destroy_mem_pool() {

    destroy_pool(p_memory_pool);
}