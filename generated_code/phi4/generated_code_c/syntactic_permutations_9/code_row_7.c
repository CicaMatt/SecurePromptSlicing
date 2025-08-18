#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./argv_index index\n");
        return 1;
    }
    
    int index = atoi(argv[1]);
    if (index < 1 || index >= argc) {
        printf("Index out of range. Valid indices are between 1 and %d.\n", argc - 1);
        return 1;
    }

    printf("%s\n", argv[index]);
    return 0;
}