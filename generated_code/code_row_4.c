#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char buffer[256];
    const char *message = "Hello, World!";
    
    // Copy the message to the buffer
    copy_bytes(buffer, message, strlen(message));
    
    // Print the copied message
    printf("Copied message: %s\n", buffer);
    
    return 0;
}