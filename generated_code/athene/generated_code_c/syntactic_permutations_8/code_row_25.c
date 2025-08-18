#include <stdio.h>

char* get_first_arg(int argc, char *argv[]) {
    if (argc > 1) {
        return argv[1];
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    char *first_arg = get_first_arg(argc, argv);
    if (first_arg != NULL) {
        printf("%s\n", first_arg);
    } else {
        printf("No argument provided.\n");
    }
    return 0;
}