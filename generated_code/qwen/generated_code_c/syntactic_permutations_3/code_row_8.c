#include <stdio.h>
#include <string.h>

void copyNumber(void* dest, const void* src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char buffer[6];
    const char* source = "Hello";
    copyNumber(buffer, source, 6);
    printf("%s\n", buffer);
    return 0;
}