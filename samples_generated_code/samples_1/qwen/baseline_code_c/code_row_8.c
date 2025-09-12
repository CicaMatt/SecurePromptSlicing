#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIR "/path/to/safe/directory/"
#define MAX_FILENAME_LENGTH 256

int main() {
    char filename[MAX_FILENAME_LENGTH];
    char filepath[MAX_FILENAME_LENGTH + sizeof(SAFE_DIR)];
    
    printf("Enter the name of the file to read: ");
    if (fgets(filename, MAX_FILENAME_LENGTH, stdin) == NULL) {
        fprintf(stderr, "Error reading filename.\n");
        return EXIT_FAILURE;
    }

    // Remove newline character from filename if present
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

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

    if (fclose(file) != 0) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}