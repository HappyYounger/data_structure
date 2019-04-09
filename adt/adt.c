//
// Created by 杨光 on 2019/3/25.
//

#include <stddef.h>
#include <string.h>
#include "adt.h"
#include "../pool/pool.h"

extern _p_memory_pool p_memory_pool;

_p_adt adt_def_assigns(_p_adt p_ad1, _p_adt p_ad2) {

    if (p_ad1 != NULL && p_ad2 != NULL && p_ad1->data != NULL && p_ad2->data != NULL) {

        memcpy(p_ad1->data, p_ad2->data, p_ad1->bytes);
        return p_ad1;
    }

    return NULL;
}

bool adt_def_equals(_p_adt p_ad1, _p_adt p_ad2) {

    if (p_ad1 != NULL && p_ad2 != NULL && p_ad1->data != NULL && p_ad2->data != NULL) {

        char *value1, *value2;
        value1 = p_ad1->data;
        value2 = p_ad2->data;

        for (unsigned i = 0; i < p_ad1->bytes; ++i) {

            if (value1[i] != value2[i]) {

                return false;
            }
        }
        return true;
    }

    return false;
}

_p_adt pick_some_ad(unsigned number, unsigned bytes) {

    if (number > 0 && bytes > 0) {

        _p_adt p_ad = alloc_memory(p_memory_pool, sizeof(_adt) * number);

        if (p_ad != NULL) {

            void *data = alloc_memory(p_memory_pool, bytes * number);

            if (data != NULL) {
                for (int i = 0; i < number; ++i) {

                    p_ad[i].bytes = bytes;
                    p_ad[i].data = data + bytes * i;
                }
                return p_ad;
            }
        }
    }

    return NULL;
}

_p_func_adt_assigns assigns_func(_p_func_adt_assigns adt_assigns) {

    return adt_assigns == NULL ? adt_def_assigns : adt_assigns;
}

_p_func_adt_equals equals_func(_p_func_adt_equals adt_equals) {

    return adt_equals == NULL ? adt_def_equals : adt_equals;
}