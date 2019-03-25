#include <stdio.h>
#include "global.h"
#include "pool/pool.h"

void pool_test();


int main() {

    pool_test();
    return 0;
}

void pool_test() {

    _p_memory_pool p_pool = init_pool();
    printf("hello my memory pool\n");


    destroy_pool(p_pool);
}