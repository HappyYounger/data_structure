#include <stdio.h>
#include "global.h"
#include "pool/pool.h"
#include "list/list.h"


void print_data_int(_p_adt p_ad);

static void list_test() {

    _p_list p_list = list_init(16, NULL, NULL, NULL, NULL);

    _p_adt p_ad = pick_some_ad(4, sizeof(int));

    p_ad[0].data = 1;
    p_ad[1].data = 3;
    p_ad[2].data = 5;
    p_ad[3].data = 7;

    _p_adt p_ad1 = pick_some_ad(1, sizeof(int));

    p_ad1->data = 100;

    for (int i = 0; i < 4; ++i) {

        list_append(p_list, p_ad + i);
    }

    list_insert(p_list, 1, p_ad1);

    list_remove_at(p_list, 2);
    list_remove_at(p_list, 1);

    int index = list_find(p_list, p_ad + 2);

    printf("%d\n", index);

    list_print(p_list, print_data_int);

    list_clear(p_list);
}

static void tree_test();

unsigned count_test(unsigned x) {

    static unsigned count = 0;

    if (x > 0) {

        count++;
        count_test(--x);
    }

    return count;
}

int main() {

    _p_memory_pool p_memory_pool = init_mem_pool();
    list_test();
    destroy_pool(p_memory_pool);

//    unsigned count = count_test(262094);//max value 262094
//    printf("%d\n", count);
    return 0;
}


void print_data_int(_p_adt p_ad) {

    if (p_ad != NULL && p_ad->data != NULL) {

        printf("%d\n", (int) p_ad->data);
    }
}

