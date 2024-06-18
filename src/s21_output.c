#include "s21_output.h"

void s21_sputchar(char **out, char c) { *((*out)++) = c; }

void s21_sput_number(char **out, uint64_t value) {
  uint_fast8_t size = 0;
  char *start = *out;

  do {
    s21_sputchar(out, '0' + value % 10);
    ++size;
  } while (value /= 10);

  reverse(start, size);
}

void s21_sput_uint(char **out, uint64_t value) { s21_sput_number(out, value); }

void s21_sput_int(char **out, int64_t value, bool print_plus,
                  bool print_space) {
  if (value < 0) {
    s21_sputchar(out, '-');
    value = -value;
  } else if (print_plus)
    s21_sputchar(out, '+');
  else if (print_space)
    s21_sputchar(out, ' ');
  s21_sput_number(out, value);
}

long double s21_sput_float_integer(char **out, long double value) {
  if (floorl(value) == 0.0) {
    s21_sputchar(out, '0');
  } else {
    int integer_digits = ceill(log10l(value));
    for (int i = 0; i < integer_digits; ++i) {
      s21_sputchar(out, '0' + (int)(value / powl(10, integer_digits - i - 1)));
      value -= (int)(value / powl(10, integer_digits - i - 1)) *
               powl(10, integer_digits - i - 1);
    }
  }
  return value;
}

void s21_sput_float_fraction(char **out, long double value, int precision,
                             bool print_point) {
  if (print_point || (precision != 0)) s21_sputchar(out, '.');
  if (precision == 0) return;

  for (int i = 0; i < precision - 1; ++i) {
    value *= 10;
    s21_sputchar(out, '0' + (int)floorl(value));
    value -= (int)floorl(value);
  }
  value *= 10;
  if (roundl(value) >= 10.0) {
    s21_sputchar(out, '0');
    char *end = *out;
    while (**out == '9') *((*out)--) = '0';
    *((*out) - 2) += 1;
    *out = end;
  } else
    s21_sputchar(out, '0' + (int)roundl(value));
}

void s21_sput_float(char **out, long double value, int precision,
                    bool print_plus, bool print_point, bool print_space) {
  if (isnan(value)) {
    s21_sputs(out, "nan");
    return;
  }

  int sign = 0;
  if (copysign(1.0, value) < 0.0) {
    s21_sputchar(out, '-');
    value = -value;
  } else if (print_plus) {
    s21_sputchar(out, '+');
  } else if (print_space) {
    s21_sputchar(out, ' ');
  }

  if (isinf(value)) {
    s21_sputs(out, "inf");
    return;
  }

  char *start = *out;
  s21_sput_float_fraction(out, s21_sput_float_integer(out, value), precision,
                          print_point);

  bool plus = false;
  for (char *rev = *out - 1; rev >= start; rev--) {
    if (*rev == '.') continue;
    if (plus) {
      if (*rev == '9') {
        *rev = '0';
      } else if (*rev == '+') {
        *rev = '1';
        sign = '+';
      } else if (*rev == '-') {
        *rev = '1';
        sign = '-';
      } else {
        *rev += 1;
        plus = false;
      }
    }
    if (*rev == ':') {
      plus = true;
      *rev = '0';
    }
  }

  if (sign) {
    for (int i = (int)(*out - start) - 1; i >= 0; i--) {
      start[i + 1] = start[i];
    }
    start[0] = (char)sign;
  }
}

void s21_sput_float_exponential(char **out, long double value, int precision,
                                bool print_plus, bool print_space,
                                char exponent_sign) {
  if (value < 0) {
    s21_sputchar(out, '-');
    value = -value;
  } else if (print_plus)
    s21_sputchar(out, '+');
  else if (print_space)
    s21_sputchar(out, ' ');

  int exp = floor(log10l(value));
  if (value != 0.0)
    value /= powl(10, exp);
  else
    exp = 0;

  {
    char temporal_buffer[256];
    char *number = temporal_buffer;
    char *end = temporal_buffer;
    s21_sput_float(&end, value, precision, false, false, false);
    copy(number, out, end - number);
  }

  s21_sputchar(out, exponent_sign);

  s21_sputchar(out, (exp >= 0) ? '+' : '-');
  exp = (exp > 0) ? exp : -exp;
  if (exp == 0) {
    s21_sputchar(out, '0');
    s21_sputchar(out, '0');
  } else if (exp < 10) {
    s21_sputchar(out, '0');
    s21_sputchar(out, '0' + exp);
  } else
    s21_sput_int(out, exp, true, false);
}

void s21_sput_hex(char **out, uint64_t value, char *hex_table) {
  if (value == 0) return s21_sputchar(out, '0');
  char *start = *out;
  uint_fast8_t size = 0;
  for (; value; value >>= 4, size++) s21_sputchar(out, hex_table[value % 16]);
  reverse(start, size);
}

void s21_sput_octal(char **out, uint64_t value, bool print_zero) {
  if (value == 0) return s21_sputchar(out, '0');
  if (print_zero) s21_sputchar(out, '0');
  char *octal_table = "01234567";
  char *start = *out;
  uint_fast8_t size = 0;

  for (; value; value >>= 3, size++) s21_sputchar(out, octal_table[value % 8]);

  reverse(start, size);
}

void s21_sputs(char **out, const char *str) {
  for (; *str; ++str) s21_sputchar(out, *str);
}