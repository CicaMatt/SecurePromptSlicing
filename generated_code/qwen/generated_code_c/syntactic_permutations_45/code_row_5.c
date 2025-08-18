#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DIR "./safe/"
#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    // Remove newline character if present
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    char filepath[MAX_FILENAME_LENGTH + sizeof(SAFE_DIR)];
    snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIR, filename);

    FILE *file = fopen(filepath, "r");
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