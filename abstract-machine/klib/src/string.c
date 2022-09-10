#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t ret = 0;
  while (s[ret] != '\0') {
    ++ret;
  }
  return ret;
}

char *strcpy(char *dst, const char *src) {
  size_t i;
  for (i = 0; src[i] != '\0'; i++)
     dst[i] = src[i];
  dst[i] = '\0';

  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++)
     dst[i] = src[i];
  for ( ; i < n; i++)
     dst[i] = '\0';

  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t dst_len = strlen(dst);
  size_t i;

  for (i = 0 ; src[i] != '\0' ; i++)
     dst[dst_len + i] = src[i];
  dst[dst_len + i] = '\0';

  return dst;
}

int strcmp(const char *s1, const char *s2) {
  size_t i;
  size_t len = strlen(s1);
  for (i = 0; i < len && s1[i] == s2[i]; ++i);
  return s1[i] - s2[i];
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;
  for (i = 0; i < n && s1[i] != '\0' && s1[i] == s2[i]; ++i);
  if (i == n) {
    return 0;
  }
  return s1[i] - s2[i];
}

void *memset(void *s, int c, size_t n) {
  unsigned char* ret = (unsigned char*)s;
  while (n--) {
    *ret = (unsigned char) n;
    ++ret;
  }
  *ret = '\0';
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  size_t i;
  unsigned char buf[n];
  for (i = 0; i < n; ++i) {
    buf[i] = ((unsigned char*)src)[i];
  }
  for (i = 0; i < n; ++i) {
    ((unsigned char*)dst)[i] = buf[i];
  }
  return dst;
}

void *memcpy(void *dst, const void *src, size_t n) {
  size_t i;
  for (i = 0; i < n; ++i) {
    ((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
  }

  return dst;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  unsigned char* ss1 = (unsigned char*) s1;
  unsigned char* ss2 = (unsigned char*) s2;

  size_t i;
  for (i = 0; i < n && ss1[i] != '\0' && ss1[i] == ss2[i]; ++i);
  if (i == n) {
    return 0;
  }
  return ss1[i] - ss2[i];
}

#endif
