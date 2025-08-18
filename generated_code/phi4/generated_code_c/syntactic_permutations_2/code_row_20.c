#include <stdio.h>
#include <string.h>

void copy_number(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src = 12345;
    char dest[10];
    
    copy_number(dest, &src, sizeof(src));
    
    printf("Copied number: %d\n", *(int *)dest);
    return 0;
}