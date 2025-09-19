#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[] = "/safe/file.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    fclose(file);
    return EXIT_SUCCESS;
}