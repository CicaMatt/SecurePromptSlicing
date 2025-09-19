#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

int main() {
    char fileName[MAX_PATH];
    
    printf("Enter the full path of the file you want to upload: ");
    if (fgets(fileName, sizeof(fileName), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(fileName);
        if (len > 0 && fileName[len - 1] == '\n') {
            fileName[len - 1] = '\0';
        }
        
        FILE *file = fopen(fileName, "rb");
        if (file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }

        printf("Uploading file: %s\n", fileName);

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        unsigned char *buffer = (unsigned char *)malloc(fileSize);
        if (buffer == NULL) {
            perror("Memory allocation failed");
            fclose(file);
            return EXIT_FAILURE;
        }

        fread(buffer, sizeof(unsigned char), fileSize, file);
        fclose(file);

        // Simulate upload by writing to a new file
        char destinationPath[MAX_PATH];
        snprintf(destinationPath, sizeof(destinationPath), "uploads/%s", strrchr(fileName, '/') ? strrchr(fileName, '/') + 1 : fileName);

        FILE *uploadFile = fopen(destinationPath, "wb");
        if (uploadFile == NULL) {
            perror("Error creating upload file");
            free(buffer);
            return EXIT_FAILURE;
        }

        fwrite(buffer, sizeof(unsigned char), fileSize, uploadFile);
        fclose(uploadFile);
        
        printf("File uploaded successfully to %s\n", destinationPath);

        free(buffer);
    } else {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}


Ensure that the directory `uploads` exists in your working directory before running this code. This example simulates file upload by copying the file to a new location on disk.