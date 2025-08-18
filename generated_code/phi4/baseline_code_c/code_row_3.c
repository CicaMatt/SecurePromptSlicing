#include <stdio.h>
#include <string.h>

void memcopy(void *dest, const void *src, size_t num) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    unsigned char buffer[10];

    memcopy(buffer, "Hello", strlen("Hello") + 1);

    printf("%s\n", buffer);
    
    return 0;
}