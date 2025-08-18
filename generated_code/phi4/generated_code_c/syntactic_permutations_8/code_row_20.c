#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <array> <index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[2]);

    for (int i = 1; argv[i] != NULL && i <= index; ++i) {
        if (i == index) {
            printf("%s\n", argv[i]);
        }
    }

    if (argv[index + 1] == NULL || index < 0) {
        fprintf(stderr, "Index out of range.\n");
        return 1;
    }

    return 0;
}