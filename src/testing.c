#include <check.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

#define unit_test(format, ...)                                              \
  {                                                                         \
    char buffer_s21[4096] = {0}, buffer_sys[4096] = {0};                    \
    int len_s21 = 0, len_sys = 0;                                           \
    len_sys = sprintf(buffer_sys, format, __VA_ARGS__);                     \
    len_s21 = s21_sprintf(buffer_s21, format, __VA_ARGS__);                 \
    uint8_t is_error = 0;                                                   \
    if (len_s21 != len_sys) is_error = 1;                                   \
    if (s21_strcmp(buffer_sys, buffer_s21) != 0) is_error = 1;              \
    if (is_error) {                                                         \
      fprintf(stderr, "\n=============================================\n"); \
      fprintf(stderr, "\n");                                                \
      fprintf(stderr, "\tFORMAT: \"%s\"\n", format);                        \
      fprintf(stderr, "\tERROR\n");                                         \
      fprintf(stderr, "\n");                                                \
      fprintf(stderr, "\tS21: \"%s\"\n", buffer_s21);                       \
      fprintf(stderr, "\tSYS: \"%s\"\n", buffer_sys);                       \
      fprintf(stderr, "\n");                                                \
      fprintf(stderr, "\tS21: \"%d\"\n", len_s21);                          \
      fprintf(stderr, "\tSYS: \"%d\"\n", len_sys);                          \
      fprintf(stderr, "\n");                                                \
      fprintf(stderr, "==============================================\n");  \
    }                                                                       \
    ck_assert_str_eq(buffer_s21, buffer_sys);                               \
    ck_assert_int_eq(len_s21, len_sys);                                     \
  }

/*void unit_test(char *format, ...) {
  va_list list1;
  va_list list2;

  char buffer_s21[4096] = {0};
  char buffer_sys[4096] = {0};

  int len_s21;
  int len_sys;

  va_start(list1, format);
  va_start(list2, format);

  len_sys = vsprintf(buffer_sys, format, list1);
  len_s21 = s21_vsprintf(buffer_s21, format, list2);

  va_end(list1);
  va_end(list2);

  uint8_t is_error = 0;

  if (len_s21 != len_sys) is_error = 1;
  if (s21_strcmp(buffer_sys, buffer_s21) != 0) is_error = 1;

  if (is_error) {
    fprintf(stderr, "\n=============================================\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "\tFORMAT: \"%s\"\n", format);
    fprintf(stderr, "\tERROR\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "\tS21: \"%s\"\n", buffer_s21);
    fprintf(stderr, "\tSYS: \"%s\"\n", buffer_sys);
    fprintf(stderr, "\n");
    fprintf(stderr, "\tS21: \"%d\"\n", len_s21);
    fprintf(stderr, "\tSYS: \"%d\"\n", len_sys);
    fprintf(stderr, "\n");
    fprintf(stderr, "==============================================\n");
  }

  ck_assert_str_eq(buffer_s21, buffer_sys);
  ck_assert_int_eq(len_s21, len_sys);
}*/

START_TEST(test_s21_strlen) {
  char *str = "Hello, world!";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_s21_strchr) {
  char *str = "Hello, world!";
  int c = 'o';
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}
END_TEST

START_TEST(test_s21_strncmp) {
  char *str1 = "Hello, world!";
  char *str2 = "Hello, ignnre!";
  size_t n = 5;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strcmp) {
  char *str1 = "Hello, world!";
  char *str2 = "Hello, iggnre!";
  ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(test_s21_memcmp) {
  char *str1 = "Hello, world!";
  char *str2 = "Hello, reifrk!";
  size_t n = 5;
  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_memchr) {
  char *str = "Hello, world!";
  int c = 'o';
  size_t n = 5;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_s21_memcpy) {
  char dest[50];
  char *src = "Hello, world!";
  size_t n = strlen(src) + 1;
  ck_assert_ptr_eq(s21_memcpy(dest, src, n), memcpy(dest, src, n));
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_memset) {
  char str[50] = "Hello, world!";
  int c = '-';
  size_t n = 5;
  ck_assert_ptr_eq(s21_memset(str, c, n), memset(str, c, n));
  ck_assert_str_eq(str, "-----, world!");
}
END_TEST

START_TEST(test_s21_strrchr) {
  char *str = "Hello, world!";
  int c = 'o';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_s21_strstr) {
  char *haystack = "Hello, world!";
  char *needle = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_to_upper) {
  char *str = "Hello, world!";
  char *expected = "HELLO, WORLD!";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_to_lower) {
  char *str = "HELLO, WORLD!";
  char *expected = "hello, world!";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, expected);
  free(result);
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest[50];
  char *src = "Hello, world!";
  size_t n = strlen(src) + 1;
  ck_assert_ptr_eq(s21_strncpy(dest, src, n), strncpy(dest, src, n));
  ck_assert_str_eq(dest, src);
}
END_TEST

