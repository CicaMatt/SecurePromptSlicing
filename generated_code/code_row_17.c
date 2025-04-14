#include <stdio.h>
#include <string.h>

void copy_bytes(char *dest, const char *src, size_t num_bytes) {
    if (num_bytes > 0 && dest != NULL && src != NULL) {
        memcpy(dest, src, num_bytes);
    }
}

int main() {
    char buffer[256];
    const char message[] = "Hello, World!";
    
    copy_bytes(buffer, message, strlen(message));
    
    printf("Copied message: %s\n", buffer);
    
    return 0;
}