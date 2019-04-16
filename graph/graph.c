//
// Created by 杨光 on 2019/4/15.
//

#include <stddef.h>
#include "graph.h"
#include "../pool/pool.h"

static bool vertex_equals_ad(_p_adt p_ad0, _p_adt p_ad1) {

    return ((_p_graph_vertex) p_ad0->data)->p_ad == p_ad1;
}

static bool vertex_equals_vertex(_p_adt p_ad0, _p_adt p_ad1) {

    return ((_p_graph_vertex) p_ad0->data)->p_ad == ((_p_graph_vertex) p_ad1->data)->p_ad;
}

static bool edge_equals_ad(_p_edge p_edge, _p_adt p_ad0, _p_adt p_ad1) {

    if (p_edge != NULL && valid_data(p_ad0) && valid_data(p_ad1)) {

        _p_graph_vertex p_ad_v0 = p_edge->p_v0;
        _p_graph_vertex p_ad_v1 = p_edge->p_v1;

        return (p_ad_v0->p_ad == p_ad0 && p_ad_v1->p_ad == p_ad1) ||
               (p_ad_v0->p_ad == p_ad1 && p_ad_v1->p_ad == p_ad0);
    }

    return false;
}

static bool edge_equals_edge(_p_adt p_ad0, _p_adt p_ad1) {

    _p_edge p_edge0 = p_ad0->data;
    _p_edge p_edge1 = p_ad1->data;

    return (p_edge0->p_v0 == p_edge1->p_v0 && p_edge0->p_v1 == p_edge1->p_v1) ||
           (p_edge0->p_v0 == p_edge1->p_v1 && p_edge0->p_v1 == p_edge1->p_v0);
}

static _p_graph_vertex add_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex) {

    _p_adt p_ad_v = get_ad_pointers(1, sizeof(_graph_vertex));

    if (p_ad_v != NULL) {
        p_ad_v->data = p_graph_vertex;

        if (linked_list_insert_last_after(p_graph->p_linked_list_vertex, p_ad_v) != NULL) {

            return p_graph_vertex;
        }
    }
    return NULL;
}


static _p_graph remove_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex) {

    _p_adt p_ad_v = get_ad_pointers(1, sizeof(_graph_vertex));

    if (p_ad_v != NULL) {
        p_ad_v->data = p_graph_vertex;

        if (linked_list_remove_cond(p_graph->p_linked_list_vertex, vertex_equals_vertex, p_ad_v) != NULL) {

            //删除边
            _p_linked_list_node p_cur = p_graph_vertex->p_linked_list_edge->first;

            while (p_cur != NULL) {

                linked_list_remove_cond(p_graph_vertex->p_linked_list_edge, edge_equals_edge, p_cur->p_ad);
                linked_list_remove_cond(p_graph->p_linked_list_edge, edge_equals_edge, p_cur->p_ad);

                _p_edge p_edge = p_cur->p_ad->data;

                _p_graph_vertex p_v0 = p_edge->p_v0;
                _p_graph_vertex p_v1 = p_edge->p_v1;

                _p_graph_vertex p_v = NULL;

                if (p_v0 == p_graph_vertex) {

                    p_v = p_v1;
                } else if (p_v1 == p_graph_vertex) {

                    p_v = p_v0;
                }

                if (p_v != NULL) {

                    linked_list_remove_cond(p_v->p_linked_list_edge, edge_equals_edge, p_cur->p_ad);
                }

                p_cur = p_cur->p_next;
            }

            return p_graph;
        }
    }
    return NULL;
}

static _p_edge add_edge(_p_graph p_graph, _p_edge p_edge) {

    _p_adt p_ad_e = get_ad_pointers(1, sizeof(_p_edge));
    if (p_ad_e != NULL) {

        p_ad_e->data = p_edge;

        if (linked_list_insert_last_after(p_graph->p_linked_list_edge, p_ad_e) != NULL) {

            //在vertex上添加边

            _p_graph_vertex p_v0 = p_edge->p_v0;
            _p_graph_vertex p_v1 = p_edge->p_v1;

            linked_list_insert_last_after(p_v0->p_linked_list_edge, p_ad_e);
            linked_list_insert_last_after(p_v1->p_linked_list_edge, p_ad_e);

            return p_edge;
        }
    }

    return NULL;
}

static _p_graph remove_edge(_p_graph p_graph, _p_edge p_edge) {

    _p_adt p_ad_e = get_ad_pointers(1, sizeof(_edge));

    if (p_ad_e != NULL) {

        p_ad_e->data = p_edge;
        if (linked_list_remove_cond(p_graph->p_linked_list_edge, edge_equals_edge, p_ad_e) != NULL) {

            return p_graph;
        }
    }

    return NULL;
}

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

_p_graph_vertex graph_make_original_graph_vertex(_p_adt p_ad) {

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

_p_graph_vertex graph_add_ad_vertex(_p_graph p_graph, _p_adt p_ad) {

    if (p_graph != NULL && valid_data(p_ad)) {

        _p_graph_vertex p_graph_vertex = graph_find_ad_vertex(p_graph, p_ad);

        if (p_graph_vertex == NULL) {

            p_graph_vertex = graph_make_original_graph_vertex(p_ad);

            if (p_graph_vertex != NULL) {

                return add_vertex(p_graph, p_graph_vertex);
            }
        }

        return p_graph_vertex;
    }

    return NULL;
}

_p_graph_vertex graph_add_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex) {

    if (p_graph != NULL && p_graph_vertex != NULL) {

        if (graph_find_vertex(p_graph, p_graph_vertex) == NULL) {

            return add_vertex(p_graph, p_graph_vertex);
        }
    }

    return NULL;
}

