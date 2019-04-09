//
// Created by 杨光 on 2019/4/9.
//

#ifndef DATA_STRUCTURE_BINARY_TREE_H
#define DATA_STRUCTURE_BINARY_TREE_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct binary_tree_node {

    _p_adt p_ad;
    struct binary_tree_node *p_parent;
    struct binary_tree_node *p_left_child;
    struct binary_tree_node *p_right_child;
    unsigned degree;
    unsigned depth;

} _binary_tree_node, *_p_binary_tree_node;

typedef struct binary_tree {

    unsigned size;
    _p_binary_tree_node root;
    _p_func_adt_assigns adt_assigns;
    _p_func_adt_equals adt_equals;

} _binary_tree, *_p_binary_tree;

_p_binary_tree binary_tree_init(_p_adt p_ad_root, _p_func_adt_assigns adt_assigns, _p_func_adt_equals adt_equals);

_p_binary_tree_node binary_tree_add_left_child_node(_p_binary_tree_node p_parent, _p_binary_tree_node p_left_node);

_p_binary_tree_node binary_tree_add_right_child_node(_p_binary_tree_node p_parent, _p_binary_tree_node p_right_node);

_p_binary_tree_node binary_tree_remove_binary_tree_node(_p_binary_tree_node p_binary_tree_node);

_p_binary_tree_node binary_tree_add_left_child_ad(_p_binary_tree p_binary_tree, _p_binary_tree_node p_parent,
                                                  _p_adt p_ad);

_p_binary_tree_node binary_tree_add_right_child_ad(_p_binary_tree p_binary_tree, _p_binary_tree_node p_parent,
                                                   _p_adt p_ad);

_p_binary_tree_node binary_tree_remove_binary_tree_ad(_p_binary_tree p_binary_tree, _p_adt p_ad);

unsigned binary_tree_node_count(_p_binary_tree_node p_binary_tree_node);

_p_binary_tree_node *pre_order_traverse(_p_binary_tree_node p_binary_tree_node);

_p_binary_tree_node *in_order_traverse(_p_binary_tree_node p_binary_tree_node);

_p_binary_tree_node *post_order_traverse(_p_binary_tree_node p_binary_tree_node);

int binary_tree_node_degree(_p_binary_tree_node p_binary_tree_node);

int binary_tree_node_depth(_p_binary_tree_node p_binary_tree_node);

int binary_tree_degree(_p_binary_tree p_binary_tree);

int binary_tree_depth(_p_binary_tree p_binary_tree);

_p_binary_tree_node binary_tree_find_node(_p_binary_tree p_binary_tree, _p_binary_tree_node p_binary_tree_node);

_p_binary_tree_node binary_tree_find_ad(_p_binary_tree p_binary_tree, _p_adt p_ad);

_p_binary_tree_node binary_tree_make_node(_p_binary_tree p_binary_tree, _p_adt p_ad);

#endif //DATA_STRUCTURE_BINARY_TREE_H

