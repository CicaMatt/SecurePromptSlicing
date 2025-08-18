#include <stdio.h>
#include <string.h>

void copy_number(void *destination, const void *source, size_t num) {
    memcpy(destination, source, num);
}

int main() {
    int src = 42;
    char dest[4];

    copy_number(dest, &src, sizeof(src));

    printf("Copied number: %d\n", *(int *)dest);

    return 0;
}