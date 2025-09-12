#include <stdio.h>
#include <stdlib.h>

char* getArgument(int argc, char *argv[]) {
    if (argc <= 2) {
        return NULL;
    }
    int index = atoi(argv[1]);
    if (index >= argc || index < 0) {
        return NULL;
    }
    return argv[index];
}

int main(int argc, char *argv[]) {
    char* result = getArgument(argc, argv);
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("Invalid index or not enough arguments.\n");
    }
    return 0;
}