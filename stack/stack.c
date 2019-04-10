//
// Created by 杨光 on 2019/3/27.
//

#include <stddef.h>
#include "stack.h"

static const unsigned _DEFAULT_STACK_CAPACITY_ = 32;

_p_stack stack_init(_p_func_adt_assigns adt_assigns, _p_func_adt_bits_assigns adt_bits_assigns) {

    _p_stack p_stack = alloc_memory(sizeof(_stack));

    if (p_stack != NULL) {

        p_stack->top = -1;
        p_stack->capacity = _DEFAULT_STACK_CAPACITY_;
        p_stack->array = alloc_memory(p_stack->capacity * sizeof(_p_adt));

        p_stack->adt_assigns = assigns_func(adt_assigns);
        p_stack->adt_bits_assigns = bits_assigns_func(adt_bits_assigns);
    }
    return p_stack;
}

_p_adt stack_pop(_p_stack p_stack) {

    if (p_stack != NULL && p_stack->top > -1) {

        return p_stack->array[p_stack->top--];
    }

    return NULL;
}

_p_stack stack_push(_p_stack p_stack, _p_adt p_ad) {

    if (p_stack != NULL && p_ad != NULL) {

        if (p_stack->top == p_stack->capacity - 1) {

            p_stack = stack_extend(p_stack);
        }

        if (p_stack != NULL) {

            p_stack->array[++p_stack->top] = p_ad;
        }
        return p_stack;
    }

    return NULL;
}

_p_adt stack_top(_p_stack p_stack) {

    if (p_stack != NULL) {

        return p_stack->array[p_stack->top];
    }

    return NULL;
}

_p_stack stack_extend(_p_stack p_stack) {

    if (p_stack != NULL) {

        _p_adt *bigger_array = alloc_memory(p_stack->capacity * 2 * sizeof(_p_adt));

        if (bigger_array != NULL) {

            for (int i = 0; i < p_stack->capacity; ++i) {

                bigger_array[i] = p_stack->array[i];
            }

            p_stack->array = bigger_array;
            p_stack->capacity *= 2;
        }

        return p_stack;
    }
    return NULL;
}
