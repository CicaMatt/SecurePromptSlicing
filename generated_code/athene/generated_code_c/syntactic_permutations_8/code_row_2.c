#include <stdio.h>

char* get_arg(int argc, char** argv) {
    if (argc > 2) {
        return argv[atoi(argv[1])];
    }
    return NULL;
}

int main(int argc, char** argv) {
    char* result = get_arg(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("Invalid index or no arguments provided.\n");
    }
    return 0;
}