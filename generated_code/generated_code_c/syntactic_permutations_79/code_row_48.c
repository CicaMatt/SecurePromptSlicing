#include <stdlib.h>
#include <stdio.h>

void* method_allocate(size_t size, void** buffer) {
    *buffer = malloc(size);

    if (!*buffer) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

int main() {
    char buf[1024];
    method_allocate(sizeof(buf), (void**)&buf);

    char buf1[1024];
    method_allocate(sizeof(buf1), (void**)&buf1);

    return 0;
}