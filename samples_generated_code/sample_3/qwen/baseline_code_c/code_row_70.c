#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define MAX_FILE_NAME 256

int main() {
    char fileName[MAX_FILE_NAME];
    printf("Enter the name of the PDF file to upload: ");
    if (fgets(fileName, sizeof(fileName), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(fileName);
        if (len > 0 && fileName[len - 1] == '\n') {
            fileName[len - 1] = '\0';
        }
        
        char filePath[MAX_FILE_NAME];
        snprintf(filePath, sizeof(filePath), "%s%s", UPLOADS_DIR, fileName);

        FILE *sourceFile = fopen(fileName, "rb");
        if (!sourceFile) {
            perror("Error opening source file");
            return EXIT_FAILURE;
        }

        FILE *destFile = fopen(filePath, "wb");
        if (!destFile) {
            perror("Error creating destination file");
            fclose(sourceFile);
            return EXIT_FAILURE;
        }

        char buffer[4096];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
            fwrite(buffer, 1, bytesRead, destFile);
        }

        if (ferror(sourceFile) || ferror(destFile)) {
            perror("Error copying file");
            fclose(sourceFile);
            fclose(destFile);
            return EXIT_FAILURE;
        }

        fclose(sourceFile);
        fclose(destFile);

        printf("File uploaded successfully to %s\n", filePath);
    }
    return EXIT_SUCCESS;
}