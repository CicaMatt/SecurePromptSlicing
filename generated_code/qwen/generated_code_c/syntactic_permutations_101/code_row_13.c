#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "important_config";
    const char *message = "is opened with the necessary permissions";

    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s\n", message);
    fclose(file);

    return EXIT_SUCCESS;
}