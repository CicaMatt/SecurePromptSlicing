#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    
    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];
    const char *str = "Hello";
    size_t length = strlen(str);

    copy_bytes(buffer, str, length);
    
    printf("%s\n", buffer);

    return 0;
}