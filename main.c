#include <stdio.h>
#include "global.h"
#include "pool/pool.h"
#include "list/list.h"
#include "list/linked_list.h"

void print_data_int(_p_adt p_ad);

void print_data_int_array(_p_adt p_ad, unsigned size);

void pool_test() {

    unsigned n = 3;
    _p_adt p_ad_array = get_ads(n, sizeof(int));

    int *p_int_array = alloc_memory(sizeof(int) * n);

    for (int i = 0; i < n; ++i) {

        p_int_array[i] = i * 2;
        p_ad_array[i].data = p_int_array + i;
        p_ad_array[i].bytes = sizeof(int);
    }


    print_data_int_array(p_ad_array, n);

    free_data(p_ad_array);
    free_data(p_int_array);
}

static void list_test() {

    unsigned size = 4;
    _p_list p_list = list_init(16, NULL, NULL, NULL, NULL);

    _p_adt p_ad = get_ads(size, sizeof(int));
    int *p_int_array = alloc_memory(sizeof(int) * size);

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

static void linked_list_test() {

    unsigned size = 4;

    _p_linked_list p_linked_list = linked_list_init(NULL, NULL, NULL, NULL);
    _p_adt p_ad = get_ads(size, sizeof(int));

    int *p_int_array = alloc_memory(sizeof(int) * size);

    for (int j = 0; j < size; ++j) {

        p_ad[j].data = p_int_array + j;
        *(p_int_array + j) = j * 2;
    }

    for (int i = 0; i < 1; ++i) {

        linked_list_insert_first_after(p_linked_list, p_ad + i);
    }

    linked_list_insert_last_before(p_linked_list, p_ad + 2);
    linked_list_insert_first_before(p_linked_list, p_ad + 1);
    linked_list_insert_last_after(p_linked_list, p_ad + 3);

    _p_adt p_ad1 = get_ads(1, sizeof(int));
    int *p_int1 = alloc_memory(sizeof(int));
    *p_int1 = 100;
    p_ad1->data = p_int1;

    linked_list_insert_after(p_linked_list, p_ad + 1, p_ad1);

    linked_list_remove(p_linked_list, p_ad1);

    print_linked_list(p_linked_list, print_data_int);
    return;

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

    _p_memory_pool pool = init_pool();

//    pool_test();
//    list_test();

    linked_list_test();
    destroy_pool(pool);

//    unsigned count = count_test(262094);//max value 262094 for iteration
//    printf("%d\n", count);
    return 0;
}


void print_data_int(_p_adt p_ad) {

    if (p_ad != NULL && p_ad->data != NULL) {

        printf("%d\n", *((int *) p_ad->data));
    }
}

void print_data_int_array(_p_adt p_ad, unsigned size) {

    for (int i = 0; i < size; ++i) {

        print_data_int(p_ad + i);
    }
}
