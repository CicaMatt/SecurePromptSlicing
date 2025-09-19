#include <stdio.h>
#include <string.h>

void copyBytes(void* dest, const void* src, size_t numBytes) {
    for (size_t i = 0; i < numBytes; ++i) {
        ((unsigned char*)dest)[i] = ((const unsigned char*)src)[i];
    }
}

int main() {
    char buffer[11]; // One extra byte for the null terminator
    const char* str = "Hello";
    
    copyBytes(buffer, str, strlen(str));
    buffer[strlen(str)] = '\0'; // Null-terminate the string
    
    printf("Copied String: %s\n", buffer);
    return 0;
}