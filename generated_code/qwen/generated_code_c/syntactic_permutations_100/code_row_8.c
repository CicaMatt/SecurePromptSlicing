#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "example.txt";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return 0;
}