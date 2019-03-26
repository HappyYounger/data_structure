//
// Created by 杨光 on 2019/3/25.
//

#ifndef DATA_STRUCTURE_ADT_H
#define DATA_STRUCTURE_ADT_H

#include <stdbool.h>

typedef struct adt {

    void *data;
    unsigned bytes;
} _adt, *_p_adt;

typedef _p_adt (*_p_func_adt_assigns)(_p_adt p_ad1, _p_adt p_ad2);

typedef bool (*_p_func_adt_equals)(_p_adt p_ad1, _p_adt p_ad2);

typedef bool (*_p_func_if)(_p_adt p_ad);

typedef void (*_p_func_print)(_p_adt p_ad);

_p_adt adt_def_assigns(_p_adt p_ad1, _p_adt p_ad2);

bool adt_def_equals(_p_adt p_ad1, _p_adt p_ad2);

_p_adt pick_some_ad(unsigned number, unsigned bytes);

#endif //DATA_STRUCTURE_ADT_H
