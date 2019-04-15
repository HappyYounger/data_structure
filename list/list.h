//
// Created by 杨光 on 2019/3/25.
//

#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "../adt/adt.h"
#include "../pool/pool.h"

typedef struct {

    unsigned size;
    unsigned capacity;
    _p_adt *list;

} _list, *_p_list;

/**
 * 初始化list
 * @param capacity 容量
 * @param adt_assigns 赋值函数
 * @param adt_equals 判断相等函数
 * @return list地址，失败返回NULL
 */
_p_list list_init(unsigned capacity);

/**
 * list容量增倍
 * @param p_list list地址
 * @return list地址，失败返回NULL
 */
_p_list list_extend(_p_list p_list);

/**
 * 查找
 * @param p_list list地址
 * @param p_ad 要查找的数据
 * @return 索引，失败返回-1
 */
int list_find(_p_list p_list, _p_adt p_ad);

/**
 * 删除一个
 * @param p_list list地址
 * @param p_ad 要查找的数据
 * @return 索引，失败返回-1
 */
int list_remove(_p_list p_list, _p_adt p_ad);

/**
 * 删除指定索引的数据
 * @param p_list list地址
 * @param index 索引
 * @return 索引，失败返回-1
 */
int list_remove_at(_p_list p_list, unsigned index);

/**
 * 删除所有
 * @param p_list list地址
 * @param p_ad 删除的数据
 * @return 删除的个数
 */
int list_remove_all(_p_list p_list, _p_adt p_ad);

/**
 * 删除所有符合条件的数据
 * @param p_list list地址
 * @param p_func_if 条件指针
 * @return 删除的个数
 */
int list_remove_if(_p_list p_list, _p_func_if p_func_if);

/**
 * 在指定索引上插入数据
 * @param p_list list地址
 * @param index 索引
 * @param p_ad 数据
 * @return 索引，失败返回-1
 */
int list_insert(_p_list p_list, unsigned index, _p_adt p_ad);

/**
 * 在最后添加数据
 * @param p_list list地址
 * @param p_ad 数据
 * @return 索引，失败返回-1
 */
int list_append(_p_list p_list, _p_adt p_ad);

/**
 * 清空
 * @param p_list
 */
void list_clear(_p_list p_list);

/**
 * 移动数据
 * @param p_list list地址
 * @param from 从索引
 * @param to 到索引
 * @return 索引，失败返回-1
 */
int list_move(_p_list p_list, unsigned from, unsigned to);

/**
 * 打印列表
 * @param p_list list地址
 * @param p_func_print 打印函数指针
 */
void list_print(_p_list p_list, _p_func_print p_func_print);


#endif //DATA_STRUCTURE_LIST_H
