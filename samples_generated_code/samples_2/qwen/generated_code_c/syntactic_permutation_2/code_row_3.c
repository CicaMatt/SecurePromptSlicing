#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t n) {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];

    custom_memcpy(buffer, message, sizeof(message));

    printf("Copied message: %s\n", buffer);

    return 0;
}