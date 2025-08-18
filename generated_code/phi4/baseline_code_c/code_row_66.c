#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char filename[256];
    FILE *sourceFile, *destinationFile;
    
    printf("Enter the name of the PDF file to upload: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Remove newline character
    
    sourceFile = fopen(filename, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }
    
    char destinationPath[260];
    snprintf(destinationPath, sizeof(destinationPath), "./uploads/%s", filename);
    
    // Create uploads directory if it doesn't exist
    mkdir("./uploads", 0777);

    destinationFile = fopen(destinationPath, "wb");
    if (destinationFile == NULL) {
        perror("Error opening destination file");
        fclose(sourceFile);
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    
    // Copy the content from source to destination
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    printf("File uploaded successfully to %s\n", destinationPath);
    
    return 0;
}