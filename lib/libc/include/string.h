#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char *);
void *memcpy(void *, const void *, size_t n);
int strcmp(const char *str1, const char *str2);

#endif
