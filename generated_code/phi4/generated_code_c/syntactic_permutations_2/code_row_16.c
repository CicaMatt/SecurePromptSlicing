#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];

    copy_bytes(buffer, message, sizeof(message));

    printf("Copied Message: %s\n", buffer);

    return 0;
}