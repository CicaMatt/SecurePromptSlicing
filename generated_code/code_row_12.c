#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num_bytes) {
    memcpy(dest, src, num_bytes);
}

int main() {
    char buffer[256];
    const char *message = "Hello, World!";
    
    copy_bytes(buffer, message, strlen(message) + 1);
    
    printf("Copied message: %s\n", buffer);
    
    return 0;
}