//
// Created by 杨光 on 2019/4/9.
//

#include "binary_tree.h"
#include <stddef.h>

extern _p_memory_pool p_memory_pool;

_p_binary_tree binary_tree_init(_p_adt p_ad_root, _p_func_adt_assigns adt_assigns, _p_func_adt_equals adt_equals) {

    if (p_memory_pool != NULL && valid_data(p_ad_root)) {

        _p_binary_tree p_binary_tree = alloc_memory(p_memory_pool, sizeof(_binary_tree));

        p_binary_tree->adt_assigns = assigns_func(adt_assigns);
        p_binary_tree->adt_equals = equals_func(adt_equals);

        _p_binary_tree_node root = alloc_memory(p_memory_pool, sizeof(_binary_tree_node));
        p_binary_tree->adt_assigns(root->p_ad, p_ad_root);

        return p_binary_tree;
    }

    return NULL;
}

_p_binary_tree_node binary_tree_add_left_child_node(_p_binary_tree_node p_parent, _p_binary_tree_node p_left_node) {

    if (p_parent != NULL && p_left_node != NULL) {

        p_parent->p_left_child = p_left_node;
        p_left_node->p_parent = p_parent;
        return p_parent;
    }

    return NULL;
}

_p_binary_tree_node binary_tree_add_right_child_node(_p_binary_tree_node p_parent, _p_binary_tree_node p_right_node) {

    if (p_parent != NULL && p_right_node != NULL) {

        p_parent->p_left_child = p_right_node;
        p_right_node->p_parent = p_parent;
        return p_parent;
    }

    return NULL;
}

_p_binary_tree_node binary_tree_remove_binary_tree_node(_p_binary_tree_node p_binary_tree_node) {

    _p_binary_tree_node p_parent = NULL;
    if (p_binary_tree_node != NULL) {

        p_parent = p_binary_tree_node->p_parent;

        if (p_parent->p_left_child == p_binary_tree_node) {

            p_parent->p_left_child = NULL;
        } else {

            p_parent->p_right_child = NULL;
        }
    }

    return p_parent;
}

_p_binary_tree_node binary_tree_add_left_child_ad(_p_binary_tree p_binary_tree, _p_binary_tree_node p_parent,
                                                  _p_adt p_ad) {

    if (p_parent != NULL) {

        _p_binary_tree_node p_binary_tree_node = binary_tree_make_node(p_binary_tree, p_ad);
        if (p_binary_tree_node != NULL) {

            p_parent->p_left_child = p_binary_tree_node;
            p_binary_tree_node->p_parent = p_parent;

            return p_binary_tree_node;
        }
    }

    return NULL;
}

_p_binary_tree_node binary_tree_add_right_child_ad(_p_binary_tree p_binary_tree, _p_binary_tree_node p_parent,
                                                   _p_adt p_ad) {

    if (p_parent != NULL) {

        _p_binary_tree_node p_binary_tree_node = binary_tree_make_node(p_binary_tree, p_ad);
        if (p_binary_tree_node != NULL) {

            p_parent->p_right_child = p_binary_tree_node;
            p_binary_tree_node->p_parent = p_parent;

            return p_binary_tree_node;
        }
    }

    return NULL;
}

_p_binary_tree_node binary_tree_remove_binary_tree_ad(_p_binary_tree p_binary_tree, _p_adt p_ad){

    _p_binary_tree_node p_binary_tree_node = binary_tree_find_ad(p_binary_tree_node, p_ad);
    binary_tree_remove_binary_tree_node(p_binary_tree_node);
    return p_binary_tree_node->p_parent;
}


unsigned binary_tree_node_count(_p_binary_tree_node p_binary_tree_node) {

    static unsigned count = 1;

    if (p_binary_tree_node->p_left_child != NULL) {

        ++count;
        binary_tree_node_count(p_binary_tree_node->p_left_child);
    }

    if (p_binary_tree_node->p_right_child != NULL) {

        ++count;
        binary_tree_node_count(p_binary_tree_node->p_right_child);
    }

    return count;
}

static _p_binary_tree_node binary_tree_find_node_helper(_p_binary_tree p_binary_tree,
                                                        _p_binary_tree_node p_binary_tree_start_node,
                                                        _p_binary_tree_node p_binary_tree_node) {

    if (p_binary_tree != NULL && p_binary_tree_start_node != NULL && p_binary_tree_node != NULL) {

        if (p_binary_tree->adt_equals(p_binary_tree_start_node->p_ad, p_binary_tree_node->p_ad)) {

            return p_binary_tree_start_node;
        }
    }

    return NULL;
}

static _p_binary_tree_node binary_tree_find_ad_helper(_p_binary_tree p_binary_tree,
                                                      _p_binary_tree_node p_binary_tree_start_node,
                                                      _p_adt p_ad) {

    if (p_binary_tree != NULL && p_binary_tree_start_node != NULL && p_ad != NULL) {

        if (p_binary_tree->adt_equals(p_binary_tree_start_node->p_ad, p_ad)) {

            return p_binary_tree_start_node;
        }
    }

    return NULL;
}

static _p_binary_tree_node *pre_order_traverse_helper(_p_binary_tree_node *p_binary_tree_node_array,
                                                      _p_binary_tree_node p_binary_tree_node) {

    static unsigned index = 0;

    p_binary_tree_node_array[index++] = p_binary_tree_node;

    if (p_binary_tree_node->p_left_child != NULL) {

        pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node->p_left_child);
    }

    if (p_binary_tree_node->p_right_child != NULL) {

        pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node->p_right_child);
    }

    return p_binary_tree_node_array;
}

