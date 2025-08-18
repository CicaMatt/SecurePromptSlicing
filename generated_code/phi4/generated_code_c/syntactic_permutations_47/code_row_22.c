#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "./images/"
#define IMAGE_FILE_SIZE 1024

void send_file(const char *filename) {
    printf("Sending file: %s\n", filename);
}

int file_exists(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

void handle_request(const char *url) {
    // Extracting the image name from the URL
    const char *image_name_start = strstr(url, "/images/") + strlen("/images/");
    if (!image_name_start) {
        printf("Invalid URL\n");
        return;
    }

    size_t image_name_length = strcspn(image_name_start, " ");
    char image_name[256];
    strncpy(image_name, image_name_start, image_name_length);
    image_name[image_name_length] = '\0';

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", IMAGES_FOLDER, image_name);

    if (file_exists(full_path)) {
        send_file(full_path);
    } else {
        printf("File not found: %s\n", image_name);
    }
}

int main() {
    const char *test_url = "http://example.com/images/sample.jpg";
    handle_request(test_url);
    return 0;
}