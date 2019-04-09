//
// Created by 杨光 on 2019/3/27.
//

#ifndef DATA_STRUCTURE_EXPRESSION_H
#define DATA_STRUCTURE_EXPRESSION_H

#include <stdbool.h>
#include <stddef.h>

char *strip_white_space(const char *infix_expression);

bool is_invalid_expression(const char *infix_expression);

char *get_postfix_expression(const char *infix_expression);

double cal_postfix_expression();

#endif //DATA_STRUCTURE_EXPRESSION_H
