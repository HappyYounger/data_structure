//
// Created by 杨光 on 2019/4/9.
//

#include <stddef.h>
#include "tree.h"

static _p_tree_node update_tree_ancestor_node(_p_tree_node parent, _p_tree_node child) {

    child->p_parent = parent;
    ++parent->degree;

    if (parent->p_first_child == NULL) {

        parent->p_first_child = child;
    } else {

        _p_tree_node last = parent->p_first_child;
        while (last->p_rigth_sibling != NULL) {

            last = last->p_rigth_sibling;
        }

        child->p_left_sibling = last;
        last->p_rigth_sibling = child;
    }

    _p_tree_node clone = child;
    while (clone->p_parent != NULL) {

        if (clone->p_parent->depth <= clone->depth) {

            clone->p_parent->depth = clone->depth + 1;
            clone = clone->p_parent;
        } else {

            break;
        }
    }

    return child;
}

static _p_tree sub_tree(_p_tree p_tree, _p_tree_node p_tree_node) {

    if (p_tree != NULL && p_tree_node != NULL) {

        _p_tree p_sub_tree = alloc_memory(sizeof(_tree));

        if (p_sub_tree != NULL) {

            p_sub_tree->adt_bits_assigns = p_tree->adt_bits_assigns;
            p_sub_tree->adt_assigns = p_tree->adt_assigns;
            p_sub_tree->adt_bits_equals = p_tree->adt_bits_equals;
            p_sub_tree->adt_equals = p_tree->adt_equals;
            p_sub_tree->root = p_tree_node;

            return p_sub_tree;
        }
    }

    return NULL;
}

_p_tree tree_init(_p_adt p_ad_root,
                  _p_func_adt_assigns adt_assigns,
                  _p_func_adt_bits_assigns bits_assigns,
                  _p_func_adt_equals adt_equals,
                  _p_func_adt_bits_equals bits_equals) {

    _p_tree p_tree = alloc_memory(sizeof(_tree));

    if (p_tree != NULL) {

        _p_tree_node p_tree_node = tree_make_node(p_tree, p_ad_root);

        if (p_tree_node != NULL) {

            p_tree->adt_bits_assigns = p_tree_node;
            return p_tree;
        }
    }

    return NULL;
}

_p_tree_node tree_make_node(_p_tree p_tree, _p_adt p_ad) {

    if (p_tree != NULL && valid_data(p_ad)) {

        _p_tree_node p_tree_node = alloc_memory(sizeof(_tree_node));

        if (p_tree_node != NULL) {

            p_tree->adt_assigns(&p_tree_node->p_ad, p_ad);
            p_tree_node->degree = 0;
            p_tree_node->depth = 1;
            p_tree_node->p_parent = p_tree_node->p_left_sibling = p_tree_node->p_rigth_sibling = p_tree_node->p_first_child = NULL;

            return p_tree_node;
        }
    }

    return NULL;
}

_p_tree_node tree_add_child_node(_p_tree_node parent, _p_tree_node child) {

    if (parent != NULL && child != NULL) {

        return update_tree_ancestor_node(parent, child);
    }
    return NULL;
}

_p_tree tree_remove_node(_p_tree p_tree, _p_tree_node child) {


    return NULL;
}

_p_tree tree_remove_ad(_p_tree p_tree, _p_adt p_ad) {

    if (p_tree != NULL && valid_data(p_ad)) {

        _p_tree_node p_tree_node = tree_find_ad(p_tree, p_ad);
        return tree_remove_node(p_tree, p_tree_node);
    }
    return NULL;
}

_p_tree_node tree_find_ad(_p_tree p_tree, _p_adt p_ad) {


    if (p_tree->adt_equals(p_tree->root->p_ad, p_ad)) {

        return p_tree->root;
    } else {

        _p_tree_node child = p_tree->root->p_first_child;
        while (child != NULL) {

            _p_tree p_sub_tree = sub_tree(p_tree, child);
            tree_find_ad(p_sub_tree, p_ad);
            child = child->p_rigth_sibling;
        }
    }

    return NULL;
}


_p_tree_node *tree_breadth_first_traverse(_p_tree p_tree) {


    return NULL;
}

_p_tree_node *tree_depth_first_traverse(_p_tree p_tree, bool is_root_first) {


    return NULL;
}

_p_binary_tree to_binary_tree(_p_tree p_tree) {


    return NULL;
}

bool node_on_tree(_p_tree p_tree, _p_tree_node p_tree_node) {

    if (p_tree->root == p_tree_node) {

        return true;
    } else {

        _p_tree_node sibling = p_tree->root->p_rigth_sibling;

        while (sibling != NULL){

            _p_tree p_sibling_tree = sub_tree(p_tree, sibling);
            node_on_tree(p_sibling_tree, sibling);
        }
        _p_tree_node child = p_tree->root->p_first_child;
        _p_tree p_sub_tree = sub_tree(p_tree, child);
        node_on_tree(p_sub_tree, p_tree_node);
    }

    return false;
}


_p_tree_node tree_find_next_ad(_p_tree p_tree, _p_tree_node p_tree_node, _p_adt p_ad) {


}
