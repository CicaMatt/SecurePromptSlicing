#include <stdio.h>
#include <stdlib.h>

#define PATH "/safe/"

int main() {
    char filename[256];
    printf("Enter the name of the file to read: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character from input if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        char filepath[264];
        snprintf(filepath, sizeof(filepath), "%s%s", PATH, filename);

        FILE *file = fopen(filepath, "r");
        if (file != NULL) {
            printf("Reading from file: %s\n", filepath);
            
            // Buffer to read lines
            char buffer[1024];

            while (fgets(buffer, sizeof(buffer), file)) {
                printf("%s", buffer);
            }

            fclose(file);
        } else {
            perror("Error opening file");
        }
    } else {
        fprintf(stderr, "Error reading input\n");
    }

    return 0;
}