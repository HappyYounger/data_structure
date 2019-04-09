//
// Created by 杨光 on 2019/3/25.
//

#include "linked_list.h"
#include <stddef.h>

extern _p_memory_pool p_memory_pool;

_p_linked_list_node linked_list_find(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_linked_list != NULL && p_ad != NULL && p_ad->data != NULL) {

        _p_linked_list_node p_cur = p_linked_list->first;

        while (p_cur != NULL) {

            if ((p_linked_list->adt_equals != NULL && p_linked_list->adt_equals(p_cur->p_ad, p_ad)) ||
                (p_linked_list->adt_equals == NULL && adt_def_equals(p_cur->p_ad, p_ad))) {

                return p_cur;
            }

            p_cur = p_cur->p_next;
        }
    }

    return NULL;
}


_p_linked_list linked_list_init(_p_func_adt_assigns adt_assigns,
                                _p_func_adt_equals adt_equals) {

    _p_linked_list p_linked_list = NULL;

    if (p_memory_pool != NULL) {

        p_linked_list = alloc_memory(p_memory_pool, sizeof(_linked_list));

        if (p_linked_list != NULL) {

            p_linked_list->size = 0;
            p_linked_list->first = p_linked_list->last = NULL;

            p_linked_list->adt_assigns = assigns_func(adt_assigns);
            p_linked_list->adt_equals = equals_func(adt_equals);
        }
    }

    return p_linked_list;
}


_p_linked_list_node linked_list_insert_before(_p_linked_list p_linked_list,
                                              _p_adt p_des_ad,
                                              _p_adt p_ad) {

    if (p_memory_pool != NULL && p_linked_list != NULL && p_des_ad != NULL && p_ad != NULL) {

        _p_linked_list_node p_des_node = linked_list_find(p_linked_list, p_des_ad);
        if (p_des_node != NULL) {

            _p_linked_list_node p_linked_list_node = alloc_memory(p_memory_pool, sizeof(struct linked_list_node));

            p_linked_list_node->p_ad = p_ad;

            p_linked_list_node->p_next = p_des_node;
            p_linked_list_node->p_previous = p_des_node->p_previous;
            p_linked_list_node->p_previous->p_next = p_linked_list_node;
            p_des_node->p_previous = p_linked_list_node;

            ++p_linked_list->size;
            return p_linked_list_node;
        }
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_after(_p_linked_list p_linked_list,
                                             _p_adt p_des_ad,
                                             _p_adt p_ad) {

    if (p_memory_pool != NULL && p_linked_list != NULL && p_des_ad != NULL && p_ad != NULL) {

        _p_linked_list_node p_des_node = linked_list_find(p_linked_list, p_des_ad);
        if (p_des_node != NULL) {

            _p_linked_list_node p_linked_list_node = alloc_memory(p_memory_pool, sizeof(struct linked_list_node));

            p_linked_list_node->p_ad = p_ad;

            p_linked_list_node->p_next = p_des_node->p_next;
            p_linked_list_node->p_previous = p_des_node;

            p_des_node->p_next = p_linked_list_node;
            p_linked_list_node->p_next->p_previous = p_linked_list_node;

            ++p_linked_list->size;
            return p_linked_list_node;
        }
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_first_before(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_memory_pool != NULL && p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(p_memory_pool, sizeof(_linked_list_node));

        p_linked_list_node->p_ad = p_ad;
        if (p_linked_list->first == NULL) {

            p_linked_list->first = p_linked_list->last = p_linked_list_node;

            p_linked_list_node->p_previous = p_linked_list_node->p_next = NULL;
        } else {

            p_linked_list_node->p_previous = NULL;
            p_linked_list_node->p_next = p_linked_list->first;
            p_linked_list->first->p_previous = p_linked_list_node;
            p_linked_list->first = p_linked_list_node;
        }
        ++p_linked_list->size;
        return p_linked_list_node;
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_first_after(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_memory_pool != NULL && p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(p_memory_pool, sizeof(_linked_list_node));

        p_linked_list_node->p_ad = p_ad;
        if (p_linked_list->first == NULL) {

            p_linked_list->first = p_linked_list->last = p_linked_list_node;

            p_linked_list_node->p_previous = p_linked_list_node->p_next = NULL;
        } else {

            p_linked_list_node->p_previous = p_linked_list->first;
            p_linked_list_node->p_next = p_linked_list->first->p_next;
            p_linked_list_node->p_next->p_previous = p_linked_list_node;
            p_linked_list->first->p_next = p_linked_list_node;
        }
        ++p_linked_list->size;
        return p_linked_list_node;
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_last_before(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_memory_pool != NULL && p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(p_memory_pool, sizeof(_linked_list_node));

        p_linked_list_node->p_ad = p_ad;
        if (p_linked_list->last == NULL) {

            p_linked_list->first = p_linked_list->last = p_linked_list_node;

            p_linked_list_node->p_previous = p_linked_list_node->p_next = NULL;
        } else {

            p_linked_list_node->p_next = p_linked_list->last;
            p_linked_list_node->p_previous = p_linked_list->last->p_previous;
            p_linked_list_node->p_previous->p_next = p_linked_list_node;
            p_linked_list->last->p_previous = p_linked_list_node;
        }
        ++p_linked_list->size;
        return p_linked_list_node;
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_last_after(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_memory_pool != NULL && p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(p_memory_pool, sizeof(_linked_list_node));

        p_linked_list_node->p_ad = p_ad;
        if (p_linked_list->last == NULL) {

            p_linked_list->first = p_linked_list->last = p_linked_list_node;

            p_linked_list_node->p_previous = p_linked_list_node->p_next = NULL;
        } else {

            p_linked_list_node->p_next = NULL;
            p_linked_list_node->p_previous = p_linked_list->last;
            p_linked_list->last->p_next = p_linked_list_node;
            p_linked_list->last = p_linked_list_node;
        }
        ++p_linked_list->size;
        return p_linked_list_node;
    }

    return NULL;
}

_p_linked_list linked_list_remove(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = linked_list_find(p_linked_list, p_ad);

        if (p_linked_list_node != NULL) {

            if (p_linked_list_node->p_previous != NULL) {

                p_linked_list_node->p_previous->p_next = p_linked_list_node->p_next;
            }

            if (p_linked_list_node->p_next != NULL) {

                p_linked_list_node->p_next->p_previous = p_linked_list_node->p_previous;
            }

            --p_linked_list->size;
        }

        return p_linked_list;
    }

    return NULL;
}

_p_linked_list linked_list_clear(_p_linked_list p_linked_list) {

    if (p_linked_list != NULL) {

        p_linked_list->first = p_linked_list->last = NULL;
        p_linked_list->size = 0;
    }

    return p_linked_list;
}