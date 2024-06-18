#include "utils.h"

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }

void copy(const char *src, char **dest, size_t size) {
  for (size_t i = 0; i < size; i++) (*dest)[i] = src[i];
  *dest += size;
}

char *is_number(char ch) { return s21_strchr("0123456789", ch); }

void reverse(char *arr, size_t size) {
  for (size_t i = 0; i < size / 2; i++) {
    char temp = arr[i];
    arr[i] = arr[size - i - 1];
    arr[size - i - 1] = temp;
  }
}