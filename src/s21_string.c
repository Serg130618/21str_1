#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  if (dest == NULL || src == NULL) return NULL;

  char *p = dest;
  while (*p != '\0') p++;

  while (*src != '\0') *p++ = *src++;

  *p = '\0';
  return dest;
}

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (src == NULL || str == NULL) return NULL;

  size_t src_len = s21_strlen(src);
  size_t str_len = s21_strlen(str);

  if (start_index > src_len) return NULL;

  char *result = calloc(src_len + str_len + 1, sizeof(char));
  if (result == NULL) return NULL;

  s21_strncpy(result, src, start_index);
  s21_strcat(result, str);
  s21_strcat(result, src + start_index);

  return result;
}

size_t s21_strlen(const char *str) {
  size_t len = 0;
  while (str[len] != '\0') len++;

  return len;
}

char *s21_strchr(const char *str, int c) {
  size_t len = s21_strlen(str);

  for (size_t i = 0; i < len + 1; i++)
    if (str[i] == c) return (char *)&str[i];

  return NULL;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) return str1[i] - str2[i];
    if (str1[i] == '\0' || str2[i] == '\0') return 0;
  }

  return 0;
}

int s21_strcmp(const char *str1, const char *str2) {
  while (*str1 != '\0' && *str2 != '\0') {
    if (*str1 != *str2) {
      return (int)*str1 - (int)*str2;
    }
    str1++;
    str2++;
  }

  return (int)(*str1 - *str2);
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const uint8_t *ptr1 = str1;
  const uint8_t *ptr2 = str2;

  for (size_t i = 0; i < n; i++)
    if (ptr1[i] != ptr2[i]) return ptr1[i] - ptr2[i];

  return 0;
}

void *s21_memchr(const void *str, int c, size_t n) {
  const uint8_t *ptr = str;
  const uint8_t ch = (uint8_t)c;

  while (n--) {
    if (*ptr == ch) return (void *)ptr;
    ptr++;
  }
  return NULL;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
  uint8_t *dest_ptr = dest;
  const uint8_t *src_ptr = src;

  for (size_t i = 0; i < n; i++) *dest_ptr++ = *src_ptr++;

  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  uint8_t *str_ptr = str;
  const uint8_t ch = (uint8_t)c;

  for (size_t i = 0; i < n; i++) str_ptr[i] = ch;

  return str;
}

char *s21_strrchr(const char *str, int c) {
  size_t len = s21_strlen(str);

  for (size_t i = len + 1; i > 0; i--)
    if (str[i] == c) return (char *)&str[i];

  return NULL;
}

char *s21_strstr(const char *haystack, const char *needle) {
  size_t haystack_len = s21_strlen(haystack);
  size_t needle_len = s21_strlen(needle);

  if (needle_len == 0) return (char *)haystack;

  for (size_t i = 0; i <= haystack_len - needle_len; i++) {
    size_t j;
    for (j = 0; j < needle_len; j++)
      if (haystack[i + j] != needle[j]) break;

    if (j == needle_len) return (char *)&haystack[i];
  }

  return NULL;
}

void *s21_to_upper(const char *str) {
  size_t len = s21_strlen(str);
  char *result = calloc(len, sizeof(char));

  for (size_t i = 0; i < len; i++) {
    if (str[i] >= 97 && str[i] <= 122) {
      result[i] = str[i] - 32;
    } else {
      result[i] = str[i];
    }
  }

  return result;
}

void *s21_to_lower(const char *str) {
  size_t len = s21_strlen(str);
  char *result = calloc(len, sizeof(char));

  for (size_t i = 0; i < len; i++) {
    if (str[i] >= 65 && str[i] <= 90) {
      result[i] = str[i] + 32;
    } else {
      result[i] = str[i];
    }
  }

  return result;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';

  return dest;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  char *d = dest;
  while (*dest != '\0') {
    dest++;
  }
  while (n > 0 && *src != '\0') {
    *dest++ = *src++;
    n--;
  }
  if (n == 0) {
    *dest = '\0';
  }
  return d;
}

size_t s21_strcspn(const char *str1, const char *str2) {
  size_t count = 0;
  const char *p = str1;
  while (*p != '\0') {
    const char *r = str2;
    while (*r != '\0') {
      if (*p == *r) {
        return count;
      }
      r++;
    }
    p++;
    count++;
  }
  return count;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last_token;
  char *p;

  if (str == NULL) str = last_token;
  if (str == NULL) return NULL;

  str += s21_strspn(str, delim);

  if (*str == '\0') return NULL;

  p = str;

  str += s21_strcspn(str, delim);

  if (*str) *str++ = '\0';

  last_token = str;
  return p;
}

