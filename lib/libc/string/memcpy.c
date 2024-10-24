#include <string.h>

void *memcpy(void *dest_str, const void *src_str, size_t n) {
  char *dest = (char *) dest_str;
  const char *src = (const char *) src_str;

  for (size_t i = 0; i < n; i++) dest[i] = src[i];

  return dest_str;
}
