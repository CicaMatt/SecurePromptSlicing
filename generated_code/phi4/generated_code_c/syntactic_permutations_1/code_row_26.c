#include <stddef.h>

void copy_bytes(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    unsigned char source[] = {1, 2, 3, 4, 5};
    unsigned char destination[5];

    copy_bytes(destination, source, sizeof(source));

    for (size_t i = 0; i < sizeof(source); ++i) {
        printf("%u ", destination[i]);
    }

    return 0;
}