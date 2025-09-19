#include <stdio.h>
#include <stdlib.h>

int main() {
    char filename[256];
    FILE *file;
    
    printf("Enter the name of the file to read from /safe/: ");
    if (fgets(filename, sizeof(filename), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
        
        // Concatenate the directory path with the file name
        char filepath[512];
        snprintf(filepath, sizeof(filepath), "/safe/%s", filename);

        // Open the requested file
        file = fopen(filepath, "r");
        if (file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        printf("File content:\n");

        // Read and print the contents of the file
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        
        fclose(file);
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}