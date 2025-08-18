#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

void handle_file_upload() {
    char filename[MAX_FILENAME_LENGTH];
    FILE *file;
    
    // Get filename from user (or request, in a web context)
    printf("Enter the filename to upload: ");
    scanf("%s", filename);

    // Open file for reading
    file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Determine file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory to contain the file content
    char *file_content = malloc(file_size + 1);
    if (!file_content) {
        fclose(file);
        fprintf(stderr, "Memory allocation error\n");
        return;
    }

    // Read file content into buffer
    fread(file_content, file_size, 1, file);
    fclose(file);

    // Simulate saving the file to a server (e.g., writing to another location)
    char new_filename[MAX_FILENAME_LENGTH];
    snprintf(new_filename, sizeof(new_filename), "server/%s", filename);
    FILE *new_file = fopen(new_filename, "wb");
    if (!new_file) {
        free(file_content);
        perror("Error saving file to server");
        return;
    }
    fwrite(file_content, file_size, 1, new_file);
    fclose(new_file);

    // Free allocated memory
    free(file_content);

    printf("File uploaded successfully.\n");
}

int main() {
    handle_file_upload();
    return 0;
}