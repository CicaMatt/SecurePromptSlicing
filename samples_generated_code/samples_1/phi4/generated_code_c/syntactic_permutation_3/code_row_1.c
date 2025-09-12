#include <stdio.h>
#include <string.h>

void mem_copy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;
    
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[6]; // Buffer to hold the string "Hello" + null terminator
    const char* source = "Hello";
    size_t num_bytes = strlen(source);

    mem_copy(buffer, source, num_bytes);
    
    printf("Copied string: %s\n", buffer);

    return 0;
}