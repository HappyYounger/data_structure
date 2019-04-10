#include <stdio.h>
#include "global.h"
#include "pool/pool.h"
#include "list/list.h"

extern _p_memory_pool p_memory_pool;

void print_data_int(_p_adt p_ad);

void pool_test() {


    _p_adt p_ad_array = pick_some_ad(3);
//    int *p_int_array = alloc_memory(p_memory_pool, sizeof(int) * 3);


    free_data(p_memory_pool, p_ad_array);
//    free_data(p_memory_pool, p_int_array);
}


static void list_test() {

    unsigned size = 4;
    _p_list p_list = list_init(16, NULL, NULL, NULL, NULL);

    _p_adt p_ad = pick_some_ad(size);
    int *p_int_array = alloc_memory(p_memory_pool, sizeof(int) * size);

    for (int j = 0; j < size; ++j) {

        p_ad[j].data = p_int_array + j;
        *(p_int_array + j) = j * 2;
    }

    for (int i = 0; i < 3; ++i) {

        list_append(p_list, p_ad + i);
    }

    list_insert(p_list, 1, p_ad + 3);

    list_remove_at(p_list, 2);
    list_remove_at(p_list, 1);

    int index = list_find(p_list, p_ad + 2);

    printf("%d\n", index);

    list_print(p_list, print_data_int);

    list_clear(p_list);
}

static void tree_test() {


}

unsigned count_test(unsigned x) {

    static unsigned count = 0;

    if (x > 0) {

        count++;
        count_test(--x);
    }

    return count;
}

int main() {

    p_memory_pool = init_memory_pool();
    //memory pool test
//    pool_test();
    list_test();
    destroy_pool(p_memory_pool);

//    unsigned count = count_test(262094);//max value 262094 for iteration
//    printf("%d\n", count);
    return 0;
}


void print_data_int(_p_adt p_ad) {

    if (p_ad != NULL && p_ad->data != NULL) {

        printf("%d\n", *((int *) p_ad->data));
    }
}

