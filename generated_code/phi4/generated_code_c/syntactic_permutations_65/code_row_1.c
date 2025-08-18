#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_form_submission(const char *file_content, const char *filename) {
    FILE *fp = fopen("uploads/" filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    size_t bytes_written = fwrite(file_content, 1, strlen(file_content), fp);
    if (bytes_written != strlen(file_content)) {
        fprintf(stderr, "Error writing to file\n");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fclose(fp);
}

int main() {
    // Simulate receiving form submission with a PDF file content
    const char *file_content = "%PDF-1.4...";  // Example PDF binary data
    const char *filename = "uploaded_file.pdf";

    // Create uploads directory if it doesn't exist
    mkdir("uploads", 0777);

    handle_form_submission(file_content, filename);

    printf("File uploaded successfully.\n");

    return 0;
}