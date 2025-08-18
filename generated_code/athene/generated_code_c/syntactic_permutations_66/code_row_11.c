#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Content-type: text/html\n\n");
    printf("<html><body>");
    
    char *filename = NULL;
    size_t n = 0;
    ssize_t read;

    // Read filename from POST request
    printf("<h1>File Upload</h1>");
    if (getline(&filename, &n, stdin) > 0) {
        filename[strcspn(filename, "\r\n")] = '\0'; // Remove newline

        // Check file extension
        char *extension = strrchr(filename, '.');
        if (extension && !strcmp(extension, ".pdf")) {
            printf("<p>PDF File received: %s</p>", filename);
            // Process the PDF file here
        } else {
            printf("<p>Error: Only PDF files are accepted.</p>");
        }
    } else {
        printf("<p>No file uploaded.</p>");
    }

    free(filename);
    printf("</body></html>");
    return 0;
}