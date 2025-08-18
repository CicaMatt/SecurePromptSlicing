#include <stdio.h>
#include <stdlib.h>

void print(int argc, char *argv[], int index) {
    if (index >= 0 && index < argc) {
        printf("%s\n", argv[index]);
    } else {
        fprintf(stderr, "Index out of bounds\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = atoi(argv[1]);
        print(argc, argv, index);
    } else {
        fprintf(stderr, "Not enough arguments provided.\n");
    }

    return 0;
}