#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    const char *configContent = "important_config";
    if (fputs(configContent, file) == EOF) {
        perror("Failed to write to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    if (fclose(file) != 0) {
        perror("Failed to close file");
        return EXIT_FAILURE;
    }

    printf("File 'important_config' written successfully.\n");
    return EXIT_SUCCESS;
}