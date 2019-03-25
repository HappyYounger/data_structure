//
// Created by 杨光 on 2019/3/14.
//

#ifndef DATA_STRUCTURE_SAMPLE_POOL_H
#define DATA_STRUCTURE_SAMPLE_POOL_H


#define POOL_MAX 10
#define TABLE_MAX POOL_MAX

//#define POOL_BASE_SIZE 8192
#define POOL_BASE_SIZE 8
#define BLOCK_SIZE 4

/**
 * 分配记录
 * block_index：块索引，每块4字节
 * size：字节数
 *
 */
typedef struct AllocRec {

    unsigned block_index;
    unsigned size;

    struct AllocRec *p_next;
    struct AllocRec *p_prev;

} _alloc_rec, *_p_alloc_rec;

/*
 * 分配表
 * rec_size：表中记录的数量
 * p_rec_first：第一条记录
 * p_rec_last：最后一条记录
 */
typedef struct AllocTable {

    unsigned rec_size;
    _p_alloc_rec p_rec_first;
    _p_alloc_rec p_rec_last;

} _alloc_table, *_p_alloc_table;

/*
 * 分配表列表
 * table_size：表数量，与内存池数量一致
 * table_array：分配表数组，记录每个分配表的地址，最大值是TABLE_MAX
 */
typedef struct AllocTableList {

    unsigned table_size;
    _p_alloc_table table_array[TABLE_MAX];

} _table_list, *_p_table_list;

/*
 * 内存池
 *
 */

typedef struct MemoryPool {

    unsigned pool_size;
    void *pool_array[POOL_MAX];
    _p_table_list p_table_list;
} _memory_pool, *_p_memory_pool;

/*
 * 初始化内存池
 *
 * return：内存池对象地址
 */
_p_memory_pool init_pool();

/*
 *克隆数据
 * p_pool：内存池
 * size：字节数
 *
 * return：地址
 *
 */

/*
 * 分配空间
 * p_pool：内存池
 * size：数据的大小
 *
 * return：克隆的对象的地址
 */
void *alloc_memory(_p_memory_pool p_pool, unsigned size);

/*
 * 释放对象
 * p_pool：内存池
 * p_data：释放的对象的地址
 *
 */
void free_data(_p_memory_pool p_pool, void *p_data);

/*
 * 销毁内存池
 */
void destroy_pool(_p_memory_pool p_pool);

#endif //DATA_STRUCTURE_SAMPLE_POOL_H
