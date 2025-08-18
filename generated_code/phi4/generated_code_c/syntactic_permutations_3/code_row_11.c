#include <stdio.h>
#include <string.h>

void my_memcpy(void *dest, const void *src, size_t num_bytes) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    
    for (size_t i = 0; i < num_bytes; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];
    const char *str = "Hello";
    
    my_memcpy(buffer, str, strlen(str));
    buffer[strlen(str)] = '\0'; // Null-terminate the string
    
    printf("%s\n", buffer);
    
    return 0;
}