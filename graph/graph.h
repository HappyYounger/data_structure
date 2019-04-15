//
// Created by 杨光 on 2019/4/15.
//

#ifndef DATA_STRUCTURE_GRAPH_H
#define DATA_STRUCTURE_GRAPH_H

#include "../adt/adt.h"
#include "../list/linked_list.h"

struct graph_vertex;

typedef struct edge {

    struct graph_vertex *p_vertex0;
    struct graph_vertex *p_vertex1;
    _p_adt p_ad_weight;

} _edge, *_p_edge;

typedef struct graph_vertex {

    _p_adt p_ad;
    _p_linked_list p_linked_list_edge;
} _graph_vertex, *_p_graph_vertex;

typedef struct graph {

    _p_linked_list p_linked_list_vertex;
    _p_linked_list p_linked_list_edge;


} _graph, *_p_graph;

_p_graph graph_init();

_p_graph_vertex graph_make_original_graph_vertex(_p_graph p_graph, _p_adt p_ad_v);

_p_graph_vertex graph_find_vertex(_p_graph p_graph, _p_adt p_ad_v);

_p_edge graph_make_edge(_p_graph p_graph, _p_adt p_ad_v0, _p_adt p_ad_v1, _p_adt p_ad_weight);

_p_edge graph_find_edge(_p_graph p_graph, _p_adt p_ad_v0, _p_adt p_ad_v1);

_p_graph graph_add_edge(_p_graph p_graph, _p_adt p_ad_v0, _p_adt p_ad_v1);

_p_graph graph_remove_edge(_p_graph p_graph, _p_adt p_ad_v0, _p_adt p_ad_v1);

_p_graph graph_add_vertex(_p_graph p_graph, _p_adt p_ad_v);

_p_graph graph_remove_vertex(_p_graph p_graph, _p_adt p_ad_v);

#endif //DATA_STRUCTURE_GRAPH_H
