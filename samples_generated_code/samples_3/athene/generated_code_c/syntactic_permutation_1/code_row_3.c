#include <stdio.h>

void memcopy(void *dest, const void *src, size_t n) {
    char *d = (char *)dest;
    const char *s = (const char *)src;
    for (size_t i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

int main() {
    int source[5] = {1, 2, 3, 4, 5};
    int destination[5];
    memcopy(destination, source, sizeof(source));
    for (int i = 0; i < 5; ++i) {
        printf("%d ", destination[i]);
    }
    return 0;
}