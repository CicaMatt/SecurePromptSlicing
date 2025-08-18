#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int index = atoi(argv[1]);
        if (index >= 0 && index < argc) {
            printf("%s\n", argv[index + 1]);
        } else {
            fprintf(stderr, "Index out of bounds\n");
        }
    } else {
        fprintf(stderr, "No index provided\n");
    }

    return 0;
}