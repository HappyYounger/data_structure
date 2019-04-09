//
// Created by 杨光 on 2019/4/9.
//

#ifndef DATA_STRUCTURE_BINARY_TREE_H
#define DATA_STRUCTURE_BINARY_TREE_H

#include "../adt/adt.h"

typedef struct binary_tree_node {

    _p_adt p_ad;
    struct binary_tree_node *p_parent;
    struct binary_tree_node *p_left_child;
    struct binary_tree_node *p_right_child;

} _binary_tree_node, *_p_binary_tree_node;

typedef struct binary_tree {

    unsigned size;
    _p_binary_tree_node root;
    _p_func_adt_assigns adt_assigns;
    _p_func_adt_equals adt_equals;
} _binary_tree, *_p_binary_tree;

_p_binary_tree binary_tree_init(_p_func_adt_assigns adt_assigns, _p_func_adt_equals adt_equals);

_p_binary_tree_node pre_order_traverse(_p_binary_tree);

_p_binary_tree_node in_order_traverse(_p_binary_tree);

_p_binary_tree_node post_order_traverse(_p_binary_tree);

_p_binary_tree_node add_left_child(_p_binary_tree_node p_parent, _p_binary_tree_node p_left_node);

_p_binary_tree_node add_right_child(_p_binary_tree_node p_parent, _p_binary_tree_node p_right_node);

_p_binary_tree_node remove_binary_tree_node(_p_binary_tree_node p_binary_tree_node);

#endif //DATA_STRUCTURE_BINARY_TREE_H

