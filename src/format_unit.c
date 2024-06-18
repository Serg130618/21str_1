#include "format_unit.h"

#define HEX_LOWER_CASE "0123456789abcdefx"
#define HEX_UPPER_CASE "0123456789ABCDEFX"

bool parse_specifier(struct format_unit *this, uint8_t *ls, uint8_t *Ls,
                     uint8_t *hs, char current) {
  char *specifiers = "dufceEspxXgGoin";
#ifdef __linux__
  if (current == 'L') *Ls += 1;
  if (current == 'L') *ls += 2;
  if (current == 'l') *ls += 1;
  if (current == 'h') *hs += 1;
#else
#ifdef __APPLE__
  if (current == 'L') *Ls += 1;
  if (current == 'l') *ls += 1;
  if (current == 'h') *hs += 1;
#endif
#endif

  if (s21_strchr(specifiers, current)) {
    if (current == 'd') this->data_type = d;
    if (current == 'u') this->data_type = u;
    if (current == 'f') this->data_type = f;
    if (current == 'e') this->data_type = e, this->exponent_sign = 'e';
    if (current == 'E') this->data_type = e, this->exponent_sign = 'E';
    if (current == 'g') this->data_type = g, this->exponent_sign = 'e';
    if (current == 'G') this->data_type = g, this->exponent_sign = 'E';
    if (current == 'c') this->data_type = c;
    if (current == 's') this->data_type = s;
    if (current == 'p') this->data_type = p;
    if (current == 'o') this->data_type = o;
    if (current == 'x') this->data_type = x, this->hex = (char *)HEX_LOWER_CASE;
    if (current == 'X') this->data_type = x, this->hex = (char *)HEX_UPPER_CASE;
    if (current == 'n') this->data_type = n;
    if (current == 'i') this->data_type = d, this->sign_forced = 1;
    return true;
  }
  return false;
}

void apply_sizes(struct format_unit *this, uint8_t _ls, uint8_t _Ls,
                 uint8_t _hs) {
  if (_ls == 1) {
    if (this->data_type == d) this->data_type = ld;
    if (this->data_type == u) this->data_type = lu;
    if (this->data_type == o) this->data_type = lo;
    if (this->data_type == x) this->data_type = lx;
    if (this->data_type == f) this->data_type = lf;
    if (this->data_type == c) this->data_type = lc;
    if (this->data_type == s) this->data_type = ls;
  }

  if (_ls >= 2) {
    if (this->data_type == d) this->data_type = lld;
    if (this->data_type == u) this->data_type = llu;
    if (this->data_type == o) this->data_type = llo;
    if (this->data_type == x) this->data_type = llx;
  }

  if (_Ls >= 1) {
    if (this->data_type == f) this->data_type = Lf;
    if (this->data_type == e) this->data_type = Le;
    if (this->data_type == g) this->data_type = Lg;
  }

  if (_hs == 1) {
    if (this->data_type == d) this->data_type = hd;
    if (this->data_type == u) this->data_type = hu;
    if (this->data_type == o) this->data_type = ho;
    if (this->data_type == x) this->data_type = hx;
  }

  if (_hs >= 2) {
    if (this->data_type == d) this->data_type = hhd;
    if (this->data_type == u) this->data_type = hhu;
    if (this->data_type == o) this->data_type = hho;
    if (this->data_type == x) this->data_type = hhx;
  }
}

bool is_float(enum type _dt) {
  if (_dt == f) return true;
  if (_dt == e) return true;
  if (_dt == g) return true;
  return false;
}

struct format_unit s21_parse_format(char **format, va_list *args) {
  if (**format != '%') fprintf(stderr, "Error parsing format\n"), exit(1);

  struct format_unit result = {.data_type = d,
                               .align = RIGHT,
                               .width = 0,
                               .precision = -1,
                               .sign_forced = false,
                               .number_sign = false,
                               .space_forced = false,
                               .filler_symbol = ' ',
                               .exponent_sign = 'e',
                               .hex = NULL};
  uint8_t ls = 0;
  uint8_t Ls = 0;
  uint8_t hs = 0;
  bool is_floating_point = false;

  while (true) {
    char ch = **format;
    if (ch == ' ') result.space_forced = true;
    if (ch == '.') is_floating_point = true;
    if (ch == '#') result.number_sign = true;
    if (ch == '-') result.align = LEFT;
    if (ch == '+') result.sign_forced = true;
    if (ch == '*') {
      if (is_floating_point)
        result.precision = va_arg(*args, int);
      else
        result.width = va_arg(*args, int);
    }

    if (is_number(ch)) {
      if (is_floating_point) {
        if (result.precision < 0) result.precision = 0;
        result.precision = result.precision * 10 + (ch - '0');
      } else {
        if ((result.width == 0) && (ch == '0'))
          result.filler_symbol = '0';
        else
          result.width = result.width * 10 + (ch - '0');
      }
    }
    if (parse_specifier(&result, &ls, &Ls, &hs, ch)) break;

    (*format)++;
  }

  if (result.precision < 0) {
    if (is_float(result.data_type))
      result.precision = 6;
    else
      result.precision = 0;
  }

  if (!is_float(result.data_type)) {
    result.width =
        (result.width > result.precision) ? result.width : result.precision;
  }

  apply_sizes(&result, ls, Ls, hs);
  return result;
}

#undef HEX_LOWER_CASE
#undef HEX_UPPER_CASE