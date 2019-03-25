//
// Created by 杨光 on 2019/3/14.
//

#include "pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *alloc_memory_pool(unsigned index);

static const void *block_start_address(const void *p_start, unsigned block_index) {

    return p_start + block_index * BLOCK_SIZE;
}

static void compact_pool(_p_memory_pool p_pool, unsigned pool_index) {

    _p_alloc_table p_alloc_table = p_pool->p_table_list->table_array[pool_index];

    const void *p_start = p_pool->pool_array[pool_index];

    void *p_realloc = p_start;

    _p_alloc_rec p_alloc_rec = p_alloc_table->p_rec_first;

    while (p_alloc_rec != NULL) {

        void *p_rec_address = block_start_address(p_realloc, p_alloc_rec->block_index);

        if (p_rec_address > p_realloc) {

            memmove(p_realloc, p_rec_address, p_alloc_rec->size);

            p_alloc_rec->block_index = (p_realloc - p_start) / BLOCK_SIZE;
            p_realloc = p_rec_address + p_alloc_rec->size;
        }

        p_alloc_rec = p_alloc_rec->p_next;
    }
}

static _p_alloc_table init_alloc_table() {

    _p_alloc_table p_alloc_table = malloc(sizeof(_alloc_table));

    if (p_alloc_table != NULL) {

        p_alloc_table->rec_size = 0;
        p_alloc_table->p_rec_first = p_alloc_table->p_rec_last = NULL;
    }

    return p_alloc_table;
}

static _p_table_list init_table_list() {

    _p_table_list p_table_list = malloc(sizeof(_table_list));

    if (p_table_list != NULL) {

        p_table_list->table_size = 1;
        p_table_list->table_array[0] = init_alloc_table();
    }

    return p_table_list;
}

static _p_table_list add_table(_p_table_list p_table_list) {

    if (p_table_list != NULL && p_table_list->table_size < TABLE_MAX) {

        _p_alloc_table p_alloc_table = init_alloc_table();

        if (p_alloc_table != NULL) {

            p_table_list->table_array[p_table_list->table_size++] = p_alloc_table;
        }
    }

    return NULL;
}

static _p_alloc_rec alloc_rec(unsigned block_index, unsigned size) {

    _p_alloc_rec p_alloc_rec = malloc(sizeof(_alloc_rec));

    if (p_alloc_rec != NULL) {

        p_alloc_rec->block_index = block_index;
        p_alloc_rec->size = size;

        return p_alloc_rec;
    }

    return NULL;
}

static void *add_alloc_rec(_p_alloc_table p_alloc_table, _p_alloc_rec p_alloc_rec) {

    if (p_alloc_table != NULL && p_alloc_rec != NULL) {

        if (p_alloc_table->p_rec_last == NULL) {

            p_alloc_table->p_rec_first = p_alloc_table->p_rec_last = p_alloc_rec;
            p_alloc_rec->p_next = p_alloc_rec->p_prev = NULL;
        } else {

            p_alloc_table->p_rec_last->p_next = p_alloc_rec;
            p_alloc_rec->p_prev = p_alloc_table->p_rec_last;
            p_alloc_rec->p_next = NULL;
            p_alloc_table->p_rec_last = p_alloc_rec;
        }

        ++p_alloc_table->rec_size;
        return p_alloc_table;
    }

    return NULL;
}

static void dump_alloc_rec(_p_alloc_rec p_alloc_rec) {

    if (p_alloc_rec != NULL) {

        free(p_alloc_rec);
    }
}

static void *remove_alloc_rec(_p_alloc_table p_alloc_table, _p_alloc_rec p_alloc_rec) {

    if (p_alloc_table != NULL && p_alloc_rec != NULL) {

        _p_alloc_rec p_current_rec = p_alloc_table->p_rec_first;

        while (p_current_rec != NULL) {

            if (p_current_rec == p_alloc_rec) {

                p_current_rec->p_prev->p_next = p_current_rec->p_next;

                dump_alloc_rec(p_alloc_rec);
                --p_alloc_table->rec_size;
                return p_alloc_table;
            }

            p_current_rec = p_current_rec->p_next;
        }
    }

    return NULL;
}

