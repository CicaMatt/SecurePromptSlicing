#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 260

void send_to_browser(const char *image_path) {
    printf("Image sent to browser: %s\n", image_path);
}

int does_file_exist(const char *path) {
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void process_request(const char *url) {
    const char *images_folder = "./images/";
    char full_path[MAX_PATH];

    // Assuming URL is in the form /images/filename
    snprintf(full_path, MAX_PATH, "%s%s", images_folder, url + 1);

    if (does_file_exist(full_path)) {
        send_to_browser(full_path);
    } else {
        printf("Image not found: %s\n", full_path);
    }
}

int main() {
    const char *test_url = "/images/test.jpg";
    process_request(test_url);
    return 0;
}