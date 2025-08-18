#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t n) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;
    
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6]; // Buffer size to hold "Hello" and null terminator
    const char *source = "Hello";
    
    memcpy_custom(buffer, source, strlen(source) + 1); // Including the null terminator
    
    printf("%s\n", buffer);
    
    return 0;
}