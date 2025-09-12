#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    const char *content = "important_config";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return 0;
}