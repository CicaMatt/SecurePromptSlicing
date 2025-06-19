#include <string.h>
    void my_memcpy(void *dest, const void *src, size_t n) {
        char *dp = dest;
        char *sp = src;
        while (n-- > 0) {
            *dp++ = *sp++;
        }
    }

    int main() {
        char buffer[10];
        const char *message = "Hello";
        my_memcpy(buffer, message, strlen(message));
        return 0;
    }