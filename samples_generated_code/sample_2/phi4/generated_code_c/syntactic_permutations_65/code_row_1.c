#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for the request
#define SERVER "localhost"
#define PORT "8000"  // Replace with your server port if different
#define UPLOAD_PATH "/path/to/upload/folder/uploads/"  // Path where files should be saved

// Function to handle file upload (simulate HTTP POST request)
void upload_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Allocate memory for the file content
    char *buffer = (char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    // Close the file after reading
    fclose(file);

    printf("Uploading %s to server...\n", filename);

    // Simulate HTTP POST request (details like headers and exact implementation are abstracted)
    char command[1024];
    snprintf(command, sizeof(command), "curl -X POST http://%s:%s/upload --data-binary @%s",
             SERVER, PORT, filename);
    
    int result = system(command);

    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    free(buffer);
}

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];

    // Ensure file exists and is a PDF
    FILE *file = fopen(filename, "rb");
    if (!file || strcmp(fgetc(file), '%') != 0) {  // Check for PDF header '%'
        fprintf(stderr, "Error: File does not exist or is not a PDF.\n");
        return EXIT_FAILURE;
    }
    fclose(file);

    upload_file(filename);

    return EXIT_SUCCESS;
}
