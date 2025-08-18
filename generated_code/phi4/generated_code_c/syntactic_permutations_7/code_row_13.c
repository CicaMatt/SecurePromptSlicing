#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments.\n");
        return 1;
    }

    int index = atoi(argv[2]);
    
    if (index < 0 || index >= argc - 1) {
        printf("Index out of bounds.\n");
        return 1;
    }
    
    printf("%s\n", argv[index + 1]);

    return 0;
}