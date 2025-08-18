#include <stdio.h>
#include <string.h>

void copy_memory(void* dest, const void* src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];

    copy_memory(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}