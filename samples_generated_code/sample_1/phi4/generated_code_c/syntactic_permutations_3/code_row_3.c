#include <stdio.h>
#include <string.h>

void memcpy_custom(void *dest, const void *src, size_t num) {
    unsigned char *d = (unsigned char *) dest;
    const unsigned char *s = (const unsigned char *) src;

    for(size_t i = 0; i < num; i++) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6];
    
    memcpy_custom(buffer, "Hello", 5);
    printf("%s\n", buffer);

    return 0;
}