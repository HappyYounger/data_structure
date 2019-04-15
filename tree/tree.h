//
// Created by 杨光 on 2019/4/9.
//

#ifndef DATA_STRUCTURE_TREE_H
#define DATA_STRUCTURE_TREE_H

#include "../adt/adt.h"
#include "../pool/pool.h"
#include "binary_tree.h"
#include "../list/list.h"


typedef struct tree_node {

    _p_adt p_ad;
    struct tree_node *p_parent;
    struct tree_node *p_left_sibling;
    struct tree_node *p_rigth_sibling;
    struct tree_node *p_first_child;
    unsigned depth;
    unsigned degree;
} _tree_node, *_p_tree_node;

typedef struct tree {

    _p_tree_node root
} _tree, *_p_tree;

typedef bool (*equals)(void *, void *);

_p_tree tree_init(_p_adt p_ad_root);

_p_tree_node tree_make_node(_p_tree p_tree, _p_adt p_ad);

_p_tree_node tree_add_child_node(_p_tree_node parent, _p_tree_node child);

_p_tree tree_remove_node(_p_tree p_tree, _p_tree_node child);

_p_tree tree_remove_ad(_p_tree p_tree, _p_adt p_ad);

_p_tree_node tree_find_ad(_p_tree p_tree, _p_adt p_ad);

_p_tree_node tree_find_next_ad(_p_tree p_tree, _p_tree_node p_tree_node, _p_adt p_ad);

_p_list tree_breadth_first_traverse(_p_tree p_tree);

_p_list tree_depth_first_traverse(_p_tree p_tree, bool is_root_first);

_p_binary_tree to_binary_tree(_p_tree p_tree);

bool tree_existed(_p_tree p_tree, void *data, bool (*equals)(void *, void *));

bool tree_node_existed(_p_tree p_tree, _p_tree_node p_tree_node);

bool tree_ad_existed(_p_tree p_tree, _p_adt p_ad);


#endif //DATA_STRUCTURE_TREE_H
