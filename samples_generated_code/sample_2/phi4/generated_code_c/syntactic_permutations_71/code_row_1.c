#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void handle_file_upload(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    fprintf(file, "%s", content);
    fclose(file);

    printf("File uploaded successfully: %s\n", filename);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    
    // Simulate receiving a file name and its content via HTTP request
    const char *filename = "uploaded_file.txt";
    const char *content = "This is the content of the uploaded file.";
    
    printf("Receiving file upload...\n");
    handle_file_upload(filename, content);

    return 0;
}