static void dump_alloc_table(_p_alloc_table p_alloc_table) {

    _p_alloc_rec p_alloc_rec;

    if (p_alloc_table != NULL) {

        while ((p_alloc_rec = p_alloc_table->p_rec_first) != NULL) {

            if (p_alloc_rec != NULL) {

                p_alloc_table->p_rec_first = p_alloc_rec->p_next;
                dump_alloc_rec(p_alloc_rec);
            }
        }
    }
    free(p_alloc_table);
}


static void *try_alloc(const void *p_start, unsigned length, _p_alloc_table p_alloc_table, unsigned size) {

    void *p_begin = p_start, *p_end;

    _p_alloc_rec p_alloc_rec = p_alloc_table->p_rec_first;

    if (p_alloc_rec == NULL) {

        p_end = p_start + length;

    } else {

        p_end = block_start_address(p_start, p_alloc_rec->block_index);

        while (p_alloc_rec != NULL) {

            if (p_end - p_begin >= size) {

                return p_begin;
            }

            p_begin = p_end + p_alloc_rec->size;
            p_alloc_rec = p_alloc_rec->p_next;
            p_end = p_alloc_rec == NULL ? p_start + length : block_start_address(p_start, p_alloc_rec->block_index);
        }
    }

    if (p_end - p_begin >= size) {

        return p_begin;
    }

    return NULL;
}


static _p_memory_pool expand_memory_pool(_p_memory_pool p_pool) {

    if (p_pool->pool_size < POOL_MAX) {

        add_table(p_pool->p_table_list);
        p_pool->pool_array[p_pool->pool_size] = alloc_memory_pool(p_pool->pool_size);
        ++p_pool->pool_size;

        return p_pool;
    }

    return NULL;
}

static void *try_alloc_memory(_p_memory_pool p_pool, unsigned size) {

    void *p_address = NULL, *p_start;

    for (unsigned i = 0; i < p_pool->pool_size; ++i) {

        p_start = p_pool->pool_array[i];
        _p_alloc_table p_alloc_table = p_pool->p_table_list->table_array[i];

        p_address = try_alloc(p_start, (i + 1) * POOL_BASE_SIZE, p_alloc_table, size);

        if (p_address != NULL) {

            unsigned block_index = (p_address - p_start) / BLOCK_SIZE;
            _p_alloc_rec p_alloc_rec = alloc_rec(block_index, size);

            add_alloc_rec(p_alloc_table, p_alloc_rec);

            return p_address;
        }

        if (i == p_pool->pool_size - 1) {

            if (expand_memory_pool(p_pool) == NULL) {

                return NULL;
            }
        }
    }

    return NULL;
}

//

_p_memory_pool init_pool() {

    _p_memory_pool p_pool = malloc(sizeof(_memory_pool));

    if (p_pool != NULL) {

        p_pool->pool_size = 1;
        p_pool->pool_array[0] = alloc_memory_pool(0);
        p_pool->p_table_list = init_table_list();
    }

    return p_pool;
}

void destroy_pool(_p_memory_pool p_pool) {

    if (p_pool != NULL) {

        for (int i = 0; i < p_pool->pool_size; ++i) {

            dump_alloc_table(p_pool->p_table_list->table_array[i]);
            free(p_pool->pool_array[i]);
        }

        free(p_pool);
    }
}

void *alloc_memory(_p_memory_pool p_pool, unsigned size) {

    if (p_pool != NULL) {

        return try_alloc_memory(p_pool, size);
    }

    return NULL;
}

void free_data(_p_memory_pool p_pool, void *p_data) {

    if (p_pool != NULL && p_data != NULL) {

        for (int i = 0; i < p_pool->pool_size; ++i) {

            if (p_data >= p_pool->pool_array[i] && p_data < p_pool->pool_array[i] + (i + 1) * POOL_BASE_SIZE) {

                _p_alloc_rec p_alloc_rec = p_pool->p_table_list->table_array[i]->p_rec_first;

                while (p_alloc_rec != NULL) {

                    void *p_rec_address = p_pool->pool_array[i] + p_alloc_rec->block_index * BLOCK_SIZE;

                    if (p_data == p_rec_address) {

                        dump_alloc_rec(p_alloc_rec);
                        return;
                    }
                    p_alloc_rec = p_alloc_rec->p_next;
                }
            }
        }
    }
}

static void *alloc_memory_pool(unsigned index) {

    return malloc(2 ^ index * POOL_BASE_SIZE);
}