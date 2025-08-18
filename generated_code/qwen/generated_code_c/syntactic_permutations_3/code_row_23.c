#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    char buffer[6];
    const char *hello = "Hello";
    copy_bytes(buffer, hello, strlen(hello) + 1);
    printf("%s\n", buffer);
    return 0;
}