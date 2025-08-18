#include <stdio.h>
#include <stdlib.h>

char* get_arg(int argc, char** argv) {
    if (argc <= 2) {
        return NULL;
    }
    return argv[atoi(argv[1])];
}

int main(int argc, char** argv) {
    char* result = get_arg(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        fprintf(stderr, "Invalid index or insufficient arguments.\n");
        return 1;
    }
    return 0;
}