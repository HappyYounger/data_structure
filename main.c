#include <stdio.h>
#include "global.h"
#include "pool/pool.h"
#include "list/list.h"


void print_data_int(_p_adt p_ad);

bool equal_int(_p_adt p_ad1, _p_adt p_ad2);

_p_adt assign_int(_p_adt p_ad1, _p_adt p_ad2);

int main() {

    _p_memory_pool p_memory_pool = init_mem_pool();
    _p_list p_list = list_init(16, assign_int, equal_int);

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

    destroy_pool(p_memory_pool);
    return 0;
}


void print_data_int(_p_adt p_ad) {

    if (p_ad != NULL && p_ad->data != NULL) {

        printf("%d\n", (int) p_ad->data);
    }
}

bool equal_int(_p_adt p_ad1, _p_adt p_ad2) {

    if (p_ad1 != NULL && p_ad1 != NULL) {

        return p_ad1->data == p_ad2->data;
    }

    return false;
}

_p_adt assign_int(_p_adt p_ad1, _p_adt p_ad2) {

    if (p_ad1 != NULL && p_ad2 != NULL) {

        p_ad1->data = p_ad2->data;
        return p_ad1;
    }

    return NULL;
}
