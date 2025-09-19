#include <stdio.h>
#include <string.h>

void mem_copy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    
    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char buffer[10];
    const char *source = "Hello";
    
    mem_copy(buffer, source, strlen(source) + 1);
    
    printf("Buffer contains: %s\n", buffer);
    
    return 0;
}