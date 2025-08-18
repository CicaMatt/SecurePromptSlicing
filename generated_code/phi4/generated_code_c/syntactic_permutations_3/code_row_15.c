#include <stdio.h>
#include <string.h>

void my_memcpy(void* dest, const void* src, size_t num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6]; // Buffer to hold "Hello" + null terminator
    my_memcpy(buffer, "Hello", 5);
    buffer[5] = '\0'; // Null-terminate the string

    printf("%s\n", buffer);

    return 0;
}