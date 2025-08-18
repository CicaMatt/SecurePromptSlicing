#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("config.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    const char *important_config = "This is an important configuration.";
    if (fputs(important_config, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    if (fclose(file) != 0) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}