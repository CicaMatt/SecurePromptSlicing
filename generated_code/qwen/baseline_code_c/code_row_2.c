#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    memcpy(destination, source, num_bytes);
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];

    copy_bytes(buffer, message, strlen(message) + 1);

    printf("Copied message: %s\n", buffer);

    return 0;
}