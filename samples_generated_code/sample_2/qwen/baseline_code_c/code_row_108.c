#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filename[256];
    char filepath[256] = "/safe/";
    FILE *file;

    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from filename if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
    }

    strcat(filepath, filename);

    file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    fclose(file);
    return EXIT_SUCCESS;
}