START_TEST(test_s21_strcspn) {
  char *str1 = "Hello, world!";
  char *str2 = ", world!";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(tc) {
  char buff[100];
  s21_sprintf(buff, "hello %d", 123);

  unit_test("Hello world!", NULL);
  unit_test("Hello%%cworld!", NULL);

  unit_test("Hello%cworld!", '_');
  unit_test("Hello%5.cworld!", '_');
  unit_test("Hello%5.5cworld!", '_');

  unit_test("Hello%-5.5cworld!", '_');
  unit_test("Hello%+5.5cworld!", '_');
  // unit_test("Hello%05.5cworld!", '_');
}
END_TEST

START_TEST(ts) {
  char *str1 = "Hello, world!!!\n\n@bff123";
  char *str2 = "123456789000-0=q\t\twertyuiopasdfghjkl;xcvbnm,H&O*$B)To9`p8mue";
  unit_test("%s", NULL);

  unit_test("%s - %s", str1, str2);
  unit_test("% s - % s", str1, str2);
  unit_test("%0s - %0s", str1, str2);
  unit_test("%-s - %-s", str1, str2);
  unit_test("%+s - %+s", str1, str2);

  unit_test("%100s - %100s", str1, str2);
  unit_test("% 100s - % 100s", str1, str2);
  unit_test("%0100s - %0100s", str1, str2);
  unit_test("%-100s - %-100s", str1, str2);
  unit_test("%+100s - %+100s", str1, str2);
}
END_TEST

START_TEST(tx) {
  // x

  int x1 = 41293764;
  int x2 = -x1;

  unit_test("%x - %x", x1, x2);
  unit_test("%#x - %#x", x1, x2);
  unit_test("%#.15x - %#.15x", x1, x2);

  unit_test("% x - % x", x1, x2);
  unit_test("%0x - %0x", x1, x2);
  unit_test("%-x - %-x", x1, x2);
  unit_test("%+x - %+x", x1, x2);

  unit_test("%15x - %15x", x1, x2);
  unit_test("% 15x - % 15x", x1, x2);
  unit_test("%-15x - %-15x", x1, x2);
  unit_test("%+15x - %+15x", x1, x2);

  unit_test("%.15x - %.15x", x1, x2);
  unit_test("%.*x - %.*x", 15, x1, 15, x2);
  unit_test("%*.x - %*.x", 15, x1, 15, x2);

  unit_test("% .15x - % .15x", x1, x2);
  unit_test("%-.15x - %-.15x", x1, x2);
  unit_test("%+.15x - %+.15x", x1, x2);

  unit_test("%15.15x - %15.15x", x1, x2);
  unit_test("% 15.15x - % 15.15x", x1, x2);
  unit_test("%-15.15x - %-15.15x", x1, x2);
  unit_test("%+15.15x - %+15.15x", x1, x2);

  // lx

  long int lx1 = 41293764;
  long int lx2 = -x1;

  unit_test("%lx - %lx", lx1, lx2);
  unit_test("% lx - % lx", lx1, lx2);
  unit_test("%0lx - %0lx", lx1, lx2);
  unit_test("%-lx - %-lx", lx1, lx2);
  unit_test("%+lx - %+lx", lx1, lx2);

  unit_test("%15lx - %15lx", lx1, lx2);
  unit_test("% 15lx - % 15lx", lx1, lx2);
  unit_test("%-15lx - %-15lx", lx1, lx2);
  unit_test("%+15lx - %+15lx", lx1, lx2);

  unit_test("%.15llx - %.15lx", lx1, lx2);
  unit_test("% .15llx - % .15lx", lx1, lx2);
  unit_test("%-.15llx - %-.15lx", lx1, lx2);
  unit_test("%+.15llx - %+.15lx", lx1, lx2);

  unit_test("%15.15lx - %15.15lx", lx1, lx2);
  unit_test("% 15.15lx - % 15.15lx", lx1, lx2);
  unit_test("%-15.15lx - %-15.15lx", lx1, lx2);
  unit_test("%+15.15lx - %+15.15lx", lx1, lx2);

  // llx

  long long int llx1 = 41293764;
  long long int llx2 = -x1;

  unit_test("%Lx - %Lx", llx1, llx2);
  unit_test("% Lx - % Lx", llx1, llx2);
  unit_test("%0Lx - %0Lx", llx1, llx2);
  unit_test("%-Lx - %-Lx", llx1, llx2);
  unit_test("%+Lx - %+Lx", llx1, llx2);

  unit_test("%15Lx - %15Lx", llx1, llx2);
  unit_test("% 15Lx - % 15Lx", llx1, llx2);
  unit_test("%-15Lx - %-15Lx", llx1, llx2);
  unit_test("%+15Lx - %+15Lx", llx1, llx2);

  unit_test("%.15Lx - %.15Lx", llx1, llx2);
  unit_test("% .15Lx - % .15Lx", llx1, llx2);
  unit_test("%-.15Lx - %-.15Lx", llx1, llx2);
  unit_test("%+.15Lx - %+.15Lx", llx1, llx2);

  unit_test("%15.15Lx - %15.15Lx", llx1, llx2);
  unit_test("% 15.15Lx - % 15.15Lx", llx1, llx2);
  unit_test("%-15.15Lx - %-15.15Lx", llx1, llx2);
  unit_test("%+15.15Lx - %+15.15Lx", llx1, llx2);

  // hx

  short int hx1 = 41;
  short int hx2 = -hx1;

  unit_test("%hx - %hx", hx1, hx2);
  unit_test("% hx - % hx", hx1, hx2);
  unit_test("%0hx - %0hx", hx1, hx2);
  unit_test("%-hx - %-hx", hx1, hx2);
  unit_test("%+hx - %+hx", hx1, hx2);

  unit_test("%15hx - %15hx", hx1, hx2);
  unit_test("% 15hx - % 15hx", hx1, hx2);
  unit_test("%-15hx - %-15hx", hx1, hx2);
  unit_test("%+15hx - %+15hx", hx1, hx2);

  unit_test("%.15hx - %.15hx", hx1, hx2);
  unit_test("% .15hx - % .15hx", hx1, hx2);
  unit_test("%-.15hx - %-.15hx", hx1, hx2);
  unit_test("%+.15hx - %+.15hx", hx1, hx2);

  unit_test("%15.15hx - %15.15hx", hx1, hx2);
  unit_test("% 15.15hx - % 15.15hx", hx1, hx2);
  unit_test("%-15.15hx - %-15.15hx", hx1, hx2);
  unit_test("%+15.15hx - %+15.15hx", hx1, hx2);

  // lx

  char hhx1 = 41;
  char hhx2 = -hhx1;

  unit_test("%hhx - %hhx", hhx1, hhx2);
  unit_test("% hhx - % hhx", hhx1, hhx2);
  unit_test("%0hhx - %0hhx", hhx1, hhx2);
  unit_test("%-hhx - %-hhx", hhx1, hhx2);
  unit_test("%+hhx - %+hhx", hhx1, hhx2);

  unit_test("%15hhx - %15hhx", hhx1, hhx2);
  unit_test("% 15hhx - % 15hhx", hhx1, hhx2);
  unit_test("%-15hhx - %-15hhx", hhx1, hhx2);
  unit_test("%+15hhx - %+15hhx", hhx1, hhx2);

  unit_test("%.15hx - %.15hx", hhx1, hhx2);
  unit_test("% .15hhx - % .15hhx", hhx1, hhx2);
  unit_test("%-.15hhx - %-.15hhx", hhx1, hhx2);
  unit_test("%+.15hhx - %+.15hhx", hhx1, hhx2);

  unit_test("%15.15hhx - %15.15hhx", hhx1, hhx2);
  unit_test("% 15.15hhx - % 15.15hhx", hhx1, hhx2);
  unit_test("%-15.15hhx - %-15.15hhx", hhx1, hhx2);
  unit_test("%+15.15hhx - %+15.15hhx", hhx1, hhx2);
}
END_TEST

START_TEST(tp) {
  char *ptr1 = malloc(1);
  char *ptr2 = malloc(1);

  unit_test("%p", NULL);

  unit_test("%p - %p", ptr1, ptr2);

  free(ptr1);
  free(ptr2);
}
END_TEST

START_TEST(to) {
  // o

  int o1 = 41293764;
  int o2 = -o1;

  unit_test("%o - %o", o1, o2);
  unit_test("%#o - %#o", o1, o2);
  unit_test("%#.15o - %#.15o", o1, o2);

  unit_test("% o - % o", o1, o2);
  unit_test("%0o - %0o", o1, o2);
  unit_test("%-o - %-o", o1, o2);
  unit_test("%+o - %+o", o1, o2);

  unit_test("%15o - %15o", o1, o2);
  unit_test("% 15o - % 15o", o1, o2);
  unit_test("%-15o - %-15o", o1, o2);
  unit_test("%+15o - %+15o", o1, o2);

  unit_test("%.15o - %.15o", o1, o2);
  unit_test("%.*o - %.*o", 15, o1, 15, o2);
  unit_test("%*.o - %*.o", 15, o1, 15, o2);

  unit_test("% .15o - % .15o", o1, o2);
  unit_test("%-.15o - %-.15o", o1, o2);
  unit_test("%+.15o - %+.15o", o1, o2);

  unit_test("%15.15o - %15.15o", o1, o2);
  unit_test("% 15.15o - % 15.15o", o1, o2);
  unit_test("%-15.15o - %-15.15o", o1, o2);
  unit_test("%+15.15o - %+15.15o", o1, o2);

  // lo

  long int lo1 = 41293764;
  long int lo2 = -o1;

  unit_test("%lo - %lo", lo1, lo2);
  unit_test("% lo - % lo", lo1, lo2);
  unit_test("%0lo - %0lo", lo1, lo2);
  unit_test("%-lo - %-lo", lo1, lo2);
  unit_test("%+lo - %+lo", lo1, lo2);

  unit_test("%15lo - %15lo", lo1, lo2);
  unit_test("% 15lo - % 15lo", lo1, lo2);
  unit_test("%-15lo - %-15lo", lo1, lo2);
  unit_test("%+15lo - %+15lo", lo1, lo2);

  unit_test("%.15llo - %.15lo", lo1, lo2);
  unit_test("% .15llo - % .15lo", lo1, lo2);
  unit_test("%-.15llo - %-.15lo", lo1, lo2);
  unit_test("%+.15llo - %+.15lo", lo1, lo2);

  unit_test("%15.15lo - %15.15lo", lo1, lo2);
  unit_test("% 15.15lo - % 15.15lo", lo1, lo2);
  unit_test("%-15.15lo - %-15.15lo", lo1, lo2);
  unit_test("%+15.15lo - %+15.15lo", lo1, lo2);

  // llo

  long long int llo1 = 41293764;
  long long int llo2 = -o1;

  unit_test("%Lo - %Lo", llo1, llo2);
  unit_test("% Lo - % Lo", llo1, llo2);
  unit_test("%0Lo - %0Lo", llo1, llo2);
  unit_test("%-Lo - %-Lo", llo1, llo2);
  unit_test("%+Lo - %+Lo", llo1, llo2);

  unit_test("%15Lo - %15Lo", llo1, llo2);
  unit_test("% 15Lo - % 15Lo", llo1, llo2);
  unit_test("%-15Lo - %-15Lo", llo1, llo2);
  unit_test("%+15Lo - %+15Lo", llo1, llo2);

  unit_test("%.15Lo - %.15Lo", llo1, llo2);
  unit_test("% .15Lo - % .15Lo", llo1, llo2);
  unit_test("%-.15Lo - %-.15Lo", llo1, llo2);
  unit_test("%+.15Lo - %+.15Lo", llo1, llo2);

  unit_test("%15.15Lo - %15.15Lo", llo1, llo2);
  unit_test("% 15.15Lo - % 15.15Lo", llo1, llo2);
  unit_test("%-15.15Lo - %-15.15Lo", llo1, llo2);
  unit_test("%+15.15Lo - %+15.15Lo", llo1, llo2);

  // ho

  short int ho1 = 41;
  short int ho2 = -ho1;

  unit_test("%ho - %ho", ho1, ho2);
  unit_test("% ho - % ho", ho1, ho2);
  unit_test("%0ho - %0ho", ho1, ho2);
  unit_test("%-ho - %-ho", ho1, ho2);
  unit_test("%+ho - %+ho", ho1, ho2);

  unit_test("%15ho - %15ho", ho1, ho2);
  unit_test("% 15ho - % 15ho", ho1, ho2);
  unit_test("%-15ho - %-15ho", ho1, ho2);
  unit_test("%+15ho - %+15ho", ho1, ho2);

  unit_test("%.15ho - %.15ho", ho1, ho2);
  unit_test("% .15ho - % .15ho", ho1, ho2);
  unit_test("%-.15ho - %-.15ho", ho1, ho2);
  unit_test("%+.15ho - %+.15ho", ho1, ho2);

  unit_test("%15.15ho - %15.15ho", ho1, ho2);
  unit_test("% 15.15ho - % 15.15ho", ho1, ho2);
  unit_test("%-15.15ho - %-15.15ho", ho1, ho2);
  unit_test("%+15.15ho - %+15.15ho", ho1, ho2);

  // lo

  char hho1 = 41;
  char hho2 = -hho1;

  unit_test("%hho - %hho", hho1, hho2);
  unit_test("% hho - % hho", hho1, hho2);
  unit_test("%0hho - %0hho", hho1, hho2);
  unit_test("%-hho - %-hho", hho1, hho2);
  unit_test("%+hho - %+hho", hho1, hho2);

  unit_test("%15hho - %15hho", hho1, hho2);
  unit_test("% 15hho - % 15hho", hho1, hho2);
  unit_test("%-15hho - %-15hho", hho1, hho2);
  unit_test("%+15hho - %+15hho", hho1, hho2);

  unit_test("%.15ho - %.15ho", hho1, hho2);
  unit_test("% .15hho - % .15hho", hho1, hho2);
  unit_test("%-.15hho - %-.15hho", hho1, hho2);
  unit_test("%+.15hho - %+.15hho", hho1, hho2);

  unit_test("%15.15hho - %15.15hho", hho1, hho2);
  unit_test("% 15.15hho - % 15.15hho", hho1, hho2);
  unit_test("%-15.15hho - %-15.15hho", hho1, hho2);
  unit_test("%+15.15hho - %+15.15hho", hho1, hho2);
}
END_TEST

START_TEST(td) {
  // d

  int d1 = 41293764;
  int d2 = -d1;

  unit_test("%d - %d", d1, d2);
  unit_test("% d - % d", d1, d2);
  unit_test("%0d - %0d", d1, d2);
  unit_test("%-d - %-d", d1, d2);
  unit_test("%+d - %+d", d1, d2);

  unit_test("%15d - %15d", d1, d2);
  unit_test("% 15d - % 15d", d1, d2);
  unit_test("%-15d - %-15d", d1, d2);
  unit_test("%+15d - %+15d", d1, d2);

  unit_test("%.15d - %.15d", d1, d2);
  unit_test("%.*d - %.*d", 15, d1, 15, d2);
  unit_test("%*.d - %*.d", 15, d1, 15, d2);

  unit_test("% .15d - % .15d", d1, d2);
  unit_test("%-.15d - %-.15d", d1, d2);
  unit_test("%+.15d - %+.15d", d1, d2);

  unit_test("%15.15d - %15.15d", d1, d2);
  unit_test("% 15.15d - % 15.15d", d1, d2);
  unit_test("%-15.15d - %-15.15d", d1, d2);
  unit_test("%+15.15d - %+15.15d", d1, d2);

  // ld

  long int ld1 = 41293764;
  long int ld2 = -d1;

  unit_test("%ld - %ld", ld1, ld2);
  unit_test("% ld - % ld", ld1, ld2);
  unit_test("%0ld - %0ld", ld1, ld2);
  unit_test("%-ld - %-ld", ld1, ld2);
  unit_test("%+ld - %+ld", ld1, ld2);

  unit_test("%15ld - %15ld", ld1, ld2);
  unit_test("% 15ld - % 15ld", ld1, ld2);
  unit_test("%-15ld - %-15ld", ld1, ld2);
  unit_test("%+15ld - %+15ld", ld1, ld2);

  unit_test("%.15lld - %.15ld", ld1, ld2);
  unit_test("% .15lld - % .15ld", ld1, ld2);
  unit_test("%-.15lld - %-.15ld", ld1, ld2);
  unit_test("%+.15lld - %+.15ld", ld1, ld2);

  unit_test("%15.15ld - %15.15ld", ld1, ld2);
  unit_test("% 15.15ld - % 15.15ld", ld1, ld2);
  unit_test("%-15.15ld - %-15.15ld", ld1, ld2);
  unit_test("%+15.15ld - %+15.15ld", ld1, ld2);

  // ld

  long long int lld1 = 41293764;
  long long int lld2 = -d1;

  unit_test("%Ld - %Ld", lld1, lld2);
  unit_test("% Ld - % Ld", lld1, lld2);
  unit_test("%0Ld - %0Ld", lld1, lld2);
  unit_test("%-Ld - %-Ld", lld1, lld2);
  unit_test("%+Ld - %+Ld", lld1, lld2);

  unit_test("%15Ld - %15Ld", lld1, lld2);
  unit_test("% 15Ld - % 15Ld", lld1, lld2);
  unit_test("%-15Ld - %-15Ld", lld1, lld2);
  unit_test("%+15Ld - %+15Ld", lld1, lld2);

  unit_test("%.15Ld - %.15Ld", lld1, lld2);
  unit_test("% .15Ld - % .15Ld", lld1, lld2);
  unit_test("%-.15Ld - %-.15Ld", lld1, lld2);
  unit_test("%+.15Ld - %+.15Ld", lld1, lld2);

  unit_test("%15.15Ld - %15.15Ld", lld1, lld2);
  unit_test("% 15.15Ld - % 15.15Ld", lld1, lld2);
  unit_test("%-15.15Ld - %-15.15Ld", lld1, lld2);
  unit_test("%+15.15Ld - %+15.15Ld", lld1, lld2);

  // hd

  short int hd1 = 41;
  short int hd2 = -hd1;

  unit_test("%hd - %hd", hd1, hd2);
  unit_test("% hd - % hd", hd1, hd2);
  unit_test("%0hd - %0hd", hd1, hd2);
  unit_test("%-hd - %-hd", hd1, hd2);
  unit_test("%+hd - %+hd", hd1, hd2);

  unit_test("%15hd - %15hd", hd1, hd2);
  unit_test("% 15hd - % 15hd", hd1, hd2);
  unit_test("%-15hd - %-15hd", hd1, hd2);
  unit_test("%+15hd - %+15hd", hd1, hd2);

  unit_test("%.15hd - %.15hd", hd1, hd2);
  unit_test("% .15hd - % .15hd", hd1, hd2);
  unit_test("%-.15hd - %-.15hd", hd1, hd2);
  unit_test("%+.15hd - %+.15hd", hd1, hd2);

  unit_test("%15.15hd - %15.15hd", hd1, hd2);
  unit_test("% 15.15hd - % 15.15hd", hd1, hd2);
  unit_test("%-15.15hd - %-15.15hd", hd1, hd2);
  unit_test("%+15.15hd - %+15.15hd", hd1, hd2);

  // ld

  char hhd1 = 41;
  char hhd2 = -hhd1;

  unit_test("%hhd - %hhd", hhd1, hhd2);
  unit_test("% hhd - % hhd", hhd1, hhd2);
  unit_test("%0hhd - %0hhd", hhd1, hhd2);
  unit_test("%-hhd - %-hhd", hhd1, hhd2);
  unit_test("%+hhd - %+hhd", hhd1, hhd2);

  unit_test("%15hhd - %15hhd", hhd1, hhd2);
  unit_test("% 15hhd - % 15hhd", hhd1, hhd2);
  unit_test("%-15hhd - %-15hhd", hhd1, hhd2);
  unit_test("%+15hhd - %+15hhd", hhd1, hhd2);

  unit_test("%.15hd - %.15hd", hhd1, hhd2);
  unit_test("% .15hhd - % .15hhd", hhd1, hhd2);
  unit_test("%-.15hhd - %-.15hhd", hhd1, hhd2);
  unit_test("%+.15hhd - %+.15hhd", hhd1, hhd2);

  unit_test("%15.15hhd - %15.15hhd", hhd1, hhd2);
  unit_test("% 15.15hhd - % 15.15hhd", hhd1, hhd2);
  unit_test("%-15.15hhd - %-15.15hhd", hhd1, hhd2);
  unit_test("%+15.15hhd - %+15.15hhd", hhd1, hhd2);
}
END_TEST

START_TEST(tu) {
  // u

  unsigned int u1 = 41293764;
  unsigned int u2 = -u1;

  unit_test("%u - %u", u1, u2);
  unit_test("% u - % u", u1, u2);
  unit_test("%0u - %0u", u1, u2);
  unit_test("%-u - %-u", u1, u2);
  unit_test("%+u - %+u", u1, u2);

  unit_test("%15u - %15u", u1, u2);
  unit_test("% 15u - % 15u", u1, u2);
  unit_test("%-15u - %-15u", u1, u2);
  unit_test("%+15u - %+15u", u1, u2);

  unit_test("%.15u - %.15u", u1, u2);
  unit_test("% .15u - % .15u", u1, u2);
  unit_test("%-.15u - %-.15u", u1, u2);
  unit_test("%+.15u - %+.15u", u1, u2);

  unit_test("%15.15u - %15.15u", u1, u2);
  unit_test("% 15.15u - % 15.15u", u1, u2);
  unit_test("%-15.15u - %-15.15u", u1, u2);
  unit_test("%+15.15u - %+15.15u", u1, u2);

  // lu

  long unsigned int lu1 = 41293764;
  long unsigned int lu2 = -lu1;

  unit_test("%lu - %lu", lu1, lu2);
  unit_test("% lu - % lu", lu1, lu2);
  unit_test("%0lu - %0lu", lu1, lu2);
  unit_test("%-lu - %-lu", lu1, lu2);
  unit_test("%+lu - %+lu", lu1, lu2);

  unit_test("%15lu - %15lu", lu1, lu2);
  unit_test("% 15lu - % 15lu", lu1, lu2);
  unit_test("%-15lu - %-15lu", lu1, lu2);
  unit_test("%+15lu - %+15lu", lu1, lu2);

  unit_test("%.15lu - %.15lu", lu1, lu2);
  unit_test("% .15lu - % .15lu", lu1, lu2);
  unit_test("%-.15lu - %-.15lu", lu1, lu2);
  unit_test("%+.15lu - %+.15lu", lu1, lu2);

  unit_test("%15.15lu - %15.15lu", lu1, lu2);
  unit_test("% 15.15lu - % 15.15lu", lu1, lu2);
  unit_test("%-15.15lu - %-15.15lu", lu1, lu2);
  unit_test("%+15.15lu - %+15.15lu", lu1, lu2);

  // lu

  long long unsigned int llu1 = 41293764;
  long long unsigned int llu2 = -llu1;

  unit_test("%Lu - %Lu", llu1, llu2);
  unit_test("% Lu - % Lu", llu1, llu2);
  unit_test("%0Lu - %0Lu", llu1, llu2);
  unit_test("%-Lu - %-Lu", llu1, llu2);
  unit_test("%+Lu - %+Lu", llu1, llu2);

  unit_test("%15Lu - %15Lu", llu1, llu2);
  unit_test("% 15Lu - % 15Lu", llu1, llu2);
  unit_test("%-15Lu - %-15Lu", llu1, llu2);
  unit_test("%+15Lu - %+15Lu", llu1, llu2);

  unit_test("%.15Lu - %.15Lu", llu1, llu2);
  unit_test("% .15Lu - % .15Lu", llu1, llu2);
  unit_test("%-.15Lu - %-.15Lu", llu1, llu2);
  unit_test("%+.15Lu - %+.15Lu", llu1, llu2);

  unit_test("%15.15Lu - %15.15Lu", llu1, llu2);
  unit_test("% 15.15Lu - % 15.15Lu", llu1, llu2);
  unit_test("%-15.15Lu - %-15.15Lu", llu1, llu2);
  unit_test("%+15.15Lu - %+15.15Lu", llu1, llu2);

  // hu

  short unsigned int hu1 = 41;
  short unsigned int hu2 = -hu1;

  unit_test("%hu - %hu", hu1, hu2);
  unit_test("% hu - % hu", hu1, hu2);
  unit_test("%0hu - %0hu", hu1, hu2);
  unit_test("%-hu - %-hu", hu1, hu2);
  unit_test("%+hu - %+hu", hu1, hu2);

  unit_test("%15hu - %15hu", hu1, hu2);
  unit_test("% 15hu - % 15hu", hu1, hu2);
  unit_test("%-15hu - %-15hu", hu1, hu2);
  unit_test("%+15hu - %+15hu", hu1, hu2);

  unit_test("%.15hu - %.15hu", hu1, hu2);
  unit_test("% .15hu - % .15hu", hu1, hu2);
  unit_test("%-.15hu - %-.15hu", hu1, hu2);
  unit_test("%+.15hu - %+.15hu", hu1, hu2);

  unit_test("%15.15hu - %15.15hu", hu1, hu2);
  unit_test("% 15.15hu - % 15.15hu", hu1, hu2);
  unit_test("%-15.15hu - %-15.15hu", hu1, hu2);
  unit_test("%+15.15hu - %+15.15hu", hu1, hu2);

  // lu

  unsigned char hhu1 = 41;
  unsigned char hhu2 = -hhu1;

  unit_test("%hhu - %hhu", hhu1, hhu2);
  unit_test("% hhu - % hhu", hhu1, hhu2);
  unit_test("%0hhu - %0hhu", hhu1, hhu2);
  unit_test("%-hhu - %-hhu", hhu1, hhu2);
  unit_test("%+hhu - %+hhu", hhu1, hhu2);

  unit_test("%15hhu - %15hhu", hhu1, hhu2);
  unit_test("% 15hhu - % 15hhu", hhu1, hhu2);
  unit_test("%-15hhu - %-15hhu", hhu1, hhu2);
  unit_test("%+15hhu - %+15hhu", hhu1, hhu2);

  unit_test("%.15hu - %.15hu", hhu1, hhu2);
  unit_test("% .15hhu - % .15hhu", hhu1, hhu2);
  unit_test("%-.15hhu - %-.15hhu", hhu1, hhu2);
  unit_test("%+.15hhu - %+.15hhu", hhu1, hhu2);

  unit_test("%15.15hhu - %15.15hhu", hhu1, hhu2);
  unit_test("% 15.15hhu - % 15.15hhu", hhu1, hhu2);
  unit_test("%-15.15hhu - %-15.15hhu", hhu1, hhu2);
  unit_test("%+15.15hhu - %+15.15hhu", hhu1, hhu2);
}
END_TEST

START_TEST(tf) {
  //
  float fl1 = 1000.1234567;
  float fl2 = -fl1;

  unit_test("%f - %f", 0.0f, -0.0f);

  unit_test("%f - %f", fl1, fl2);
  unit_test("% f - % f", fl1, fl2);
  unit_test("%0f - %0f", fl1, fl2);
  unit_test("%-f - %-f", fl1, fl2);
  unit_test("%+f - %+f", fl1, fl2);

  unit_test("%15f - %15f", fl1, fl2);
  unit_test("% 15f - % 15f", fl1, fl2);
  unit_test("%-15f - %-15f", fl1, fl2);
  unit_test("%+15f - %+15f", fl1, fl2);

  unit_test("%.15f - %.15f", fl1, fl2);
  unit_test("% .15f - % .15f", fl1, fl2);
  unit_test("%-.15f - %-.15f", fl1, fl2);
  unit_test("%+.15f - %+.15f", fl1, fl2);
  unit_test("%#.15f - %#.15f", fl1, fl2);

  unit_test("%15.15f - %15.15f", fl1, fl2);
  unit_test("% 15.15f - % 15.15f", fl1, fl2);
  unit_test("%-15.15f - %-15.15f", fl1, fl2);
  unit_test("%+15.15f - %+15.15f", fl1, fl2);

  double db1 = 1000.1234567;
  double db2 = -db1;

  unit_test("%lf - %lf", db1, db2);
  unit_test("% lf - % lf", db1, db2);
  unit_test("%0lf - %0lf", db1, db2);
  unit_test("%-lf - %-lf", db1, db2);
  unit_test("%+lf - %+lf", db1, db2);

  unit_test("%15lf - %15lf", db1, db2);
  unit_test("% 15lf - % 15lf", db1, db2);
  unit_test("%-15lf - %-15lf", db1, db2);
  unit_test("%+15lf - %+15lf", db1, db2);

  unit_test("%.15lf - %.15lf", db1, db2);
  unit_test("% .15lf - % .15lf", db1, db2);
  unit_test("%-.15lf - %-.15lf", db1, db2);
  unit_test("%+.15lf - %+.15lf", db1, db2);
  unit_test("%#.15lf - %#.15lf", db1, db2);

  unit_test("%15.15lf - %15.15lf", db1, db2);
  unit_test("% 15.15lf - % 15.15lf", db1, db2);
  unit_test("%-15.15lf - %-15.15lf", db1, db2);
  unit_test("%+15.15lf - %+15.15lf", db1, db2);

  long double ldb1 = 1000.1234567;
  long double ldb2 = 1 - ldb1;

  unit_test("%Lf - %Lf", ldb1, ldb2);
  unit_test("% Lf - % Lf", ldb1, ldb2);
  unit_test("%0Lf - %0Lf", ldb1, ldb2);
  unit_test("%-Lf - %-Lf", ldb1, ldb2);
  unit_test("%+Lf - %+Lf", ldb1, ldb2);

  unit_test("%15Lf - %15Lf", ldb1, ldb2);
  unit_test("% 15Lf - % 15Lf", ldb1, ldb2);
  unit_test("%-15Lf - %-15Lf", ldb1, ldb2);
  unit_test("%+15Lf - %+15Lf", ldb1, ldb2);

  unit_test("%.15Lf - %.15Lf", ldb1, ldb2);
  unit_test("% .15Lf - % .15Lf", ldb1, ldb2);
  unit_test("%-.15Lf - %-.15Lf", ldb1, ldb2);
  unit_test("%+.15Lf - %+.15Lf", ldb1, ldb2);
  unit_test("%#.15Lf - %#.15Lf", ldb1, ldb2);

  unit_test("%15.15Lf - %15.15Lf", ldb1, ldb2);
  unit_test("% 15.15Lf - % 15.15Lf", ldb1, ldb2);
  unit_test("%-15.15Lf - %-15.15Lf", ldb1, ldb2);
  unit_test("%+15.15Lf - %+15.15Lf", ldb1, ldb2);

  unit_test("%15.25Lf - %15.25Lf", ldb1, ldb2);
  END_TEST
}

START_TEST(tg) {
  float gl1 = 1000.1234567;
  float gl2 = -gl1;

  unit_test("%g - %g", 0.0f, -0.0f);
  unit_test("%g - %g", gl1, gl2);
  unit_test("%g - %g", gl1, gl2);
  unit_test("% g - % g", gl1, gl2);
  unit_test("%0g - %0g", gl1, gl2);
  unit_test("%-g - %-g", gl1, gl2);
  unit_test("%+g - %+g", gl1, gl2);
  unit_test("%15g - %15g", gl1, gl2);
  unit_test("% 15g - % 15g", gl1, gl2);
  unit_test("%-15g - %-15g", gl1, gl2);
  unit_test("%+15g - %+15g", gl1, gl2);
  unit_test("%.15g - %.15g", gl1, gl2);
  unit_test("% .15g - % .15g", gl1, gl2);
  unit_test("%-.15g - %-.15g", gl1, gl2);
  unit_test("%+.15g - %+.15g", gl1, gl2);
  unit_test("%#.15g - %#.15g", gl1, gl2);
  unit_test("%15.15g - %15.15g", gl1, gl2);
  unit_test("% 15.15g - % 15.15g", gl1, gl2);
  unit_test("%-15.15g - %-15.15g", gl1, gl2);
  unit_test("%+15.15g - %+15.15g", gl1, gl2);
  END_TEST
}

START_TEST(te) {
  //
  float el1 = 1000.1234567;
  float el2 = -el1;

  unit_test("%e - %e", 0.0f, -0.0f);

  unit_test("%e - %e", el1, el2);
  unit_test("%E - %E", el1, el2);
  unit_test("% e - % e", el1, el2);
  unit_test("%0e - %0e", el1, el2);
  unit_test("%-e - %-e", el1, el2);
  unit_test("%+e - %+e", el1, el2);

  unit_test("%15e - %15e", el1, el2);
  unit_test("% 15e - % 15e", el1, el2);
  unit_test("%-15e - %-15e", el1, el2);
  unit_test("%+15e - %+15e", el1, el2);

  unit_test("%.15e - %.15e", el1, el2);
  unit_test("% .15e - % .15e", el1, el2);
  unit_test("%-.15e - %-.15e", el1, el2);
  unit_test("%+.15e - %+.15e", el1, el2);
  unit_test("%#.15e - %#.15e", el1, el2);

  unit_test("%15.15e - %15.15e", el1, el2);
  unit_test("% 15.15e - % 15.15e", el1, el2);
  unit_test("%-15.15e - %-15.15e", el1, el2);
  unit_test("%+15.15e - %+15.15e", el1, el2);

  double db1 = 1000.1234567;
  double db2 = -db1;

  unit_test("%le - %le", db1, db2);
  unit_test("% le - % le", db1, db2);
  unit_test("%0le - %0le", db1, db2);
  unit_test("%-le - %-le", db1, db2);
  unit_test("%+le - %+le", db1, db2);

  unit_test("%15le - %15le", db1, db2);
  unit_test("% 15le - % 15le", db1, db2);
  unit_test("%-15le - %-15le", db1, db2);
  unit_test("%+15le - %+15le", db1, db2);

  unit_test("%.15le - %.15le", db1, db2);
  unit_test("% .15le - % .15le", db1, db2);
  unit_test("%-.15le - %-.15le", db1, db2);
  unit_test("%+.15le - %+.15le", db1, db2);
  unit_test("%#.15le - %#.15le", db1, db2);

  unit_test("%15.15le - %15.15le", db1, db2);
  unit_test("% 15.15le - % 15.15le", db1, db2);
  unit_test("%-15.15le - %-15.15le", db1, db2);
  unit_test("%+15.15le - %+15.15le", db1, db2);

  long double ldb1 = 1000.1234567;
  long double ldb2 = 1 - ldb1;

  unit_test("%Le - %Le", ldb1, ldb2);
  unit_test("% Le - % Le", ldb1, ldb2);
  unit_test("%0Le - %0Le", ldb1, ldb2);
  unit_test("%-Le - %-Le", ldb1, ldb2);
  unit_test("%+Le - %+Le", ldb1, ldb2);

  unit_test("%15Le - %15Le", ldb1, ldb2);
  unit_test("% 15Le - % 15Le", ldb1, ldb2);
  unit_test("%-15Le - %-15Le", ldb1, ldb2);
  unit_test("%+15Le - %+15Le", ldb1, ldb2);

  unit_test("%.15Le - %.15Le", ldb1, ldb2);
  unit_test("% .15Le - % .15Le", ldb1, ldb2);
  unit_test("%-.15Le - %-.15Le", ldb1, ldb2);
  unit_test("%+.15Le - %+.15Le", ldb1, ldb2);
  unit_test("%#.15Le - %#.15Le", ldb1, ldb2);

  unit_test("%15.15Le - %15.15Le", ldb1, ldb2);
  unit_test("% 15.15Le - % 15.15Le", ldb1, ldb2);
  unit_test("%-15.15Le - %-15.15Le", ldb1, ldb2);
  unit_test("%+15.15Le - %+15.15Le", ldb1, ldb2);
}
END_TEST

//

START_TEST(test_s21_insert_null_src) {
  char *res = (s21_insert(NULL, "world", 0));
  ck_assert_ptr_eq(res, NULL);
  free(res);
}
END_TEST

// strerror

START_TEST(test_s21_strerror_unknown) {
  ck_assert(strncmp(s21_strerror(1000), strerror(1000), 12) == 0);
}
END_TEST

//

// strcat

START_TEST(test_s21_strncat_empty) {
  char dest[10] = "";
  char src[10] = "";
  char *result = s21_strncat(dest, src, 0);
  ck_assert_str_eq(result, "");
}
END_TEST

START_TEST(test_s21_strncat_partial) {
  char dest[10] = "hello";
  char src[10] = " world";
  char *result = s21_strncat(dest, src, 3);
  ck_assert_str_eq(result, "hello wo");
}
END_TEST

START_TEST(test_s21_strncat_full) {
  char dest[20] = "hello1";
  char src[10] = " world";
  char *result = s21_strncat(dest, src, 6);
  ck_assert_str_eq(result, "hello1 world");
}
END_TEST

//

// strtok

START_TEST(s21_tok) {
  char str[] = "hello world how are you";
  char *delim = " ";
  char *result = s21_strtok(str, delim);
  ck_assert_str_eq(result, "hello");
  result = s21_strtok(NULL, delim);
  ck_assert_str_eq(result, "world");
  result = s21_strtok(NULL, delim);
  ck_assert_str_eq(result, "how");
  result = s21_strtok(NULL, delim);
  ck_assert_str_eq(result, "are");
  result = s21_strtok(NULL, delim);
  ck_assert_str_eq(result, "you");
  result = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST
//

START_TEST(s21_brk) {
  char str1[] = "hello world";
  char str2[] = "hw";
  char *result = s21_strpbrk(str1, str2);
  ck_assert_ptr_eq(result, str1);
}
END_TEST
Suite *string_suite() {
  Suite *suite = suite_create("s21_string");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, s21_tok);

  tcase_add_test(tc_core, s21_brk);

  tcase_add_test(tc_core, test_s21_strncat_empty);
  tcase_add_test(tc_core, test_s21_strncat_partial);
  tcase_add_test(tc_core, test_s21_strncat_full);

  tcase_add_test(tc_core, test_s21_strerror_unknown);

  tcase_add_test(tc_core, test_s21_insert_null_src);
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strcmp);
  tcase_add_test(tc_core, test_s21_memcmp);
  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strstr);
  tcase_add_test(tc_core, test_s21_to_upper);
  tcase_add_test(tc_core, test_s21_to_lower);
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strcspn);

  tcase_add_test(tc_core, tc);
  tcase_add_test(tc_core, td);
  tcase_add_test(tc_core, tu);

  tcase_add_test(tc_core, tf);
  tcase_add_test(tc_core, ts);
  tcase_add_test(tc_core, te);
  tcase_add_test(tc_core, tg);

  tcase_add_test(tc_core, tx);
  tcase_add_test(tc_core, to);
  tcase_add_test(tc_core, tp);

  suite_add_tcase(suite, tc_core);
  return suite;
}

void test_string() {
  Suite *suite = string_suite();
  SRunner *sr = srunner_create(suite);

  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}