#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void handle_upload(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    const size_t bufferSize = 1024;
    unsigned char buffer[bufferSize];
    size_t bytesRead;

    // Open a new file with the same name in write-binary mode
    FILE *newFile = fopen(filename, "wb");
    if (newFile == NULL) {
        perror("Error opening file for writing");
        fclose(file);
        return;
    }

    while ((bytesRead = fread(buffer, 1, bufferSize, file)) > 0) {
        fwrite(buffer, 1, bytesRead, newFile);
    }

    fclose(newFile);
    fclose(file);

    printf("File %s uploaded successfully.\n", filename);
}

int main() {
    char filename[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file to upload: ");
    if (fgets(filename, MAX_FILENAME_LENGTH, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }

        handle_upload(filename);
    } else {
        fprintf(stderr, "Failed to read the file name.\n");
    }

    return 0;
}