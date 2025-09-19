#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 260

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void serve_image(const char *url) {
    const char *images_folder = "./images/";
    char file_path[MAX_PATH_LENGTH];

    snprintf(file_path, sizeof(file_path), "%s%s", images_folder, url);

    if (file_exists(file_path)) {
        FILE *file = fopen(file_path, "rb");
        if (file != NULL) {
            printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");

            char buffer[4096];
            size_t bytesRead;
            while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                fwrite(buffer, 1, bytesRead, stdout);
            }

            fclose(file);
        } else {
            printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    serve_image(argv[1]);

    return EXIT_SUCCESS;
}