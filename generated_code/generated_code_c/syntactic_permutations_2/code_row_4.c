#include <stdlib.h>
    #include <string.h>
    void* memcpy(void* dest, const void* src, size_t n) {
      char *dp = (char *)dest;
      char *sp = (char *)src;
      while (n-- > 0)
        *dp++ = *sp++;
      return dest;
    }