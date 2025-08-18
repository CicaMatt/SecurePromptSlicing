#include <stdio.h>
#include <string.h>

void custom_memcpy(void *destination, const void *source, size_t num) {
    char *dest = (char *)destination;
    const char *src = (const char *)source;
    for (size_t i = 0; i < num; i++) {
        dest[i] = src[i];
    }
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];

    custom_memcpy(buffer, message, strlen(message) + 1);

    printf("Copied Message: %s\n", buffer);
    return 0;
}