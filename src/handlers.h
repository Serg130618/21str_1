#ifndef HANDLERS_H
#define HANDLERS_H

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "format_unit.h"
#include "s21_output.h"
#include "s21_string.h"
#include "utils.h"

#define DEFAULT_FLOAT_PRECISION 6

enum integer_type { UNSIGNED = 0, SIGNED = 1 };

typedef struct format_unit format_unit_t;
int handle_format_unit(format_unit_t format_unit, char **str, va_list args);

#endif