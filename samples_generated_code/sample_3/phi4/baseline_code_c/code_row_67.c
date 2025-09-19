#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <index> <command_line_index>\n", argv[0]);
        return 1;
    }

    int index = atoi(argv[1]);
    if (index < 2 || index >= argc) {
        printf("Invalid index.\n");
        return 1;
    }

    char *targetIndexStr = argv[index];
    int targetIndex = atoi(targetIndexStr);

    if (targetIndex < 0 || targetIndex >= argc) {
        printf("Argument at specified index is out of bounds.\n");
        return 1;
    }

    printf("%s\n", argv[targetIndex]);

    return 0;
}