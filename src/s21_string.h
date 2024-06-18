#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "format_unit.h"
#include "handlers.h"
#include "s21_output.h"

int s21_strcmp(const char *str1, const char *str2);
size_t s21_strspn(const char *str, const char *accept);
int s21_vsprintf(char *str, const char *format, va_list args);

// 1
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str.
void *s21_memchr(const void *str, int c, size_t n);

// 2
// Сравнивает первые n байтов str1 и str2.
int s21_memcmp(const void *str1, const void *str2, size_t n);

// 3
// Копирует n символов из src в dest.
void *s21_memcpy(void *dest, const void *src, size_t n);

// 4
// Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str.
void *s21_memset(void *str, int c, size_t n);

// 5
// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.
char *s21_strncat(char *dest, const char *src, size_t n);

// 6
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strchr(const char *str, int c);

// 7
// Сравнивает не более первых n байтов str1 и str2.
int s21_strncmp(const char *str1, const char *str2, size_t n);

// 8
// Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, size_t n);

// 9
// Вычисляет длину начального сегмента str1, который полностью состоит из
// символов, не входящих в str2.
size_t s21_strcspn(const char *str1, const char *str2);

// 10
// Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает
// указатель на строку с сообщением об ошибке. Нужно объявить макросы,
// содержащие массивы сообщений об ошибке для операционных систем mac и linux.
// Описания ошибок есть в оригинальной библиотеке. Проверка текущей ОС
// осуществляется с помощью директив.
char *s21_strerror(int errnum);

// 11
// Вычисляет длину строки str, не включая завершающий нулевой символ.
size_t s21_strlen(const char *str);

// 12
// Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2.
char *s21_strpbrk(const char *str1, const char *str2);

// 13
// Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
char *s21_strrchr(const char *str, int c);

// 14
// Находит первое вхождение всей строки needle (не включая завершающий нулевой
// символ), которая появляется в строке haystack.
char *s21_strstr(const char *haystack, const char *needle);

// 15
// Разбивает строку str на ряд токенов, разделенных delim.
char *s21_strtok(char *str, const char *delim);

// str − Это С-строка, которую функция обрабатывает в качестве источника для
// извлечения данных;
// ---------------------------
// format −  это С-строка, содержащая один или несколько следующих элементов:
// пробельный символ, непробельный символ и спецификаторы формата. Спецификатор
// формата для печатающих функций следует прототипу:
// %[флаги][ширина][.точность][длина]спецификатор. Спецификатор формата для
// сканирующих функций следует прототипу: %[*][ширина][длина]спецификатор.

// 16
// TODO
// Считывает форматированный ввод из строки.
int s21_sscanf(const char *str, const char *format, ...);

// 17
// Отправляет форматированный вывод в строку, на которую указывает str.
int s21_sprintf(char *str, const char *format, ...);

// 18
// Возвращает копию строки (str), преобразованной в верхний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL.
void *s21_to_upper(const char *str);

// 19
// Возвращает копию строки (str), преобразованной в нижний регистр. В случае
// какой-либо ошибки следует вернуть значение NULL.
void *s21_to_lower(const char *str);

// 20
// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL.
void *s21_insert(const char *src, const char *str, size_t start_index);

// 21
// Возвращает новую строку, в которой удаляются все начальные и конечные
// вхождения набора заданных символов (trim_chars) из данной строки (src). В
// случае какой-либо ошибки следует вернуть значение NULL.
void *s21_trim(const char *src, const char *trim_chars);

#endif
