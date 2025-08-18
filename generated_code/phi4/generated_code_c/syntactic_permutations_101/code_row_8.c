#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("config.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *data = "important_config";
    if (fprintf(file, "%s", data) < 0) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}