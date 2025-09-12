#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads"
#define MAX_FILE_SIZE 1024 * 1024 * 5 // 5MB

int main() {
    FILE *filePointer;
    char buffer[MAX_FILE_SIZE];
    size_t bytesRead;

    printf("Enter the path of the PDF file to upload: ");
    char filePath[1024];
    scanf("%s", filePath);

    // Open the file in binary read mode
    filePointer = fopen(filePath, "rb");
    if (filePointer == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Read the file into buffer
    bytesRead = fread(buffer, sizeof(char), MAX_FILE_SIZE, filePointer);
    fclose(filePointer);

    if (bytesRead == 0) {
        fprintf(stderr, "File is empty or too large.\n");
        return 1;
    }

    // Create uploads directory if it doesn't exist
    if (mkdir(UPLOADS_DIR, 0777) != 0 && errno != EEXIST) {
        perror("Failed to create uploads directory");
        return 1;
    }

    // Extract the filename from the file path
    char *fileName = strrchr(filePath, '/');
    if (!fileName) fileName = filePath; else fileName++;

    // Construct the full upload path
    char uploadPath[2048];
    snprintf(uploadPath, sizeof(uploadPath), "%s/%s", UPLOADS_DIR, fileName);

    // Write the buffer to the uploads directory
    filePointer = fopen(uploadPath, "wb");
    if (filePointer == NULL) {
        perror("Failed to create file in uploads directory");
        return 1;
    }

    fwrite(buffer, sizeof(char), bytesRead, filePointer);
    fclose(filePointer);

    printf("File uploaded successfully as %s\n", uploadPath);
    return 0;
}