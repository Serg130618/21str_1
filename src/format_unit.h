#ifndef FORMAT_UNIT_H
#define FORMAT_UNIT_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "bool.h"
#include "s21_string.h"
#include "utils.h"

enum position { LEFT, RIGHT };
enum type {
  hhd,
  hd,
  d,
  ld,
  lld,

  hhu,
  hu,
  u,
  lu,
  llu,

  hho,
  ho,
  o,
  lo,
  llo,

  hhx,
  hx,
  x,
  lx,
  llx,

  f,
  lf,
  Lf,

  c,
  lc,

  e,
  Le,

  g,
  Lg,

  s,
  ls,

  p,
  n
};

struct format_unit {
  enum type data_type;  // %d %ld %c %s
  enum position align;  // -
  int width;            // (num) or *
  int precision;        // .num or .*
  bool sign_forced;     // +
  bool space_forced;    // "space"
  bool number_sign;     // #
  char filler_symbol;   // '0' or ' '
  char exponent_sign;   // 2e10 or 2E10 (%e / %E)
  char *hex;            // hex table (uppercase or lowercase) (%x / %X)
};

bool parse_specifier(struct format_unit *this, uint8_t *ls, uint8_t *Ls,
                     uint8_t *hs, char current);

void apply_sizes(struct format_unit *format_unit, uint8_t ls, uint8_t _Ls,
                 uint8_t hs);

struct format_unit s21_parse_format(char **format, va_list *args);

#endif