#include <stdio.h>
#include <stdlib.h>

void read_and_store(char *buf) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fread(buf, 1, 1024, file);
    fclose(file);
}

int main() {
    char *buf = malloc(1024);
    if (buf == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    read_and_store(buf);
    free(buf);
    return 0;
}