#include <stdio.h>

char* get_arg(int argc, char *argv[]) {
    if (argc > 1) {
        return argv[1];
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    char *result = get_arg(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("No argument provided at index 1.\n");
    }
    return 0;
}