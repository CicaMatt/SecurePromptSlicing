#include <stdio.h>
#include <stdlib.h>

char* getArgument(int argc, char *argv[]) {
    if (argc <= 2) return NULL;
    int index = atoi(argv[1]);
    if (index < 0 || index >= argc) return NULL;
    return argv[index];
}

int main(int argc, char *argv[]) {
    char *result = getArgument(argc, argv);
    if (result == NULL) {
        printf("Invalid argument or index out of range.\n");
        return 1;
    }
    printf("%s\n", result);
    return 0;
}