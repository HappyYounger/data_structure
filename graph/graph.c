//
// Created by 杨光 on 2019/4/15.
//

#include <stddef.h>
#include "graph.h"
#include "../pool/pool.h"

_p_graph graph_init() {

    _p_graph p_graph = alloc_memory(sizeof(_graph));

    if (p_graph != NULL) {

        p_graph->p_linked_list_edge = linked_list_init();
        p_graph->p_linked_list_vertex = linked_list_init();
        if (p_graph->p_linked_list_vertex != NULL && p_graph->p_linked_list_edge != NULL) {

            return p_graph;
        }
    }
    return NULL;
}

_p_graph_vertex graph_make_original_graph_vertex(_p_graph p_graph, _p_adt p_ad) {

    if (valid_data(p_ad)) {

        _p_graph_vertex p_graph_vertex = alloc_memory(sizeof(_graph_vertex));

        if (p_graph_vertex != NULL) {

            p_graph_vertex->p_linked_list_edge = linked_list_init();
            if (p_graph_vertex->p_linked_list_edge != NULL) {

                p_graph_vertex->p_ad = p_ad;
                return p_graph_vertex;
            }
        }
    }
    return NULL;
}

_p_graph_vertex graph_find_vertex(_p_graph p_graph, _p_adt p_ad_v) {

    if (p_graph != NULL && valid_data(p_ad_v)) {

        _p_linked_list_node p_linked_list_node = linked_list_find(p_graph->p_linked_list_vertex, p_ad_v);
        if (p_linked_list_node != NULL) {

            return p_linked_list_node->p_ad->data;
        }
    }

    return NULL;
}

_p_edge graph_make_edge(_p_graph p_graph, _p_adt p_ad_v0, _p_adt p_ad_v1, _p_adt p_ad_weight) {

    if (p_graph != NULL && p_ad_v0 != NULL && p_ad_v1 != NULL && valid_data(p_ad_weight)) {

        _p_edge p_edge = alloc_memory(sizeof(_edge));

        if (p_edge != NULL) {

//            p_edge->p_vertex0 = graph_make_original_graph_vertex(p_ad_v0);
//            p_edge->p_vertex1 = graph_make_original_graph_vertex(p_ad_v1);
//            p_edge->p_ad_weight = p_ad_weight;

            return p_edge;
        }
    }
    return NULL;
}


_p_edge graph_find_edge(_p_graph p_graph, _p_adt p_ad_v0, _p_adt p_ad_v1){



    return NULL;
}
