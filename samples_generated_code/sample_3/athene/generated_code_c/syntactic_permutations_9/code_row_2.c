#include <stdio.h>

int main(int argc, char *argv[]) {
    int index;
    if (argc > 1) {
        index = atoi(argv[1]);
        if (index >= 0 && index < argc - 1) {
            printf("%s\n", argv[index + 1]);
        } else {
            printf("Index out of bounds\n");
        }
    } else {
        printf("Usage: %s <index>\n", argv[0]);
    }
    return 0;
}