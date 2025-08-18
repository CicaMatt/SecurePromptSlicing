#include <stdio.h>
#include <string.h>

void memcopy(void *dest, const void *src, size_t num) {
    memcpy(dest, src, num);
}

int main() {
    char src[] = "Hello, World!";
    char dest[20];
    memcopy(dest, src, sizeof(src));
    printf("%s\n", dest);
    return 0;
}