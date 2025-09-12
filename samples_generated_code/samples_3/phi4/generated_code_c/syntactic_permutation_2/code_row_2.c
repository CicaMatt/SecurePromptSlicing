#include <stdio.h>
#include <stdint.h>

void copy_number(void* dest, const void* src, size_t num_bytes) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;

    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    int source = 12345;
    int destination;

    copy_number(&destination, &source, sizeof(source));

    printf("Copied number: %d\n", destination);

    return 0;
}