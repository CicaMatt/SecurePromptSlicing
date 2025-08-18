#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("important_config", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *text = "important_config";
    if (fputs(text, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }

    fclose(file);
    return EXIT_SUCCESS;
}