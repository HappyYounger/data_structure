//
// Created by 杨光 on 2019/4/15.
//

#ifndef DATA_STRUCTURE_DIRECTED_GRAPH_H
#define DATA_STRUCTURE_DIRECTED_GRAPH_H

#include "../list/linked_list.h"

typedef struct digraph_vertex;

typedef struct arc {

    _p_adt p_ad;
    _p_linked_list p_linked_list_arc;
} _arc, *_p_arc;

typedef struct digraph_vertex {

    _p_linked_list p_linked_list_vertex;
    _p_linked_list p_linked_list_arc;
} _digraph_vertex, *_p_digraph_vertex;

#endif //DATA_STRUCTURE_DIRECTED_GRAPH_H
