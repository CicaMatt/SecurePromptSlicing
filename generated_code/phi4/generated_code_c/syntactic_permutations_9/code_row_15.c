#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Error: Not enough arguments.\n");
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 0 || index >= argc - 1) {
        printf("Error: Index out of range.\n");
        return 1;
    }

    printf("%s\n", argv[index + 1]);
    return 0;
}