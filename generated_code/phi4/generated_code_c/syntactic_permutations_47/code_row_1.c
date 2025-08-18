#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_DIR "./images/"
#define MAX_PATH_LENGTH 256

int send_file_to_browser(const char *filename) {
    FILE *file = fopen(IMAGES_DIR filename, "rb");
    if (!file) {
        printf("File not found.\n");
        return -1;
    }

    // Send file to the browser (simulated)
    printf("Sending %s to the browser...\n", IMAGES_DIR filename);

    fclose(file);
    return 0;
}

void handle_request(const char *url) {
    if (strncmp(url, "/images/", strlen("/images/")) == 0) {
        size_t len = strlen(url + strlen("/images/"));
        
        // Ensure null-termination
        char filename[MAX_PATH_LENGTH];
        strncpy(filename, url + strlen("/images/"), len);
        filename[len] = '\0';

        send_file_to_browser(filename);
    } else {
        printf("Invalid URL.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}