#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    const char *text_to_write = "This is an important configuration.\n";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    if (fprintf(file, "%s", text_to_write) < 0) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}