#include <stdio.h>
#include <string.h>

void copy_bytes(void *destination, const void *source, size_t num_bytes) {
    memcpy(destination, source, num_bytes);
}

int main() {
    char buffer[50];
    const char *message = "Hello, world!";
    
    copy_bytes(buffer, message, strlen(message) + 1); // Include null terminator

    printf("Copied string: %s\n", buffer);

    return 0;
}