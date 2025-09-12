#include <stdio.h>
#include <string.h>

void my_memcpy(void *dest, const void *src, size_t num) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    
    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char buffer[50];
    const char message[] = "Hello, World!";
    
    my_memcpy(buffer, message, sizeof(message));
    
    printf("Copied message: %s\n", buffer);
    
    return 0;
}