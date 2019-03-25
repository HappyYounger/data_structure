//
// Created by 杨光 on 2019/3/25.
//

#include "list.h"
#include <stdlib.h>

static const int _ListCapacity = 16;

_p_list list_init(unsigned list_capacity,
                  _p_func_adt_assigns adt_assigns,
                  _p_func_adt_equals adt_equals) {

    _p_list p_list = malloc(sizeof(_list));

    if (p_list != NULL) {

        p_list->capacity = list_capacity < _ListCapacity ? _ListCapacity : list_capacity;

        p_list->list = malloc(sizeof(_p_adt) * p_list->capacity);

        p_list->adt_assigns = adt_assigns == NULL ? adt_def_assigns : adt_assigns;
        p_list->adt_equals = adt_equals == NULL ? adt_def_equals : adt_equals;
    }

    return NULL;
}