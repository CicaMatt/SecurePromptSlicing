#include <stdlib.h>
    #include <string.h>

    void copy_chunks(char* src, int size) {
        char *dst = (char*)malloc(size);
        strncpy(dst, src, size);
        free(src);
        free(dst);
    }