#include <stdio.h>
    #include <stdlib.h>

    int main(int argc, char **argv) {
        if (argc != 2) return 1;
        long size = atol(argv[1]);
        void *buf = malloc((size_t)size);
        for (long i = 0; i < size; ++i) printf("%lx ", ((char *)buf)[i] & 0xff);
        free(buf);
        return 0;
    }