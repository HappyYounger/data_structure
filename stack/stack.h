//
// Created by 杨光 on 2019/3/27.
//

#ifndef DATA_STRUCTURE_STACK_H
#define DATA_STRUCTURE_STACK_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct stack {

    int top;
    unsigned capacity;
    _p_adt *array;

} _stack, *_p_stack;

_p_stack stack_init();

_p_stack stack_extend(_p_stack p_stack);

_p_adt stack_pop(_p_stack p_stack);

_p_stack stack_push(_p_stack p_stack, _p_adt p_ad);

_p_adt stack_top(_p_stack p_stack);


#endif //DATA_STRUCTURE_STACK_H
