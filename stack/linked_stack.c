//
// Created by 杨光 on 2019/3/27.
//

#include "linked_stack.h"
#include <stddef.h>

_p_linked_stack linked_stack_init() {

    _p_linked_stack p_linked_stack = alloc_memory(sizeof(struct linked_stack));

    if (p_linked_stack != NULL) {

        p_linked_stack->top = NULL;
    }

    return NULL;
}

_p_linked_stack linked_stack_push(_p_linked_stack p_linked_stack, _p_adt p_ad) {

    if (p_linked_stack != NULL && p_ad != NULL) {

        _p_linked_stack_node p_linked_stack_node = alloc_memory(sizeof(struct linked_stack_node));

        p_linked_stack_node->p_ad = p_ad;
        p_linked_stack_node->p_next = p_linked_stack->top;
        p_linked_stack->top = p_linked_stack_node;

        return p_linked_stack;
    }

    return NULL;
}

_p_adt linked_stack_pop(_p_linked_stack p_linked_stack) {

    if (p_linked_stack != NULL && p_linked_stack->top != NULL) {

        _p_adt p_ad = p_linked_stack->top->p_ad;
        _p_linked_stack_node new_top = p_linked_stack->top->p_next;
        p_linked_stack->top->p_next = NULL;
        p_linked_stack->top = new_top;
        return p_ad;
    }

    return NULL;
}

_p_adt linked_stack_top(_p_linked_stack p_linked_stack) {

    if (p_linked_stack != NULL && p_linked_stack->top != NULL) {

        return p_linked_stack->top->p_ad;
    }
    return NULL;
}