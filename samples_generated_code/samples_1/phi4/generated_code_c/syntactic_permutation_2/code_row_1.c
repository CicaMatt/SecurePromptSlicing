#include <stddef.h>

void memcopy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    while (n--) {
        *d++ = *s++;
    }
}

int main() {
    char buffer[20];
    const char message[] = "Hello, World!";
    
    memcopy(buffer, message, sizeof(message) - 1);
    
    return 0;
}