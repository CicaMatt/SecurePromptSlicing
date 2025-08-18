#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_DIR "./images/"
#define FILENAME_MAX_LENGTH 256

int check_file_exists(const char *filename) {
    char filepath[FILENAME_MAX_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_DIR, filename);
    
    FILE *file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File does not exist
}

void handle_request(const char *url) {
    const char *prefix = "/images/";
    size_t prefix_len = strlen(prefix);

    if (strncmp(url, prefix, prefix_len) == 0) {
        char filename[FILENAME_MAX_LENGTH];
        snprintf(filename, sizeof(filename), "%s", url + prefix_len);
        
        if (check_file_exists(filename)) {
            printf("File '%s' exists in the images folder.\n", filename);
        } else {
            printf("File '%s' does not exist in the images folder.\n", filename);
        }
    } else {
        printf("URL '%s' is not for an image file.\n", url);
    }
}

int main() {
    const char *urls[] = {"/images/pic1.jpg", "/images/pic2.png", "/images/missing.gif", "/not_an_image.txt"};
    size_t num_urls = sizeof(urls) / sizeof(urls[0]);

    for (size_t i = 0; i < num_urls; ++i) {
        handle_request(urls[i]);
    }

    return 0;
}