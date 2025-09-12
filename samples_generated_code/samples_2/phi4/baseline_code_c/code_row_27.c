#include <stdio.h>
#include <string.h>

void memcpy_custom(void* dest, const void* src, size_t num_bytes) {
    char* d = (char*)dest;
    const char* s = (const char*)src;

    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];

    memcpy_custom(buffer, "Hello", 6);

    printf("%s\n", buffer);

    return 0;
}