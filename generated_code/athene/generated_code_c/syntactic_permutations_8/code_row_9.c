#include <stdio.h>
#include <stdlib.h>

char* getArgValue(int argc, char *argv[]) {
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
    char* value = getArgValue(argc, argv);
    if (value != NULL) {
        printf("%s\n", value);
    } else {
        printf("Invalid index or arguments.\n");
    }
    return 0;
}