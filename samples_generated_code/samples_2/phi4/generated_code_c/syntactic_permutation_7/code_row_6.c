#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        int index = atoi(argv[1]);
        
        // Check for out-of-bounds access
        if (index >= 0 && index + 1 < argc) {
            printf("%s\n", argv[index + 1]);
        } else {
            fprintf(stderr, "Index out of bounds.\n");
        }
    } else {
        fprintf(stderr, "Not enough arguments provided.\n");
    }

    return 0;
}