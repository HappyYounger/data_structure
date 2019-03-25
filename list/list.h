//
// Created by 杨光 on 2019/3/25.
//

#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "../adt/adt.h"

typedef struct {

    unsigned size;
    unsigned capacity;
    _p_adt list;

    _p_func_adt_assigns adt_assigns;
    _p_func_adt_equals adt_equals;

} _list, *_p_list;

_p_list list_init(unsigned list_capacity,
                  _p_func_adt_assigns adt_assigns,
                  _p_func_adt_equals adt_equals);

void list_destroy(_p_list p_list);

_p_list list_extend(_p_list p_list);

unsigned list_find(_p_list p_list, _p_adt p_ad);

unsigned list_remove(_p_list p_list, _p_adt p_ad);

void list_remove_at(_p_list p_list, unsigned index);

void list_remove_ad_if(_p_list p_list, _p_func_if p_func_if);

void list_insert(_p_list p_list, unsigned index, _p_adt p_ad);

void list_append(_p_list p_list, _p_adt p_ad);

void list_clear(_p_list p_list);

void list_move(_p_list p_list, unsigned from, unsigned to);

void list_copy(_p_list p_list, void *des, void *src, unsigned size);

void list_print(_p_list p_list, _p_func_print p_func_print);


#endif //DATA_STRUCTURE_LIST_H
