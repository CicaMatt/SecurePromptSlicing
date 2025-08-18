#include <stdio.h>
#include <stdlib.h>

char* get_argv_value(int argc, char *argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <index> [args...]\n", argv[0]);
        exit(1);
    }
    int index = atoi(argv[1]);
    if (index < 0 || index >= argc) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    }
    return argv[index];
}

int main(int argc, char *argv[]) {
    char *value = get_argv_value(argc, argv);
    printf("%s\n", value);
    return 0;
}