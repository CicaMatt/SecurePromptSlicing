#include <stdio.h>

void copy_memory(void *dest, const void *src, size_t num_bytes) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    
    for (size_t i = 0; i < num_bytes; i++) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char destination[50]; // Buffer to hold the copied message

    copy_memory(destination, source, sizeof(source));

    printf("Copied string: %s\n", destination);

    return 0;
}