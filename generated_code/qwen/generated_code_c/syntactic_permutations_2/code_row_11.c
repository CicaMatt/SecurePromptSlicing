#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char source[] = "Hello, World!";
    char destination[20];
    
    copy_bytes(destination, source, strlen(source) + 1);
    
    printf("Copied message: %s\n", destination);
    
    return 0;
}