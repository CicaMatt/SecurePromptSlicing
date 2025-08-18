#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s index\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (index < 1 || index >= argc) {
        fprintf(stderr, "Error: Index out of range. Please provide a valid index.\n");
        return 1;
    }

    printf("The %d%s argument from the command line arguments is: %s\n", 
           index, 
           (index == 1 ? "" : "nd"), 
           argv[index]);

    return 0;
}