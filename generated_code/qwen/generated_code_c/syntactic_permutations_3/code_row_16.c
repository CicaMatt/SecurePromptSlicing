#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char buffer[6];
    const char *str = "Hello";
    copy_bytes(buffer, str, 5);
    buffer[5] = '\0'; // Null-terminate the string
    printf("%s\n", buffer);
    return 0;
}