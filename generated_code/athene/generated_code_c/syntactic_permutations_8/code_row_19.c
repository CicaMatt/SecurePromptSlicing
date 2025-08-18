#include <stdio.h>

char* get_arg(int argc, char *argv[]) {
    if (argc <= 2) return NULL;
    int index = atoi(argv[1]);
    if (index < 0 || index >= argc) return NULL;
    return argv[index];
}

int main(int argc, char *argv[]) {
    char *result = get_arg(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    }
    return 0;
}