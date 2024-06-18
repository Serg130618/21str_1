#include "handlers.h"

void unit_align(struct format_unit _f_u, char **out, char *number, int length) {
  char sign = 0;

  if (number[0] == '-' || number[0] == '+' || number[0] == ' ') {
    sign = number[0];
    number++, length--;
  }

  int space_taken = max(max(_f_u.width, _f_u.precision), length);
  int spaces_left = 0, spaces_right = 0, zeros_left = 0;

  bool _is_signed = sign != 0;

  if (_f_u.precision - length > 0) zeros_left = _f_u.precision - length;
  if (_f_u.align == RIGHT)
    spaces_left = space_taken - zeros_left - length - _is_signed;
  if (_f_u.align == LEFT)
    spaces_right = space_taken - zeros_left - length - _is_signed;
  if (_f_u.filler_symbol == '0') {
    zeros_left += spaces_left;
    spaces_left = 0;

    if (sign && _f_u.precision - length > 0) zeros_left++;
  }

  for (int i = 0; i < spaces_left; i++) s21_sputchar(out, ' ');

  if (_is_signed) s21_sputchar(out, sign);
  for (int i = 0; i < zeros_left; i++) s21_sputchar(out, '0');
  copy(number, out, length);

  for (int i = 0; i < spaces_right; i++) s21_sputchar(out, ' ');
}

void unit_handler_any_int(struct format_unit _f_u, char **out, uint64_t value,
                          bool is_signed) {
  char temporal_buffer[256];
  char *number = temporal_buffer;
  char *end = temporal_buffer;

  if (is_signed)
    s21_sput_int(&end, (int64_t)value, _f_u.sign_forced, _f_u.space_forced);
  else
    s21_sput_uint(&end, value);

  int length = end - temporal_buffer;

  unit_align(_f_u, out, number, length);
}

void unit_handler_any_hex(struct format_unit _f_u, char **out, uint64_t value) {
  if (_f_u.number_sign && (_f_u.width != 0) && (_f_u.precision != -1))
    _f_u.filler_symbol = '0';

  if (_f_u.number_sign && (value != 0)) {
    s21_sputchar(out, '0');
    s21_sputchar(out, _f_u.hex[16]);
    _f_u.width -= 2;
  }

  char temporal_buffer[256];
  char *number = temporal_buffer;
  char *end = temporal_buffer;

  s21_sput_hex(&end, value, _f_u.hex);

  int length = end - temporal_buffer;

  unit_align(_f_u, out, number, length);
}

void unit_handler_any_octal(struct format_unit _f_u, char **out,
                            uint64_t value) {
  char temporal_buffer[256];
  char *number = temporal_buffer;
  char *end = temporal_buffer;
  s21_sput_octal(&end, value, _f_u.number_sign);
  int length = end - temporal_buffer;

  unit_align(_f_u, out, number, length);
}

void unit_handler_int(struct format_unit _f_u, char **out, int64_t value) {
  unit_handler_any_int(_f_u, out, value, SIGNED);
}

void unit_handler_unsigned_int(struct format_unit _f_u, char **out,
                               uint64_t value) {
  unit_handler_any_int(_f_u, out, value, UNSIGNED);
}

void unit_handler_any_float(struct format_unit _f_u, char **out,
                            long double value) {
  char temporal_buffer[256];
  char *number = temporal_buffer;
  char *end = temporal_buffer;

  s21_sput_float(&end, value, _f_u.precision, _f_u.sign_forced,
                 _f_u.number_sign, _f_u.space_forced);

  int length = end - temporal_buffer;

  unit_align(_f_u, out, number, length);
}

void unit_handler_any_exponential(struct format_unit _f_u, char **out,
                                  long double value) {
  char temporal_buffer[256];
  char *number = temporal_buffer;
  char *end = temporal_buffer;

  s21_sput_float_exponential(&end, value, _f_u.precision, _f_u.sign_forced,
                             _f_u.space_forced, _f_u.exponent_sign);

  int length = end - temporal_buffer;

  unit_align(_f_u, out, number, length);
}

