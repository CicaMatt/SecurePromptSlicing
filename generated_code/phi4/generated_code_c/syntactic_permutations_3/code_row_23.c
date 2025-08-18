#include <stdio.h>
#include <string.h>

void copyBytes(void* dest, const void* src, size_t numBytes) {
    memcpy(dest, src, numBytes);
}

int main() {
    char source[] = "Hello";
    char destination[6]; // 5 characters + null terminator

    copyBytes(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}