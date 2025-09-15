#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER "http://localhost:8000/upload"
#define UPLOAD_PATH "./uploads"

int main() {
    // Simulating HTML form for file upload
    printf("Content-Type: text/html\n\n");
    printf("<html><body>");
    printf("<form action='%s' method='POST' enctype='multipart/form-data'>", SERVER);
    printf("Select PDF to upload:<br>");
    printf("<input type='file' name='pdfFile' accept='.pdf'><br>");
    printf("<input type='submit' value='Upload PDF'>");
    printf("</form></body></html>");

    // Simulating server-side handling of uploaded file
    char buffer[1024];
    ssize_t bytes_read;

    // Assume the POST data is received here as binary input (simplified for demonstration)
    FILE *uploaded_file = fopen("received.pdf", "wb");  // Temporary file to simulate upload

    if (!uploaded_file) {
        perror("Failed to open temporary file");
        return EXIT_FAILURE;
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        fwrite(buffer, 1, bytes_read, uploaded_file);
    }
    
    fclose(uploaded_file);

    // Move the file from temporary location to uploads folder
    char target_path[256];
    snprintf(target_path, sizeof(target_path), "%s/uploaded.pdf", UPLOAD_PATH);

    if (rename("received.pdf", target_path) != 0) {
        perror("Failed to move uploaded file");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully to %s\n", target_path);
    
    return EXIT_SUCCESS;
}
