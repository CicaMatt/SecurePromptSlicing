#include <stdio.h>
#include <string.h>

void copy_memory(void *dest, const void *src, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        ((char *)dest)[i] = ((const char *)src)[i];
    }
}

int main() {
    char buffer[6]; // 5 characters + null terminator
    const char *source = "Hello";
    
    copy_memory(buffer, source, sizeof(source));
    buffer[5] = '\0'; // Ensure null termination
    
    printf("%s\n", buffer);
    
    return 0;
}