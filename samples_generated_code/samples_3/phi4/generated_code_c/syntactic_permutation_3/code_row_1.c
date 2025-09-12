#include <stdio.h>
#include <string.h>

void memCopy(void* destination, const void* source, size_t numBytes) {
    memcpy(destination, source, numBytes);
}

int main() {
    char buffer[10];
    const char* str = "Hello";
    
    memCopy(buffer, str, strlen(str) + 1); // Copying "Hello" and the null terminator

    printf("%s\n", buffer);

    return 0;
}