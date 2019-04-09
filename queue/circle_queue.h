//
// Created by 杨光 on 2019/3/31.
//

#ifndef DATA_STRUCTURE_CIRCLE_QUEUE_H
#define DATA_STRUCTURE_CIRCLE_QUEUE_H

#include "../adt/adt.h"

typedef struct circle_queue {

    unsigned capacity;
    unsigned size;
    unsigned front, rear;
    _p_adt array;

} _circle_queue, *_p_circle_queue;
#endif //DATA_STRUCTURE_CIRCLE_QUEUE_H
