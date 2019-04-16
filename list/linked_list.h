//
// Created by 杨光 on 2019/3/25.
//

#ifndef DATA_STRUCTURE_LINKED_LIST_H
#define DATA_STRUCTURE_LINKED_LIST_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct linked_list_node {

    _p_adt p_ad;
    struct linked_list_node *p_previous;
    struct linked_list_node *p_next;
} _linked_list_node, *_p_linked_list_node;

typedef struct linked_list {

    unsigned size;
    _p_linked_list_node first;
    _p_linked_list_node last;
} _linked_list, *_p_linked_list;


_p_linked_list linked_list_init();

_p_linked_list_node linked_list_insert_before(_p_linked_list p_linked_list,
                                              _p_adt p_des_ad,
                                              _p_adt p_ad);

_p_linked_list_node linked_list_insert_after(_p_linked_list p_linked_list,
                                             _p_adt p_des_ad,
                                             _p_adt p_ad);

_p_linked_list_node linked_list_insert_first_before(_p_linked_list p_linked_list, _p_adt p_ad);

_p_linked_list_node linked_list_insert_first_after(_p_linked_list p_linked_list, _p_adt p_ad);

_p_linked_list_node linked_list_insert_last_before(_p_linked_list p_linked_list, _p_adt p_ad);

_p_linked_list_node linked_list_insert_last_after(_p_linked_list p_linked_list, _p_adt p_ad);

_p_linked_list_node linked_list_find_cond(_p_linked_list p_linked_list, _p_func_cond func_cond, _p_adt p_ad);

_p_linked_list linked_list_remove_cond(_p_linked_list p_linked_list, _p_func_cond func_cond, _p_adt p_ad);

_p_linked_list linked_list_clear(_p_linked_list p_linked_list);

void print_linked_list(_p_linked_list p_linked_list, _p_func_print p_func_print);

#endif //DATA_STRUCTURE_LINKED_LIST_H
