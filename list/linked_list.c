//
// Created by 杨光 on 2019/3/25.
//

#include "linked_list.h"
#include <stddef.h>

_p_linked_list_node linked_list_find_cond(_p_linked_list p_linked_list, _p_func_cond func_cond, _p_adt p_ad) {

    _p_func_cond cond = func_cond == NULL ? adt_equals : func_cond;

    if (p_linked_list != NULL && p_ad != NULL && p_ad->data != NULL) {

        _p_linked_list_node p_cur = p_linked_list->first;

        while (p_cur != NULL) {

            if (cond(p_cur->p_ad, p_ad)) {

                return p_cur;
            }

            p_cur = p_cur->p_next;
        }
    }

    return NULL;
}


_p_linked_list linked_list_init() {

    _p_linked_list p_linked_list = alloc_memory(sizeof(_linked_list));

    if (p_linked_list != NULL) {

        p_linked_list->size = 0;
        p_linked_list->first = p_linked_list->last = NULL;
        return p_linked_list;
    }

    return p_linked_list;
}


_p_linked_list_node linked_list_insert_before(_p_linked_list p_linked_list,
                                              _p_adt p_des_ad,
                                              _p_adt p_ad) {

    if (p_linked_list != NULL && valid_data(p_des_ad) && valid_ad(p_ad)) {

        _p_linked_list_node p_des_node = linked_list_find_cond(p_linked_list, NULL, p_des_ad);
        if (p_des_node != NULL) {

            _p_linked_list_node p_linked_list_node = alloc_memory(sizeof(struct linked_list_node));

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

    if (p_linked_list != NULL && p_des_ad != NULL && p_ad != NULL) {

        _p_linked_list_node p_des_node = linked_list_find_cond(p_linked_list, NULL, p_des_ad);
        if (p_des_node != NULL) {

            _p_linked_list_node p_linked_list_node = alloc_memory(sizeof(struct linked_list_node));

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

    if (p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(sizeof(_linked_list_node));

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

    if (p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(sizeof(_linked_list_node));

        p_linked_list_node->p_ad = p_ad;

        if (p_linked_list->first == NULL) {

            p_linked_list->first = p_linked_list->last = p_linked_list_node;
            p_linked_list_node->p_previous = p_linked_list_node->p_next = NULL;
        } else {

            p_linked_list_node->p_previous = p_linked_list->first;
            p_linked_list_node->p_next = p_linked_list->first->p_next;
            if (p_linked_list_node->p_next != NULL) {

                p_linked_list_node->p_next->p_previous = p_linked_list_node;
            } else {

                p_linked_list->last = p_linked_list_node;
            }
            p_linked_list->first->p_next = p_linked_list_node;
        }
        ++p_linked_list->size;
        return p_linked_list_node;
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_last_before(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(sizeof(_linked_list_node));

        p_linked_list_node->p_ad = p_ad;

        if (p_linked_list->last == NULL) {

            p_linked_list->first = p_linked_list->last = p_linked_list_node;

            p_linked_list_node->p_previous = p_linked_list_node->p_next = NULL;
        } else {

            p_linked_list_node->p_next = p_linked_list->last;
            p_linked_list_node->p_previous = p_linked_list->last->p_previous;
            if (p_linked_list_node->p_previous != NULL) {

                p_linked_list_node->p_previous->p_next = p_linked_list_node;
            } else {

                p_linked_list->first = p_linked_list_node;
            }
            p_linked_list->last->p_previous = p_linked_list_node;
        }
        ++p_linked_list->size;
        return p_linked_list_node;
    }

    return NULL;
}

_p_linked_list_node linked_list_insert_last_after(_p_linked_list p_linked_list, _p_adt p_ad) {

    if (p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = alloc_memory(sizeof(_linked_list_node));

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

_p_linked_list linked_list_remove_cond(_p_linked_list p_linked_list, _p_func_cond func_cond, _p_adt p_ad) {

    if (p_linked_list != NULL && p_ad != NULL) {

        _p_linked_list_node p_linked_list_node = linked_list_find_cond(p_linked_list, func_cond, p_ad);

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

void print_linked_list(_p_linked_list p_linked_list, _p_func_print p_func_print) {

    if (p_linked_list != NULL) {

        _p_linked_list_node p_current_node = p_linked_list->first;
        while (p_current_node != NULL) {

            p_func_print(p_current_node->p_ad);
            p_current_node = p_current_node->p_next;
        }
    }
}
