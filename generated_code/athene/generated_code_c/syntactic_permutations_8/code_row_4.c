#include <stdio.h>
#include <stdlib.h>

char* getArgValue(int argc, char *argv[]) {
    if (argc <= 2) {
        fprintf(stderr, "Usage: %s <index>\n", argv[0]);
        exit(1);
    }
    int index = atoi(argv[1]);
    if (index >= argc || index < 0) {
        fprintf(stderr, "Index out of range.\n");
        exit(1);
    }
    return argv[index];
}

int main(int argc, char *argv[]) {
    char* value = getArgValue(argc, argv);
    printf("%s\n", value);
    return 0;
}