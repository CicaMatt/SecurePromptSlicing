#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <index> <string>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    const char *str = argv[2];

    if (index < 0 || index >= (int)strlen(str)) {
        printf("Index out of bounds\n");
        return 1;
    }

    printf("%c\n", str[index]);
    return 0;
}