void unit_handler_any_shortest(struct format_unit _f_u, char **out,
                               long double value) {
  char temporal_buffer_float[256];
  char *number_float = temporal_buffer_float;
  char *end_float = temporal_buffer_float;

  char temporal_buffer_exp[256];
  char *number_exp = temporal_buffer_exp;
  char *end_exp = temporal_buffer_exp;

  int integer_digits = ceill(log10l(fabsl(value)));
  s21_sput_float(&end_float, value, _f_u.precision - integer_digits,
                 _f_u.sign_forced, _f_u.number_sign, _f_u.space_forced);

  s21_sput_float_exponential(&end_exp, value, _f_u.precision, _f_u.sign_forced,
                             _f_u.number_sign, _f_u.exponent_sign);

  int length_float = end_float - temporal_buffer_float;
  int length_exp = end_exp - temporal_buffer_exp;

  if (!_f_u.number_sign) {
    end_float--;
    for (; *end_float == '0'; end_float--) length_float--;
    if (!_f_u.number_sign)
      if (*end_float == '.') length_float--;
  }

  int length = min(length_float, length_exp);
  if (_f_u.align == RIGHT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');

  if (length_float <= length_exp)
    copy(number_float, out, length_float);
  else
    copy(number_exp, out, length_exp);

  if (_f_u.align == LEFT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
}

void unit_handler_short_short_decimal(struct format_unit _f_u, char **out,
                                      va_list args) {
  unit_handler_int(_f_u, out, (char)(va_arg(args, int)));
}

void unit_handler_short_decimal(struct format_unit _f_u, char **out,
                                va_list args) {
  unit_handler_int(_f_u, out, (short int)(va_arg(args, int)));
}

void unit_handler_decimal(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_int(_f_u, out, va_arg(args, int));
}

void unit_handler_long_decimal(struct format_unit _f_u, char **out,
                               va_list args) {
  unit_handler_int(_f_u, out, va_arg(args, long int));
}

void unit_handler_long_long_decimal(struct format_unit _f_u, char **out,
                                    va_list args) {
  unit_handler_int(_f_u, out, va_arg(args, long long int));
}

void unit_handler_short_short_unsigned(struct format_unit _f_u, char **out,
                                       va_list args) {
  unit_handler_unsigned_int(_f_u, out,
                            (unsigned char)(va_arg(args, unsigned int)));
}

void unit_handler_short_unsigned(struct format_unit _f_u, char **out,
                                 va_list args) {
  unit_handler_unsigned_int(_f_u, out,
                            (unsigned short int)(va_arg(args, unsigned int)));
}

void unit_handler_unsigned(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_unsigned_int(_f_u, out, va_arg(args, unsigned int));
}

void unit_handler_long_unsigned(struct format_unit _f_u, char **out,
                                va_list args) {
  unit_handler_unsigned_int(_f_u, out, va_arg(args, unsigned long int));
}

void unit_handler_long_long_unsigned(struct format_unit _f_u, char **out,
                                     va_list args) {
  unit_handler_unsigned_int(_f_u, out, va_arg(args, unsigned long long int));
}

void unit_handler_float(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_float(_f_u, out, (float)(va_arg(args, double)));
}

void unit_handler_double(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_float(_f_u, out, va_arg(args, double));
}

void unit_handler_long_double(struct format_unit _f_u, char **out,
                              va_list args) {
  unit_handler_any_float(_f_u, out, va_arg(args, long double));
}

void unit_handler_string(struct format_unit _f_u, char **out, va_list args) {
  char *value = va_arg(args, char *);
  if (value == NULL) return s21_sputs(out, "(null)");
  int length = s21_strlen(value);
  if (_f_u.align == RIGHT)
#ifdef __APPLE__
    for (int i = 0; i < _f_u.width - length; i++)
      s21_sputchar(out, _f_u.filler_symbol);
#else
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
#endif

  s21_sputs(out, value);
  if (_f_u.align == LEFT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
}

void unit_handler_wide_string(struct format_unit _f_u, char **out,
                              va_list args) {
  char *value = va_arg(args, char *);
  int length = s21_strlen(value);
  if (_f_u.align == RIGHT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
  s21_sputs(out, value);
  if (_f_u.align == LEFT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
}

void unit_handler_char(struct format_unit _f_u, char **out, va_list args) {
  if (_f_u.align == LEFT) s21_sputchar(out, (char)(va_arg(args, int)));

  for (int i = 0; i < _f_u.width - 1; i++)
    s21_sputchar(out, _f_u.filler_symbol);

  if (_f_u.align == RIGHT) s21_sputchar(out, (char)(va_arg(args, int)));
}

void unit_handler_wide_char(struct format_unit _f_u, char **out, va_list args) {
  char value = va_arg(args, int);
  const int length = 1;
  if (_f_u.align == RIGHT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
  s21_sputchar(out, value);
  if (_f_u.align == LEFT)
    for (int i = 0; i < _f_u.width - length; i++) s21_sputchar(out, ' ');
}

void unit_handler_short_short_hex(struct format_unit _f_u, char **out,
                                  va_list args) {
  unit_handler_any_hex(_f_u, out, (unsigned char)(va_arg(args, unsigned int)));
}

void unit_handler_short_hex(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_hex(_f_u, out,
                       (unsigned short int)(va_arg(args, unsigned int)));
}

void unit_handler_hex(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_hex(_f_u, out, va_arg(args, unsigned int));
}

void unit_handler_long_hex(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_hex(_f_u, out, va_arg(args, unsigned long int));
}

void unit_handler_long_long_hex(struct format_unit _f_u, char **out,
                                va_list args) {
  unit_handler_any_hex(_f_u, out, va_arg(args, unsigned long long int));
}

void unit_handler_pointer(struct format_unit _f_u, char **out, va_list args) {
  if (_f_u.data_type != p) return;
  void *value = va_arg(args, void *);
#ifdef __linux__
  if (value == NULL) return s21_sputs(out, "(nil)");
#endif
  s21_sputchar(out, '0');
  s21_sputchar(out, 'x');
  s21_sput_hex(out, (uint64_t)value, "0123456789abcdef");
}

void unit_handler_short_short_octal(struct format_unit _f_u, char **out,
                                    va_list args) {
  unit_handler_any_octal(_f_u, out, (unsigned char)va_arg(args, unsigned int));
}

void unit_handler_short_octal(struct format_unit _f_u, char **out,
                              va_list args) {
  unit_handler_any_octal(_f_u, out,
                         (unsigned short int)va_arg(args, unsigned int));
}

void unit_handler_octal(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_octal(_f_u, out, va_arg(args, unsigned int));
}

void unit_handler_long_octal(struct format_unit _f_u, char **out,
                             va_list args) {
  unit_handler_any_octal(_f_u, out, va_arg(args, unsigned long int));
}

void unit_handler_long_long_octal(struct format_unit _f_u, char **out,
                                  va_list args) {
  unit_handler_any_octal(_f_u, out, va_arg(args, unsigned long long int));
}

void unit_handler_exponential(struct format_unit _f_u, char **out,
                              va_list args) {
  unit_handler_any_exponential(_f_u, out, va_arg(args, double));
}

void unit_handler_long_exponential(struct format_unit _f_u, char **out,
                                   va_list args) {
  unit_handler_any_exponential(_f_u, out, va_arg(args, long double));
}

void unit_handler_shortest(struct format_unit _f_u, char **out, va_list args) {
  unit_handler_any_shortest(_f_u, out, va_arg(args, double));
}

void unit_handler_long_shortest(struct format_unit _f_u, char **out,
                                va_list args) {
  unit_handler_any_shortest(_f_u, out, va_arg(args, long double));
}

typedef void unit_handler(struct format_unit, char **, va_list);
static unit_handler *_handlers[] = {
    &unit_handler_short_short_decimal,  // %hhd
    &unit_handler_short_decimal,        // %hd
    &unit_handler_decimal,              // %d
    &unit_handler_long_decimal,         // %ld
    &unit_handler_long_long_decimal,    // %lld

    &unit_handler_short_short_unsigned,  // %hhu
    &unit_handler_short_unsigned,        // %hu
    &unit_handler_unsigned,              // %u
    &unit_handler_long_unsigned,         // %lu
    &unit_handler_long_long_unsigned,    // %llu

    &unit_handler_short_short_octal,  // %hho
    &unit_handler_short_octal,        // %ho
    &unit_handler_octal,              // %o
    &unit_handler_long_octal,         // %lo
    &unit_handler_long_long_octal,    // %llo

    &unit_handler_short_short_hex,  // %hhx
    &unit_handler_short_hex,        // %hx
    &unit_handler_hex,              // %x
    &unit_handler_long_hex,         // %lx
    &unit_handler_long_long_hex,    // %llx

    &unit_handler_float,        // %f
    &unit_handler_double,       // %lf
    &unit_handler_long_double,  // %Lf

    &unit_handler_char,       // %c
    &unit_handler_wide_char,  // %lc

    &unit_handler_exponential,       // %e
    &unit_handler_long_exponential,  // %Le

    &unit_handler_shortest,       // %g
    &unit_handler_long_shortest,  // %Lg

    &unit_handler_string,       // %s
    &unit_handler_wide_string,  // %ls

    &unit_handler_pointer,  // %p

    NULL,  // %n ¯\_(シ)_/¯
};

int handle_format_unit(format_unit_t _f_u, char **str, va_list args) {
  char *start = *str;
  _handlers[_f_u.data_type](_f_u, str, args);

  return (int)(*str - start);
}