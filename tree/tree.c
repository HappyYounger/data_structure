//
// Created by 杨光 on 2019/4/9.
//

#include <stdio.h>
#include <stddef.h>
#include "tree.h"
#include "../list/linked_list.h"
#include "../queue/queue.h"

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

            p_sub_tree->root = p_tree_node;

            return p_sub_tree;
        }
    }

    return NULL;
}

_p_tree tree_init(_p_adt p_ad_root) {

    _p_tree p_tree = alloc_memory(sizeof(_tree));


    if (p_tree != NULL) {

        _p_tree_node p_tree_node = tree_make_node(p_tree, p_ad_root);

        if (p_tree_node != NULL) {

            p_tree->root = p_tree_node;
            return p_tree;
        }
    }

    return NULL;
}

_p_tree_node tree_make_node(_p_tree p_tree, _p_adt p_ad) {

    if (p_tree != NULL && valid_data(p_ad)) {

        _p_tree_node p_tree_node = alloc_memory(sizeof(_tree_node));

        if (p_tree_node != NULL) {

            p_tree_node->p_ad = p_ad;
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

    if (adt_equals(p_tree->root->p_ad, p_ad)) {

        _p_tree_node sibling = p_tree->root->p_rigth_sibling;

        while (sibling != NULL) {

            _p_tree p_sibling_tree = sub_tree(p_tree, sibling);
            _p_tree_node p_tree_node = tree_find_ad(p_sibling_tree, p_ad);

            if (p_tree_node == NULL) {

                sibling = sibling->p_rigth_sibling;
            } else {

                return p_tree_node;
            }
        }
        _p_tree_node child = p_tree->root->p_first_child;
        _p_tree p_sub_tree = sub_tree(p_tree, child);

        return tree_find_ad(p_sub_tree, p_ad);
    }

    return p_tree->root;
}

_p_tree_node tree_find_next_ad(_p_tree p_tree, _p_tree_node p_tree_node, _p_adt p_ad) {

    if (p_tree_node != NULL) {

        _p_tree_node sibling = p_tree_node->p_rigth_sibling;

        while (sibling != NULL) {

            _p_tree p_sibling_tree = sub_tree(p_tree, sibling);
            _p_tree_node p_sub_tree_node = tree_find_ad(p_sibling_tree, p_ad);

            if (p_sub_tree_node == NULL) {

                sibling = sibling->p_rigth_sibling;
            } else {

                return p_sub_tree_node;
            }
        }

        _p_tree_node child = p_tree_node->p_first_child;
        _p_tree p_sub_tree = sub_tree(p_tree, child);

        return tree_find_ad(p_sub_tree, p_ad);
    }

    return NULL;
}


_p_list tree_breadth_first_traverse(_p_tree p_tree) {

    _p_list p_list = list_init(32);
    _p_queue p_queue = queue_init(NULL, NULL);

    _p_adt p_ad = get_ad_objects(1, sizeof(_p_tree_node));
    p_ad->data = p_tree->root;

    while (p_ad != NULL) {

        list_append(p_list, p_ad);
        _p_tree_node child = ((_p_tree_node) (p_ad->data))->p_first_child;

        while (child != NULL) {

            _p_adt p_ad_child = get_ad_objects(1, sizeof(_p_tree_node));
            p_ad_child->data = child;
            queue_enqueue(p_queue, p_ad_child);
            child = child->p_rigth_sibling;
        }
        p_ad = queue_dequeue(p_queue);
    }

    return p_list;
}

static _p_list tree_depth_first_traverse_helper(_p_list p_list, _p_tree p_tree, bool is_root_first) {

    if (p_tree != NULL) {

        if (!is_root_first) {

            _p_tree_node child = p_tree->root->p_first_child;

            while (child != NULL) {

                _p_tree p_sub_tree = sub_tree(p_tree, child);
                tree_depth_first_traverse_helper(p_list, p_sub_tree, is_root_first);
                child = child->p_rigth_sibling;
            }

            _p_adt p_ad = get_ad_objects(1, sizeof(_p_tree_node));
            p_ad->data = p_tree->root;
            list_append(p_list, p_ad);

        } else {
            _p_tree_node child = p_tree->root->p_first_child;

            _p_adt p_ad = get_ad_objects(1, sizeof(_p_tree_node));
            p_ad->data = p_tree->root;
            list_append(p_list, p_ad);

            while (child != NULL) {

                _p_tree p_sub_tree = sub_tree(p_tree, child);
                tree_depth_first_traverse_helper(p_list, p_sub_tree, is_root_first);
                child = child->p_rigth_sibling;
            }
        }
    }

    return p_list;
}

_p_list tree_depth_first_traverse(_p_tree p_tree, bool is_root_first) {

    if (p_tree != NULL) {

        _p_list p_list = list_init(32);
        return tree_depth_first_traverse_helper(p_list, p_tree, is_root_first);
    }

    return NULL;
}

_p_binary_tree to_binary_tree(_p_tree p_tree) {


    return NULL;
}


static bool node_equals(void *data1, void *data2) {

    _p_tree_node root = ((_p_tree) data1)->root;
    _p_tree_node p_tree_node = (_p_tree_node) data2;

    return root == p_tree_node;
}

static bool ad_equals(void *data1, void *data2) {

    _p_tree p_tree = (_p_tree) data1;
    _p_tree_node root = p_tree->root;
    _p_adt p_ad = (_p_adt) data2;
    return adt_equals(root->p_ad, p_ad);
}

bool tree_existed(_p_tree p_tree, void *data, bool (*equals)(void *, void *)) {

    if (!equals(p_tree, data)) {

        _p_tree_node sibling = p_tree->root->p_rigth_sibling;

        while (sibling != NULL) {

            _p_tree p_sibling_tree = sub_tree(p_tree, sibling);

            if (!tree_existed(p_sibling_tree, data, equals)) {

                sibling = sibling->p_rigth_sibling;
            } else {

                return true;
            }
        }
        _p_tree_node child = p_tree->root->p_first_child;
        _p_tree p_sub_tree = sub_tree(p_tree, child);

        return p_sub_tree != NULL ? tree_existed(p_sub_tree, data, equals) : false;
    }

    return true;
}


bool tree_node_existed(_p_tree p_tree, _p_tree_node p_tree_node) {

    return tree_existed(p_tree, p_tree_node, node_equals);
}

bool tree_ad_existed(_p_tree p_tree, _p_adt p_ad) {

    return tree_existed(p_tree, p_ad, ad_equals);
}




