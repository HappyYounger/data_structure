//
// Created by 杨光 on 2019/3/25.
//

#include "list.h"
#include <stdlib.h>
#include <string.h>

static const int _DEFAULT_LIST_CAPACITY_ = 16;

_p_list list_init(unsigned capacity,
                  _p_func_adt_assigns adt_assigns,
                  _p_func_adt_bits_assigns bits_assigns,
                  _p_func_adt_equals adt_equals,
                  _p_func_adt_bits_equals bits_equals) {

    _p_list p_list = alloc_memory(sizeof(_list));

    if (p_list != NULL) {

        p_list->size = 0;
        p_list->capacity = capacity < _DEFAULT_LIST_CAPACITY_ ? _DEFAULT_LIST_CAPACITY_ : capacity;

        p_list->list = alloc_memory(sizeof(_p_adt) * p_list->capacity);

        p_list->adt_assigns = assigns_func(adt_assigns);
        p_list->adt_equals = equals_func(adt_equals);
        p_list->adt_bits_assigns = bits_assigns_func(bits_assigns);
        p_list->adt_bits_equals = bits_assigns_func(bits_equals);

        return p_list;
    }

    return NULL;
}

_p_list list_extend(_p_list p_list) {

    if (p_list != NULL) {

        _p_adt *old_list = p_list->list;

        p_list->capacity *= 2;
        p_list->list = alloc_memory(sizeof(_p_adt) * p_list->capacity);

        memcpy(p_list->list, old_list, sizeof(_adt) * p_list->capacity / 2);

        free(old_list);
        return p_list;
    }
    return NULL;
}

int list_find(_p_list p_list, _p_adt p_ad) {

    if (p_list != NULL && p_ad != NULL) {

        for (int i = 0; i < p_list->size; ++i) {

            if (p_list->adt_equals(p_list->list[i], p_ad)) {

                return i;
            }
        }
    }

    return -1;
}

int list_remove(_p_list p_list, _p_adt p_ad) {

    if (p_list != NULL && p_ad != NULL && p_ad->data != NULL) {
        int index = list_find(p_list, p_ad);

        if (index > -1) {

            return list_remove_at(p_list, index);
        }

        return index;
    }

    return -1;
}

int list_remove_at(_p_list p_list, unsigned index) {

    if (p_list != NULL) {

        memmove(p_list->list + index, p_list->list + index + 1, sizeof(_p_adt) * (p_list->size - index - 1));
        --p_list->size;
        return index;
    }

    return -1;
}

int list_remove_all(_p_list p_list, _p_adt p_ad) {

    int count = 0;
    for (int i = 0; i < p_list->size;) {

        _p_adt p_ad1 = p_list->list[i];

        if ((p_list->adt_equals != NULL && p_list->adt_equals(p_ad1, p_ad))
            ||
            (p_list->adt_equals == NULL && p_ad1->data == p_ad->data)) {

            list_remove_at(p_list, i);
            ++count;
            continue;
        }
        ++i;
    }

    return count;
}

int list_remove_if(_p_list p_list, _p_func_if p_func_if) {

    int count;
    for (int i = 0; i < p_list->size;) {

        if (p_func_if(p_list->list[i])) {

            list_remove_at(p_list, i);
            ++count;
            continue;
        }
        ++i;
    }

    return count;
}

int list_insert(_p_list p_list, unsigned index, _p_adt p_ad) {

    if (p_list != NULL) {

        if (p_list->size == p_list->capacity) {

            list_extend(p_list);
        }

        ++p_list->size;
        list_move(p_list, index, index + 1);
        p_list->list[index] = p_ad;

        return index;
    }

    return -1;
}

int list_append(_p_list p_list, _p_adt p_ad) {

    if (p_list->size == p_list->capacity) {

        list_extend(p_list);
    }

    p_list->list[p_list->size] = p_ad;
    ++p_list->size;

    return p_list->size - 1;
}

void list_clear(_p_list p_list) {

    p_list->size = 0;

}

int list_move(_p_list p_list, unsigned from, unsigned to) {

    if (p_list != NULL) {

        memmove(p_list->list + to, p_list->list + from, sizeof(_p_adt) * (p_list->size - from));
        return to;
    }

    return -1;
}

void list_print(_p_list p_list, _p_func_print print_ad) {

    if (p_list != NULL && print_ad != NULL) {

        for (int i = 0; i < p_list->size; ++i) {

            print_ad(p_list->list[i]);
        }
    }
}