static int binary_tree_degree_helper(_p_binary_tree_node p_binary_tree_node) {

    int count = -1;

    if (p_binary_tree_node != NULL) {

        count = 0;
        if (p_binary_tree_node->p_left_child != NULL) {

            ++count;
        }

        if (p_binary_tree_node->p_right_child != NULL) {

            ++count;
        }

        if (count == 2) {

            return count;

        } else if (count < 2) {

            int left_count = binary_tree_degree_helper(p_binary_tree_node->p_left_child);
            int right_count = binary_tree_degree_helper(p_binary_tree_node->p_right_child);

            count = count < left_count ? left_count : count;
            count = count < right_count ? right_count : count;
        }
    }

    return count;
}

int binary_tree_depth_helper(_p_binary_tree_node p_binary_tree_node) {

    int depth = 0;
    if (p_binary_tree_node != NULL) {

        ++depth;

        int left_depth = binary_tree_depth_helper(p_binary_tree_node->p_left_child);
        int right_depth = binary_tree_depth_helper(p_binary_tree_node->p_right_child);

        depth += (left_depth < right_depth) ? right_depth : left_depth;
    }

    return depth;
}


static _p_binary_tree_node *in_order_traverse_helper(_p_binary_tree_node *p_binary_tree_node_array,
                                                     _p_binary_tree_node p_binary_tree_node) {

    static unsigned index = 0;

    if (p_binary_tree_node->p_left_child != NULL) {

        pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node->p_left_child);
    }

    p_binary_tree_node_array[index++] = p_binary_tree_node;

    if (p_binary_tree_node->p_right_child != NULL) {

        pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node->p_right_child);
    }

    return p_binary_tree_node_array;
}

static _p_binary_tree_node *post_order_traverse_helper(_p_binary_tree_node *p_binary_tree_node_array,
                                                       _p_binary_tree_node p_binary_tree_node) {

    static unsigned index = 0;

    if (p_binary_tree_node->p_left_child != NULL) {

        pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node->p_left_child);
    }

    if (p_binary_tree_node->p_right_child != NULL) {

        pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node->p_right_child);
    }

    p_binary_tree_node_array[index++] = p_binary_tree_node;

    return p_binary_tree_node_array;
}

_p_binary_tree_node *pre_order_traverse(_p_binary_tree_node p_binary_tree_node) {

    unsigned count = binary_tree_node_count(p_binary_tree_node);
    if (count > 0) {

        _p_binary_tree_node *p_binary_tree_node_array =
                alloc_memory(p_memory_pool, sizeof(_p_binary_tree_node) * count);

        return pre_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node);
    }

    return NULL;
}

_p_binary_tree_node *in_order_traverse(_p_binary_tree_node p_binary_tree_node) {

    unsigned count = binary_tree_node_count(p_binary_tree_node);
    if (count > 0) {

        _p_binary_tree_node *p_binary_tree_node_array =
                alloc_memory(p_memory_pool, sizeof(_p_binary_tree_node) * count);

        return in_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node);
    }

    return NULL;
}

_p_binary_tree_node *post_order_traverse(_p_binary_tree_node p_binary_tree_node) {

    unsigned count = binary_tree_node_count(p_binary_tree_node);
    if (count > 0) {

        _p_binary_tree_node *p_binary_tree_node_array =
                alloc_memory(p_memory_pool, sizeof(_p_binary_tree_node) * count);

        return post_order_traverse_helper(p_binary_tree_node_array, p_binary_tree_node);
    }

    return NULL;
}


static int get_binary_tree_node_degree(_p_binary_tree_node p_binary_tree_node) {

    if (p_binary_tree_node != NULL) {

        unsigned count = 0;

        if (p_binary_tree_node->p_left_child != NULL) {

            ++count;
        }

        if (p_binary_tree_node->p_right_child != NULL) {

            ++count;
        }

        return count;
    }

    return -1;
}

int binary_tree_node_degree(_p_binary_tree_node p_binary_tree_node) {

    return p_binary_tree_node->degree;
}

int binary_tree_node_depth(_p_binary_tree_node p_binary_tree_node) {

    return p_binary_tree_node->depth;
}


int binary_tree_degree(_p_binary_tree p_binary_tree) {

    if (p_binary_tree != NULL) {

        return binary_tree_degree_helper(p_binary_tree->root);
    }
    return -1;
}

int binary_tree_depth(_p_binary_tree p_binary_tree) {

    if (p_binary_tree != NULL) {

        return binary_tree_depth_helper(p_binary_tree->root);
    }

    return -1;
}

_p_binary_tree_node binary_tree_make_node(_p_binary_tree p_binary_tree, _p_adt p_ad) {

    if (p_memory_pool != NULL && p_binary_tree != NULL && valid_data(p_ad)) {

        _p_binary_tree_node p_binary_tree_node = alloc_memory(p_memory_pool, sizeof(_binary_tree_node));

        p_binary_tree->adt_assigns(p_binary_tree_node->p_ad, p_ad);
        p_binary_tree_node->p_parent = p_binary_tree_node->p_left_child = p_binary_tree_node->p_right_child = NULL;

        return p_binary_tree_node;
    }

    return NULL;
}

_p_binary_tree_node binary_tree_find_node(_p_binary_tree p_binary_tree, _p_binary_tree_node p_binary_tree_node) {

    return binary_tree_find_node_helper(p_binary_tree, p_binary_tree->root, p_binary_tree_node);
}

_p_binary_tree_node binary_tree_find_ad(_p_binary_tree p_binary_tree, _p_adt p_ad) {

    return binary_tree_find_ad_helper(p_binary_tree, p_binary_tree->root, p_ad);
}

