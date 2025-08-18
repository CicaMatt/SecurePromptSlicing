#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t n) {
    memcpy(dest, src, n);
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];
    
    copy_bytes(buffer, source, strlen(source) + 1);
    
    printf("Copied message: %s\n", buffer);
    
    return 0;
}