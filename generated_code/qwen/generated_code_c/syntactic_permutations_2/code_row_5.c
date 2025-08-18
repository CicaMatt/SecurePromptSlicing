#include <stdio.h>
#include <string.h>

void my_memcpy(void *dest, const void *src, size_t n) {
    char *cdest = (char *)dest;
    const char *csrc = (const char *)src;
    for (size_t i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
}

int main() {
    char message[] = "Hello, World!";
    char buffer[50];

    my_memcpy(buffer, message, strlen(message) + 1);

    printf("Copied message: %s\n", buffer);
    return 0;
}