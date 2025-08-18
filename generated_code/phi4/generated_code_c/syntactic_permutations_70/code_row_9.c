#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int upload_file(const char *filename, const char *destination) {
    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return -1;
    }

    FILE *dest = fopen(destination, "wb");
    if (!dest) {
        perror("Failed to open destination file");
        fclose(source);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    if (ferror(source) || ferror(dest)) {
        perror("Error during file copy");
        fclose(source);
        fclose(dest);
        return -1;
    }

    fclose(source);
    fclose(dest);
    printf("File uploaded successfully.\n");
    return 0;
}

int main() {
    char sourceFilename[256];
    char destinationPath[] = "./uploads/";

    printf("Enter the path of the file to upload: ");
    if (fgets(sourceFilename, sizeof(sourceFilename), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(sourceFilename);
        if (len > 0 && sourceFilename[len - 1] == '\n') {
            sourceFilename[--len] = '\0';
        }

        char destinationFilename[256];
        snprintf(destinationFilename, sizeof(destinationFilename), "%s%s", destinationPath, strrchr(sourceFilename, '/') ? strrchr(sourceFilename, '/') + 1 : sourceFilename);

        if (upload_file(sourceFilename, destinationFilename) != 0) {
            fprintf(stderr, "Failed to upload file.\n");
        }
    } else {
        perror("Failed to read input");
    }

    return 0;
}