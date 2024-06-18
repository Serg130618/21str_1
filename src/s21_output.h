#ifndef S21_OUTPUT
#define S21_OUTPUT

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "utils.h"

void s21_sputchar(char **out, char c);

#define s21_sputchars(buffer, c, loop) loop s21_sputchar(buffer, c)

void s21_sput_uint(char **out, uint64_t value);

void s21_sput_int(char **out, int64_t value, bool print_plus, bool print_space);

void s21_sput_float(char **out, long double value, int precision,
                    bool print_plus, bool print_point, bool print_space);

void s21_sput_float_exponential(char **out, long double value, int precision,
                                bool print_plus, bool print_space,
                                char exponent_sign);

void s21_sputs(char **out, const char *value);

void s21_sput_hex(char **out, uint64_t value, char *hex_table);

void s21_sput_octal(char **out, uint64_t value, bool print_zero);

#endif
