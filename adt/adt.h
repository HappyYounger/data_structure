//
// Created by 杨光 on 2019/3/25.
//

#ifndef DATA_STRUCTURE_ADT_H
#define DATA_STRUCTURE_ADT_H

#include <stdbool.h>

/**
 * data:对象的地址
 * bytes:对象的大小
 */
typedef struct adt {

    void *data;
    unsigned bytes;
} _adt, *_p_adt;

/**
 * 赋值
 */
typedef _p_adt (*_p_func_adt_assigns)(_p_adt* p_ad1, _p_adt p_ad2);

/**
 * 按字节赋值
 */
typedef _p_adt (*_p_func_adt_bits_assigns)(_p_adt p_ad1, _p_adt p_ad2);

/**
 * 判断相等
 */
typedef bool (*_p_func_adt_equals)(_p_adt p_ad1, _p_adt p_ad2);

/**
 * 按字节相等
 */
typedef bool (*_p_func_adt_bits_equals)(_p_adt p_ad1, _p_adt p_ad2);

/**
 * 条件判断
 */
typedef bool (*_p_func_if)(_p_adt p_ad);

/**
 * 打印
 */
typedef void (*_p_func_print)(_p_adt p_ad);

/**
 * 默认赋值函数 p_ad1=p_ad2
 * @param p_ad1
 * @param p_ad2
 * @return p_ad1
 */
_p_adt adt_def_assigns(_p_adt* pp_ad1, _p_adt p_ad2);


/**
 * 拷贝赋值函数 按字节拷贝
 * @param p_ad1
 * @param p_ad2
 * @return p_ad1
 */
_p_adt adt_bits_assigns(_p_adt p_ad1, _p_adt p_ad2);


/**
 * 默认判断相等 p_ad1==p_ad2
 * @param p_ad1
 * @param p_ad2
 * @return true：相等
 */
bool adt_def_equals(_p_adt p_ad1, _p_adt p_ad2);

/**
 * 按字节判断相等
 * @param p_ad1
 * @param p_ad2
 * @return true：相等
 */
bool adt_bits_equals(_p_adt p_ad1, _p_adt p_ad2);

/**
 * 从系统pool中取number个对象，每个对象bytes个字节
 * @param size 对象个数
 * @param bytes 字节数
 * @return 第一个adt的地址
 */
_p_adt get_ads(unsigned size, unsigned bytes);

_p_func_adt_assigns assigns_func(_p_func_adt_assigns adt_assigns);

_p_func_adt_bits_assigns bits_assigns_func(_p_func_adt_bits_assigns bits_assign);

_p_func_adt_equals equals_func(_p_func_adt_equals adt_equals);

_p_func_adt_bits_equals bits_equals_func(_p_func_adt_bits_equals bits_equals);

bool valid_data(_p_adt p_ad);

#endif //DATA_STRUCTURE_ADT_H
