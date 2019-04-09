//
// Created by 杨光 on 2019/3/27.
//

#ifndef DATA_STRUCTURE_LINKED_STACK_H
#define DATA_STRUCTURE_LINKED_STACK_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct linked_stack_node {

    _p_adt p_ad;
    struct linkded_stack_node *p_next;

} _linked_stack_node, *_p_linked_stack_node;

typedef struct linked_stack {

    _p_linked_stack_node top;
    _p_func_adt_assigns adt_assigns;
} _linked_stack, *_p_linked_stack;

_p_linked_stack linked_stack_init(_p_func_adt_assigns adt_assigns);

_p_linked_stack linked_stack_push(_p_linked_stack p_linked_stack, _p_adt p_ad);

_p_adt linked_stack_pop(_p_linked_stack p_linked_stack);

_p_adt linked_stack_top(_p_linked_stack p_linked_stack);

#endif //DATA_STRUCTURE_LINKED_STACK_H
