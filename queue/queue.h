//
// Created by 杨光 on 2019/3/27.
//

#ifndef DATA_STRUCTURE_QUEUE_H
#define DATA_STRUCTURE_QUEUE_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct q_node {

    _p_adt *p_ad;
    struct q_node *next;
} _q_node, *_p_q_node;

typedef struct queue {

    unsigned size;
    _p_q_node front;
    _p_q_node back;
} _queue, *_p_queue;


_p_queue queue_init();

_p_queue queue_enqueue(_p_queue p_queue, _p_adt p_ad);

_p_adt queue_dequeue(_p_queue p_queue);

_p_adt queue_peek(_p_queue p_queue);

#endif //DATA_STRUCTURE_QUEUE_H
