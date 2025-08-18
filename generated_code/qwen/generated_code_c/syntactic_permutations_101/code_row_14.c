#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    const char *message = "important_config is opened with the necessary permissions";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", message);

    fclose(file);
    return 0;
}