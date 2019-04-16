//
// Created by 杨光 on 2019/4/15.
//

#ifndef DATA_STRUCTURE_GRAPH_H
#define DATA_STRUCTURE_GRAPH_H

#include "../adt/adt.h"
#include "../list/linked_list.h"

struct graph_vertex;

typedef struct edge {

    struct graph_vertex *p_v0;
    struct graph_vertex *p_v1;
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

_p_graph_vertex graph_add_ad_vertex(_p_graph p_graph, _p_adt p_ad);

_p_graph_vertex graph_make_original_graph_vertex(_p_adt p_ad);

_p_graph_vertex graph_add_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex);

_p_graph_vertex graph_find_ad_vertex(_p_graph p_graph, _p_adt p_ad);

_p_graph_vertex graph_find_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex);

_p_edge graph_make_original_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1, _p_adt p_ad_weight);

_p_edge graph_find_ad_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1);

_p_edge graph_find_edge(_p_graph p_graph, _p_edge p_edge);

//_p_linked_list graph_find_ad_edge_list(_p_graph p_graph, _p_adt p_ad);
//
//_p_linked_list graph_find_edge_list(_p_graph p_graph, _p_edge);

_p_edge graph_add_ad_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1, _p_adt p_ad_weight);

_p_edge graph_add_edge(_p_graph p_graph, _p_edge p_edge);

_p_graph graph_remove_ad_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1);

_p_graph graph_remove_edge(_p_graph p_graph, _p_edge p_edge);

_p_graph graph_remove_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex);

_p_graph graph_remove_ad_vertex(_p_graph p_graph, _p_adt p_ad);

#endif //DATA_STRUCTURE_GRAPH_H
