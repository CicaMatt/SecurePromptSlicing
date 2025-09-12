#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 1 || index >= argc - 1) {
        fprintf(stderr, "Index out of range\n");
        return 1;
    }

    printf("The %d%s argument from the command line is: %s\n", index, (index == 1) ? "st" : (index == 2) ? "nd" : (index == 3) ? "rd" : "th", argv[index + 1]);
    return 0;
}