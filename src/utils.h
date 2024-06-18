#ifndef S21_UTILS_H_
#define S21_UTILS_H_

#include <stdlib.h>

#include "s21_string.h"

int max(int a, int b);
int min(int a, int b);

void copy(const char *src, char **dest, size_t size);
char *is_number(char ch);
void reverse(char *arr, size_t size);

#endif