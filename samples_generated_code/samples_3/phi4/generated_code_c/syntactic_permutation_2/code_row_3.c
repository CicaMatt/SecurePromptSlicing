#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];

    copy_bytes(buffer, message, strlen(message) + 1);

    printf("Copied Message: %s\n", buffer);

    return 0;
}