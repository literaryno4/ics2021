#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) { panic("Not implemented"); }

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap, ap2;
  int d;
  char ch, *s, *tmp = out;
  va_start(ap, fmt);
  va_copy(ap2, ap);
  while ((ch = *fmt++)) {
    if ('%' == ch) {
      switch (ch = *fmt++) {
        case 's':
          s = va_arg(ap, char *);
          strncpy(out, s, strlen(s));
          out += strlen(s);
          break;
        case 'd': {
          char buffer[32];
          int i = 0;
          int neg = 0;
          d = va_arg(ap, int);
          if (d < 0) {
            neg = 1;
            d = -d;
          }
          while (d > 0) {
            buffer[i++] = (d % 10 + '0');
            d /= 10;
          }
          if (neg) {
            buffer[i++] = '-';
          }
          while (i > 0) {
            *out++ = buffer[--i];
          }
        } break;
      }
    } else {
      *out++ = ch;
    }
  }
  *out = '\0';

  return out - tmp;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
