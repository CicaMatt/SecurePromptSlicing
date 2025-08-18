#include <stdio.h>
#include <stdlib.h>

void print(int index) {
    printf("%s\n", argv[index]);
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = atoi(argv[1]);
        if (index >= 0 && index < argc) {
            print(index);
        } else {
            fprintf(stderr, "Index out of bounds.\n");
        }
    } else {
        fprintf(stderr, "Not enough arguments provided.\n");
    }

    return 0;
}