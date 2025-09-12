#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> <value>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);

    if (argc <= index + 1 || index < 0) {
        printf("Invalid index.\n");
        return 1;
    }

    printf("%s\n", argv[index + 1]);
    return 0;
}