#include <stdio.h>
#include <string.h>

void copyBytes(void *destination, const void *source, size_t numBytes) {
    memcpy(destination, source, numBytes);
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    
    copyBytes(dest, src, strlen(src) + 1);
    
    printf("Copied string: %s\n", dest);
    
    return 0;
}