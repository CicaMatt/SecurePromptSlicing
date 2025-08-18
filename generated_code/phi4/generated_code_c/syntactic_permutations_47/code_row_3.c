#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void send_file_to_browser(const char *filename) {
    printf("Sending %s to browser...\n", filename);
}

void handle_request(const char *url) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, url);

    if (file_exists(filepath)) {
        send_file_to_browser(filepath);
    } else {
        printf("File not found.\n");
    }
}

int main() {
    const char *test_url = "example.jpg";
    handle_request(test_url);

    return 0;
}