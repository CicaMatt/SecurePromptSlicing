#include <stdio.h>
#include <string.h>

void my_memcpy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;

    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[10];
    const char *source = "Hello";
    
    my_memcpy(buffer, source, strlen(source) + 1);
    
    printf("%s\n", buffer); // Output should be: Hello

    return 0;
}