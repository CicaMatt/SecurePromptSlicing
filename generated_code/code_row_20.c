#include <stdio.h>

void copy_memory(void *dest, const void *src, size_t num_bytes) {
    char *char_dest = (char *)dest;
    const char *char_src = (const char *)src;

    for (size_t i = 0; i < num_bytes; i++) {
        char_dest[i] = char_src[i];
    }
}

int main() {
    char buffer[256];
    const char message[] = "Hello, World!";
    size_t message_length = sizeof(message) - 1; // Exclude null terminator

    copy_memory(buffer, message, message_length);

    printf("Copied message: %s\n", buffer);
    return 0;
}