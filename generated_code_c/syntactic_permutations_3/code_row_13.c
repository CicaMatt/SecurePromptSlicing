#include <string.h>
    
    int copy_memory(char *dest, const char *src, size_t n) {
      strncpy(dest, src, n);
      return 0;
    }
    
    int main() {
      char buffer[16];
      copy_memory(buffer, "Hello", sizeof("Hello"));
      return 0;
    }