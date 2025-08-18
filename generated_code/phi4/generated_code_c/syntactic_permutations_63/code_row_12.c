#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    FILE *file;
    char filename[100];
    char buffer[BUFFER_SIZE];
    long fileSize = 0;

    printf("Enter the file name: ");
    scanf("%99s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read contents into buffer
    while (!feof(file)) {
        size_t bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE - 1, file);
        fileSize += bytesRead;

        // Process the buffer if needed
        for (size_t i = 0; i < bytesRead; ++i) {
            // Example: Print each character
            putchar(buffer[i]);
        }
    }

    fclose(file);

    printf("\nFile size in bytes: %ld\n", fileSize);
    
    return EXIT_SUCCESS;
}