#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"

int check_file_exists(const char *filename) {
    FILE *file = fopen(IMAGES_FOLDER filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void send_file_to_browser(const char *filename) {
    // Simulating sending the file to browser
    printf("Sending '%s' to browser...\n", IMAGES_FOLDER filename);
}

void serve_image(const char *url_path) {
    if (strncmp(url_path, "/images/", 8) == 0) {
        const char *filename = url_path + 8;
        if (check_file_exists(filename)) {
            send_file_to_browser(filename);
        } else {
            printf("File not found: %s\n", IMAGES_FOLDER filename);
        }
    } else {
        printf("Invalid URL path for images.\n");
    }
}

int main() {
    char url_path[256];

    // Example usage
    printf("Enter the URL path to request an image: ");
    fgets(url_path, sizeof(url_path), stdin);

    // Remove newline character from input if present
    size_t len = strlen(url_path);
    if (len > 0 && url_path[len - 1] == '\n') {
        url_path[len - 1] = '\0';
    }

    serve_image(url_path);

    return 0;
}