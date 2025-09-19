#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIRECTORY "./safe/"
#define MAX_FILENAME_LENGTH 100

int main() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from filename if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
    }

    char full_path[MAX_FILENAME_LENGTH + sizeof(SAFE_DIRECTORY)];
    snprintf(full_path, sizeof(full_path), "%s%s", SAFE_DIRECTORY, filename);

    FILE *file = fopen(full_path, "r");
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