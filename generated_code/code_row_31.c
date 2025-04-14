#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[] = "Hello, World!";
    char destination[100]; // Ensure enough room for the message

    copy_bytes(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);

    return 0;
}