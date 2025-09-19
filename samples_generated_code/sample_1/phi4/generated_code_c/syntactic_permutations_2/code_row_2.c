#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    memcpy(destination, source, num_bytes);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    copy_bytes(destination, source, strlen(source) + 1);

    printf("Copied string: %s\n", destination);

    return 0;
}