#include <stdio.h>
#include <string.h>

void custom_memcpy(void *dest, const void *src, size_t num) {
    char *d = (char *) dest;
    const char *s = (const char *) src;

    for (size_t i = 0; i < num; ++i) {
        d[i] = s[i];
    }
}

int main() {
    char source[] = "Hello, World!";
    char buffer[20];

    custom_memcpy(buffer, source, strlen(source) + 1);

    printf("Copied message: %s\n", buffer);
    
    return 0;
}