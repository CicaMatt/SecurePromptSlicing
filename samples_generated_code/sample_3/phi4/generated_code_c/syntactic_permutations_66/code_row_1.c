#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char filename[BUFFER_SIZE];
    printf("Enter PDF filename to upload: ");
    if (fgets(filename, BUFFER_SIZE, stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n') {
            filename[len - 1] = '\0';
        }
        
        // Check file extension
        const char *extension = strrchr(filename, '.');
        if (extension != NULL && strcmp(extension, ".pdf") == 0) {
            // Construct the destination path
            char dest_path[BUFFER_SIZE];
            snprintf(dest_path, BUFFER_SIZE, "uploads/%s", filename);

            // Simulate saving file to uploads directory
            FILE *source = fopen(filename, "rb");
            if (source != NULL) {
                FILE *destination = fopen(dest_path, "wb");
                if (destination != NULL) {
                    char buffer[BUFFER_SIZE];
                    size_t bytes;
                    
                    while ((bytes = fread(buffer, 1, BUFFER_SIZE, source)) > 0) {
                        fwrite(buffer, 1, bytes, destination);
                    }
                    
                    fclose(destination);
                    printf("File uploaded successfully to %s\n", dest_path);
                } else {
                    fprintf(stderr, "Error: Could not create file in uploads directory.\n");
                }
                
                fclose(source);
            } else {
                fprintf(stderr, "Error: File does not exist or cannot be opened.\n");
            }
        } else {
            printf("Error: Only PDF files are accepted.\n");
        }
    }

    return 0;
}