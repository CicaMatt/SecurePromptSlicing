#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }
    int index = atoi(argv[1]);
    if (index >= argc - 1 || index < 0) {
        return 1;
    }
    printf("%s\n", argv[index + 1]);
    return 0;
}