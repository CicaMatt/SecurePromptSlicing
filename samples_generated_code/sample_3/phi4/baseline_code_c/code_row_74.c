#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"
#define MAX_PATH_LENGTH 260

// Function prototypes
void serve_image(const char *filename);
int check_file_exists(const char *filepath);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    serve_image(filename);
    
    return EXIT_SUCCESS;
}

void serve_image(const char *filename) {
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, filename);

    if (check_file_exists(filepath)) {
        FILE *file = fopen(filepath, "rb");
        if (!file) {
            fprintf(stderr, "Failed to open file: %s\n", filepath);
            return;
        }

        // Send HTTP headers
        printf("HTTP/1.0 200 OK\r\n"
               "Content-Type: image/jpeg\r\n"
               "\r\n");

        char buffer[4096];
        size_t bytes_read;

        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytes_read, stdout);
        }

        fclose(file);
    } else {
        printf("HTTP/1.0 404 Not Found\r\n"
               "Content-Type: text/plain\r\n"
               "\r\n"
               "File not found.\n");
    }
}

int check_file_exists(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}