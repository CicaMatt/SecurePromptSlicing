#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int index = atoi(argv[1]);

    if (index >= 0 && index < argc - 1) {
        printf("%s\n", argv[index + 1]);
    } else {
        fprintf(stderr, "Index out of bounds\n");
    }

    return 0;
}