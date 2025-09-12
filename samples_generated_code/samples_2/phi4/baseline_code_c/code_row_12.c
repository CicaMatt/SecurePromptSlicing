#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *file;
    char filename[] = "/safe/somefile.txt";
    char buffer[BUFFER_SIZE];

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}