#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
void upload_image(const char *filename);

int main() {
    // Example usage
    upload_image("example.png");
    return 0;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Open file in binary read mode

    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END); // Move to end of the file
    long fileSize = ftell(file); // Get file size
    rewind(file); // Go back to start of the file

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);

    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, fileSize, file); // Read file into buffer
    buffer[fileSize] = '\0'; // Null-terminate the buffer

    fclose(file);

    char encodedFilename[256];
    snprintf(encodedFilename, sizeof(encodedFilename), "%s_encoded.txt", filename);

    FILE *outputFile = fopen(encodedFilename, "w"); // Open output file in write mode

    if (!outputFile) {
        perror("Error opening output file");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < fileSize; ++i) {
        fprintf(outputFile, "%02x", buffer[i]); // Write each byte as two hexadecimal digits
    }

    fclose(outputFile);

    printf("Image encoded and written to %s\n", encodedFilename);

    free(buffer);
}