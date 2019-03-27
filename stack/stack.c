//
// Created by 杨光 on 2019/3/27.
//

#include <stddef.h>
#include "stack.h"

extern _p_memory_pool p_memory_pool;

static const unsigned _DEFAULT_STACK_CAPACITY_ = 32;

_p_stack stack_init() {

    if (p_memory_pool != NULL) {

        _p_stack p_stack = alloc_memory(p_memory_pool, sizeof(_stack));

        p_stack->top = -1;
        p_stack->capacity = _DEFAULT_STACK_CAPACITY_;
        p_stack->array = alloc_memory(p_memory_pool, p_stack->capacity * sizeof(_p_adt));

        return p_stack;
    }
    return NULL;
}

_p_adt stack_pop(_p_stack p_stack) {

    if (p_stack != NULL && p_stack->top >= 0) {

        return p_stack->array[p_stack->top--];
    }

    return NULL;
}

_p_stack stack_push(_p_stack p_stack, _p_adt p_ad) {

    if (p_stack != NULL && p_ad != NULL) {

        p_stack->array[++p_stack->top] = p_ad;
        return p_stack;
    }

    return NULL;
}

_p_adt stack_top(_p_stack p_stack) {

    if (p_stack != NULL && p_stack->top >= 0) {

        return p_stack->array[p_stack->top];
    }

    return NULL;
}

