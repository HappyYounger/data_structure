//
// Created by 杨光 on 2019/3/25.
//

#include <stddef.h>
#include <string.h>
#include "adt.h"
#include "../pool/pool.h"

extern _p_memory_pool p_memory_pool;

bool adt_equals(_p_adt p_ad1, _p_adt p_ad2) {

    return valid_ad(p_ad1) &&valid_ad(p_ad2) ? p_ad1 == p_ad2 : NULL;
}

_p_adt get_ads(unsigned size, unsigned bytes) {

    if (size > 0) {

        _p_adt p_ad = alloc_memory((sizeof(_adt) + bytes) * size);

        for (int i = 0; i < size; ++i) {

            (p_ad + i)->data = p_ad + sizeof(_adt) * size + i * bytes;
            (p_ad + i)->bytes = bytes;
        }
        return p_ad;
    }

    return NULL;
}

bool valid_data(_p_adt p_ad) {

    return p_ad != NULL && p_ad->data != NULL;
}

bool valid_ad(_p_adt p_ad) {

    return p_ad != NULL;
}
