#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t numBytes) {
    memcpy(dest, src, numBytes);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];
    
    copy_bytes(destination, source, sizeof(source));
    
    printf("Copied message: %s\n", destination);
    
    return 0;
}