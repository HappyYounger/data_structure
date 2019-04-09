//
// Created by 杨光 on 2019/4/9.
//

#ifndef DATA_STRUCTURE_TREE_H
#define DATA_STRUCTURE_TREE_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct tree_node {

    _p_adt p_ad;
    struct tree_node *p_first_child;
    _p_func_adt_assigns adt_assigns;
    _p_func_adt_equals adt_equals;

} _tree_node, *_p_tree_node;

typedef struct tree {

    _p_tree_node root;
};

#endif //DATA_STRUCTURE_TREE_H
