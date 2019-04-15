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

    unsigned bytes;
    void *data;
} _adt, *_p_adt;

/**
 * 条件判断
 */
typedef bool (*_p_func_if)(_p_adt p_ad);

/**
 * 打印
 */
typedef void (*_p_func_print)(_p_adt p_ad);

/**
 * 默认判断相等 p_ad1==p_ad2
 * @param p_ad1
 * @param p_ad2
 * @return true：相等
 */
bool adt_equals(_p_adt p_ad1, _p_adt p_ad2);

/**
 * 从系统pool中取number个对象，每个对象bytes个字节
 * @param size 对象个数
 * @param bytes 字节数
 * @return 第一个adt的地址
 */
_p_adt get_ads(unsigned size, unsigned bytes);

bool valid_data(_p_adt p_ad);

bool valid_ad(_p_adt p_ad);

#endif //DATA_STRUCTURE_ADT_H
