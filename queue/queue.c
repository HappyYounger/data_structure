//
// Created by 杨光 on 2019/3/27.
//

#include <stddef.h>
#include "queue.h"

extern _p_memory_pool p_memory_pool;

_p_queue queue_init(_p_func_adt_assigns adt_assigns) {

    if (p_memory_pool != NULL) {

        _p_queue p_queue = alloc_memory(p_memory_pool, sizeof(_queue));
        p_queue->back = p_queue->front = NULL;
        p_queue->size = 0;

        p_queue->adt_assigns = assigns_func(adt_assigns);
    }

    return NULL;
}

_p_queue queue_enqueue(_p_queue p_queue, _p_adt p_ad) {

    if (p_queue != NULL && p_ad != NULL) {

        _p_q_node p_q_node = alloc_memory(p_memory_pool, sizeof(_q_node));
        p_queue->adt_assigns(p_q_node->p_ad, p_ad);

        if (p_queue->front == NULL) {

            p_queue->front = p_queue->back = p_q_node;
        } else {

            p_queue->back->next = p_q_node;
            p_queue->back = p_q_node;
        }
        ++p_queue->size;
    }

    return NULL;
}

_p_adt queue_dequeue(_p_queue p_queue) {

    _p_adt p_ad = NULL;
    if (p_queue != NULL && p_queue->size > 0) {

        p_ad = p_queue->front->p_ad;
        if (p_queue->size == 1) {

            p_queue->front = p_queue->back = NULL;
        } else {

            p_queue->front = p_queue->front->next;
        }
        --p_queue->size;
    }
    return p_ad;
}

_p_adt queue_peek(_p_queue p_queue) {

    if (p_queue != NULL && p_queue->front != NULL) {

        return p_queue->front->p_ad;
    }

    return NULL;
}