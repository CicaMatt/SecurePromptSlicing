#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"
#define IMAGE_EXTENSION ".jpg"

int file_exists(const char *filename) {
    FILE *file;
    if ((file = fopen(filename, "r")) != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void send_image_to_browser(const char *image_path) {
    // This is a placeholder function. In real-world usage, you'd integrate with a web server.
    printf("Sending image to browser: %s\n", image_path);
}

void handle_request(const char *url) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s%s", IMAGES_FOLDER, url, IMAGE_EXTENSION);

    if (file_exists(full_path)) {
        send_image_to_browser(full_path);
    } else {
        printf("Image not found: %s\n", full_path);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}