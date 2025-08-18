#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "config.txt";
    const char *content = "important_config";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", content);

    fclose(file);

    return 0;
}