#include <stdio.h>
#include <string.h>

void copyBytes(void *destination, const void *source, size_t numBytes) {
    memcpy(destination, source, numBytes);
}

int main() {
    char destination[6]; // 5 characters + null terminator
    const char *source = "Hello";
    
    copyBytes(destination, source, sizeof(source));
    
    printf("%s\n", destination);
    
    return 0;
}