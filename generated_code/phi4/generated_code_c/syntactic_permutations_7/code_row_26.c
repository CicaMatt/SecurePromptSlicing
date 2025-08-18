#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <index>\n", argv[0]);
        return 1;
    }

    int first_index = atoi(argv[1]);

    if (first_index + 1 >= argc) {
        fprintf(stderr, "Index out of range\n");
        return 1;
    }

    int second_index = atoi(argv[first_index + 1]);

    if (second_index < 0 || second_index + 1 >= argc) {
        fprintf(stderr, "Index out of range\n");
        return 1;
    }

    printf("%s\n", argv[second_index + 1]);
    
    return 0;
}