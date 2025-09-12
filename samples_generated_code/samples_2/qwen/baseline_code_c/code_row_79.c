#include <stdio.h>
#include <string.h>

void copy_memory(void *destination, const void *source, size_t num_bytes) {
    memcpy(destination, source, num_bytes);
}

int main() {
    char message[] = "Hello, World!";
    char buffer[20];
    
    copy_memory(buffer, message, sizeof(message));
    
    printf("Copied Message: %s\n", buffer);
    
    return 0;
}