//
size_t s21_strspn(const char *str, const char *accept) {
  const char *p = str;
  size_t count = 0;
  while (*p != '\0') {
    const char *a = accept;
    int found = 0;
    while (*a != '\0') {
      if (*p == *a) {
        found = 1;
        break;
      }
      a++;
    }
    if (!found) {
      return count;
    }
    p++;
    count++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  const char *ptr1 = 0;
  const char *ptr2 = 0;
  if (*str2 == '\0') return NULL;
  for (ptr1 = str1; *ptr1 != '\0'; ptr1++) {
    for (ptr2 = str2; *ptr2 != '\0'; ptr2++) {
      if (*ptr1 == *ptr2) return (char *)ptr1;
    }
  }
  return NULL;
}

///////////

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int count_printed = 0;

  for (char *p = (char *)format; *p; p++) {
    char current_char = *p;
    if (current_char == '%') {
      if (*(p + 1) == '%') {
        s21_sputchar(&str, '%');

        count_printed++;
        p++;
      } else {
        struct format_unit _current_format_unit = s21_parse_format(&p, &args);
        count_printed += handle_format_unit(_current_format_unit, &str, args);
      }
    } else {
      count_printed++;
      s21_sputchar(&str, current_char);
    }
  }

  va_end(args);
  s21_sputchar(&str, '\0');

  return count_printed;
}

char *s21_strerror(int errnum) {
#if defined(__APPLE__)
  char *err[] = {"Undefined error: 0",
                 "Operation not permitted",
                 "No such file or directory",
                 "No such process",
                 "Interrupted system call",
                 "Input/output error",
                 "Device not configured",
                 "Argument list too long",
                 "Exec format error",
                 "Bad file descriptor",
                 "No child processes",
                 "Resource deadlock avoided",
                 "Cannot allocate memory",
                 "Permission denied",
                 "Bad address",
                 "Block device required",
                 "Resource busy",
                 "File exists",
                 "Cross-device link",
                 "Operation not supported by device",
                 "Not a directory",
                 "Is a directory",
                 "Invalid argument",
                 "Too many open files in system",
                 "Too many open files",
                 "Inappropriate ioctl for device",
                 "Text file busy",
                 "File too large",
                 "No space left on device",
                 "Illegal seek",
                 "Read-only file system",
                 "Too many links",
                 "Broken pipe",
                 "Numerical argument out of domain",
                 "Result too large",
                 "Resource temporarily unavailable",
                 "Operation now in progress",
                 "Operation already in progress",
                 "Socket operation on non-socket",
                 "Destination address required",
                 "Message too long",
                 "Protocol wrong type for socket",
                 "Protocol not available",
                 "Protocol not supported",
                 "Socket type not supported",
                 "Operation not supported",
                 "Protocol family not supported",
                 "Address family not supported by protocol family",
                 "Address already in use",
                 "Can't assign requested address",
                 "Network is down",
                 "Network is unreachable",
                 "Network dropped connection on reset",
                 "Software caused connection abort",
                 "Connection reset by peer",
                 "No buffer space available",
                 "Socket is already connected",
                 "Socket is not connected",
                 "Can't send after socket shutdown",
                 "Too many references: can't splice",
                 "Operation timed out",
                 "Connection refused",
                 "Too many levels of symbolic links",
                 "File name too long",
                 "Host is down",
                 "No route to host",
                 "Directory not empty",
                 "Too many processes",
                 "Too many users",
                 "Disc quota exceeded",
                 "Stale NFS file handle",
                 "Too many levels of remote in path",
                 "RPC struct is bad",
                 "RPC version wrong",
                 "RPC prog. not avail",
                 "Program version wrong",
                 "Bad procedure for program",
                 "No locks available",
                 "Function not implemented",
                 "Inappropriate file type or format",
                 "Authentication error",
                 "Need authenticator",
                 "Device power is off",
                 "Device error",
                 "Value too large to be stored in data type",
                 "Bad executable (or shared library)",
                 "Bad CPU type in executable",
                 "Shared library version mismatch",
                 "Malformed Mach-o file",
                 "Operation canceled",
                 "Identifier removed",
                 "No message of desired type",
                 "Illegal byte sequence",
                 "Attribute not found",
                 "Bad message",
                 "EMULTIHOP (Reserved)",
                 "No message available on STREAM",
                 "ENOLINK (Reserved)",
                 "No STREAM resources",
                 "Not a STREAM",
                 "Protocol error",
                 "STREAM ioctl timeout",
                 "Operation not supported on socket",
                 "Policy not found",
                 "State not recoverable",
                 "Previous owner died",
                 "Interface output queue is full",
                 "Unknown error"};
#else
  char *err[] = {"any references: cannot splice",
                 "Connection timed out",
                 "Connection refused",
                 "Host is down",
                 "No route to host",
                 "Operation already in progress",
                 "Operation now in progress",
                 "Stale file handle",
                 "Structure needs cleaning",
                 "Not a XENIX named type file",
                 "No XENIX semaphores available",
                 "Is a named type file",
                 "Remote I/O error",
                 "Disk quota exceeded",
                 "No medium found",
                 "Wrong medium type",
                 "Operation canceled",
                 "Required key not available",
                 "Key has expired",
                 "Key has been revoked",
                 "Key was rejected by service",
                 "Owner died",
                 "State not recoverable",
                 "Operation not possible due to RF-kill",
                 "Memory page has hardware error"};
#endif
  int max_N = sizeof(err) / sizeof(char *);

  static char res_err[100];

  res_err[0] = 0;

  if (*err[0] == 'U') max_N = 107;

  if (errnum > 0 && errnum <= max_N) {
    s21_strncpy(res_err, err[errnum], 100);
  } else {
    s21_strncpy(res_err, "Unknown error: ", 100);
  }
  return res_err;
}