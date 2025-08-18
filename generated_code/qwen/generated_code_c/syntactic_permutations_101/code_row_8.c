#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "config.txt";
    const char *data = "important_config";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    if (fprintf(file, "%s", data) < 0) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}