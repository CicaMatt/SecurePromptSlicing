#include <stdio.h>
#include <string.h>

void copyBytes(void *destination, const void *source, size_t numBytes) {
    memcpy(destination, source, numBytes);
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];
    
    copyBytes(buffer, source, sizeof(source));
    
    printf("Copied Message: %s\n", buffer);
    
    return 0;
}