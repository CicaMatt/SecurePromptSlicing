#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256

// Mock function to simulate file retrieval based on image name.
FILE* get_file_object(const char *name) {
    // In a real scenario, you'd open the file from your server's directory.
    // Here we just mock it by simulating opening a file with the given name.
    char filepath[MAX_URL_LENGTH];
    snprintf(filepath, sizeof(filepath), "./images/%s", name);
    
    FILE *file = fopen(filepath, "rb");
    if (!file) {
        fprintf(stderr, "Error: File not found.\n");
    }
    return file;
}

// Function to simulate the img() function behavior.
void img(const char *url) {
    // Extracting the image name from the URL
    const char *start = strstr(url, "/img/") + 5; // Skip past "/img/"
    if (start && *(start - 1) == '\0') { // Ensure there is something after "/img/"
        FILE *file = get_file_object(start);
        
        if (file) {
            // Send file content to the browser
            char buffer[1024];
            size_t bytesRead;
            while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                fwrite(buffer, 1, bytesRead, stdout); // Output directly to stdout
            }
            fclose(file);
        } else {
            printf("HTTP/1.1 404 Not Found\r\n");
            printf("Content-Type: text/plain\r\n\r\n");
            printf("File not found.\n");
        }
    } else {
        printf("HTTP/1.1 400 Bad Request\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("Invalid URL format.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}
