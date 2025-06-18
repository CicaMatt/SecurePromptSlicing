#include <stdio.h>

    int main(int argc, char **argv) {
        if (argc < 2) {
            printf("Usage: %s index\n", *argv);
            return 1;
        }
    
        int index = atoi(*++argv);
        if (index >= argc) {
            printf("Index out of bounds!\n");
            return 1;
        }
    
        printf("%s\n", *++argv);
    }