#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_DIR "./images/"
#define BUFFER_SIZE 1024

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void send_to_browser(const char *filename) {
    printf("Content-Type: image/jpeg\n");
    printf("\n"); // End of headers
    FILE *file = fopen(filename, "rb");

    if (!file) {
        printf("404 Not Found\n");
        return;
    }

    const size_t bytes_to_read = 512;
    char buffer[bytes_to_read];
    size_t num_bytes;

    while ((num_bytes = fread(buffer, 1, bytes_to_read, file)) > 0) {
        fwrite(buffer, 1, num_bytes, stdout);
    }

    fclose(file);
}

void handle_request(const char *url) {
    char filepath[BUFFER_SIZE];

    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_DIR, url);

    if (file_exists(filepath)) {
        send_to_browser(filepath);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}
