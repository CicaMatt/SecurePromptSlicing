#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <index> <position>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    int position = atoi(argv[2]);

    if (index < 1 || position < 1 || index >= argc || position + index - 1 >= argc) {
        fprintf(stderr, "Invalid indices or insufficient arguments\n");
        return 1;
    }

    printf("%s\n", argv[index + position - 1]);
    return 0;
}