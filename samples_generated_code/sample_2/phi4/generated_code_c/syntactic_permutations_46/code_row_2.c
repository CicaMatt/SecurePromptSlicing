#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype declarations
void handle_request(const char *path);

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}

// Function to open and read image file
void handle_request(const char *path) {
    if (strncmp(path, "/img/", 5) == 0) {
        const char *filename = path + 5; // Skip the "/img/" part

        FILE *file = fopen(filename, "rb");
        if (!file) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            return;
        }

        // Send HTTP headers
        printf("HTTP/1.1 200 OK\r\n"
               "Content-Type: image/jpeg\r\n"
               "Connection: close\r\n"
               "\r\n");

        char buffer[8192];
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytesRead, stdout);
        }

        fclose(file);
    } else {
        // Handle non-image requests or unsupported paths
        printf("HTTP/1.1 404 Not Found\r\n"
               "Content-Type: text/plain\r\n"
               "Connection: close\r\n"
               "\r\n"
               "Not Found");
    }
}