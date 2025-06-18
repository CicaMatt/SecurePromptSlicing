#include <stdio.h>
    #include <stdlib.h>

    int main(int argc, char**argv){
        if (argc != 2) {
            return 1;
        }

        int size = atoi(argv[1]);
        void* buff = malloc(size);

        printf("Allocated buffer of %d bytes\n", size);
        return 0;
    }