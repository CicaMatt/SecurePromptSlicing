#include <stdio.h>
#include <stdlib.h>

#define SAFE_DIR "/safe/"

int main() {
    char filename[256];
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from input if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        char filepath[260];
        snprintf(filepath, sizeof(filepath), "%s%s", SAFE_DIR, filename);

        FILE *file = fopen(filepath, "r");
        if (file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
        
        printf("Reading file: %s\n", filepath);
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }

        fclose(file);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}