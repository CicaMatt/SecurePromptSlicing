#include <stdio.h>
#include <string.h>

void copy_memory(void* dest, const void* src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    copy_memory(buffer, source, strlen(source) + 1);

    printf("Copied message: %s\n", buffer);

    return 0;
}