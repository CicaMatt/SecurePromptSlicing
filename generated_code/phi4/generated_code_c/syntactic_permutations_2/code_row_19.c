#include <stdio.h>
#include <stdlib.h>

void* my_memcpy(void* dest, const void* src, size_t n) {
    char* d = (char*)dest;
    const char* s = (const char*)src;

    for(size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }

    return dest;
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    my_memcpy(buffer, source, sizeof(source));
    
    printf("Copied string: %s\n", buffer);

    return 0;
}