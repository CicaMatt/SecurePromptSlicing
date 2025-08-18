#include <stdio.h>
#include <string.h>

void copy_bytes(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    
    copy_bytes(dest, src, strlen(src) + 1);
    
    printf("Copied string: %s\n", dest);
    
    return 0;
}