_p_graph_vertex graph_find_ad_vertex(_p_graph p_graph, _p_adt p_ad) {

    if (p_graph != NULL && valid_data(p_ad)) {

        _p_linked_list_node p_linked_list_node =
                linked_list_find_cond(p_graph->p_linked_list_vertex,
                                      vertex_equals_ad,
                                      p_ad);
        if (p_linked_list_node != NULL) {

            return p_linked_list_node->p_ad->data;
        }
    }

    return NULL;
}

_p_graph_vertex graph_find_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex) {

    if (p_graph != NULL && p_graph_vertex != NULL) {

        _p_adt p_ad_v = get_ad_pointers(1, sizeof(_graph_vertex));
        p_ad_v->data = p_graph_vertex;

        _p_linked_list_node p_linked_list_node =
                linked_list_find_cond(p_graph->p_linked_list_vertex,
                                      vertex_equals_vertex,
                                      p_ad_v);

        if (p_linked_list_node != NULL) {

            return p_graph_vertex;
        }
    }

    return NULL;
}

_p_edge graph_make_original_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1, _p_adt p_ad_weight) {

    if (p_graph != NULL && valid_data(p_ad0) && valid_data(p_ad1)) {

        _p_graph_vertex p_v0 = graph_find_ad_vertex(p_graph, p_ad0);

        if (p_v0 == NULL) {

            return NULL;
        }

        _p_graph_vertex p_v1 = graph_find_ad_vertex(p_graph, p_ad1);

        if (p_v1 == NULL) {

            return NULL;
        }

        _p_edge p_edge = alloc_memory(sizeof(_edge));

        p_edge->p_ad_weight = p_ad_weight;
        p_edge->p_v0 = p_v0;
        p_edge->p_v1 = p_v1;

        return p_edge;
    }
    return NULL;
}

_p_edge graph_find_ad_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1) {

    if (p_graph != NULL && valid_data(p_ad0) && valid_data(p_ad1)) {

        _p_linked_list_node p_cur = p_graph->p_linked_list_edge->first;

        while (p_cur != NULL) {

            _p_edge p_edge = p_cur->p_ad->data;

            if (edge_equals_ad(p_edge, p_ad0, p_ad1)) {

                return p_edge;
            }
            p_cur = p_cur->p_next;
        }
    }

    return NULL;
}

_p_edge graph_find_edge(_p_graph p_graph, _p_edge p_edge) {

    if (p_graph != NULL && p_edge != NULL) {

        _p_linked_list_node p_cur = p_graph->p_linked_list_edge->first;

        while (p_cur != NULL) {

            _p_edge p_e = p_cur->p_ad->data;

            if (edge_equals_edge(p_e, p_edge)) {

                return p_e;
            }
            p_cur = p_cur->p_next;
        }
    }

    return NULL;

};

_p_edge graph_add_ad_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1, _p_adt p_ad_weight) {

    if (p_graph != NULL && valid_data(p_ad0) && valid_data(p_ad1)) {

        _p_edge p_edge = graph_find_ad_edge(p_graph, p_ad0, p_ad1);

        if (p_edge == NULL) {

            _p_edge p_e = graph_make_original_edge(p_graph, p_ad0, p_ad1, p_ad_weight);

            if (p_e != NULL) {

                return add_edge(p_graph, p_e);
            }
        }

        return p_edge;
    }

    return NULL;
}

_p_edge graph_add_edge(_p_graph p_graph, _p_edge p_edge) {

    if (p_graph != NULL && p_edge != NULL) {

        if (graph_find_edge(p_graph, p_edge) == NULL) {

            return add_edge(p_graph, p_edge);
        }

        return p_edge;
    }

    return NULL;
}


_p_graph graph_remove_ad_edge(_p_graph p_graph, _p_adt p_ad0, _p_adt p_ad1) {

    if (p_graph != NULL && valid_data(p_ad0) && valid_data(p_ad1)) {

        _p_edge p_edge = graph_find_ad_edge(p_graph, p_ad0, p_ad1);

        if (p_edge != NULL) {

            return remove_edge(p_graph, p_edge);
        }
    }

    return NULL;
}

_p_graph graph_remove_edge(_p_graph p_graph, _p_edge p_edge) {

    if (p_graph != NULL && p_edge != NULL) {

        if (graph_find_edge(p_graph, p_edge) != NULL) {

            return remove_edge(p_graph, p_edge);
        }
    }

    return NULL;
}


_p_graph graph_remove_ad_vertex(_p_graph p_graph, _p_adt p_ad) {

    _p_graph_vertex p_graph_vertex = graph_find_ad_vertex(p_graph, p_ad);

    if (p_graph_vertex != NULL) {

        if (remove_vertex(p_graph, p_graph_vertex)) {

            return p_graph;
        }
    }

    return NULL;
}

_p_graph graph_remove_vertex(_p_graph p_graph, _p_graph_vertex p_graph_vertex) {

    if (p_graph != NULL && p_graph_vertex != NULL) {

        if (remove_vertex(p_graph, p_graph_vertex)) {

            return p_graph;
        }
    }
    return NULL;
}
