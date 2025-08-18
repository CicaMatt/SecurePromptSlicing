#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_DIR "./images/"
#define MAX_PATH_LENGTH 256

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
    // Simulate sending file
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);  // Output content as response
        }
        fclose(file);
    } else {
        printf("File not found.\n");
    }
}

void handle_request(const char *url_path) {
    char full_path[MAX_PATH_LENGTH];
    snprintf(full_path, sizeof(full_path), "%s%s", IMAGES_DIR, url_path);

    if (file_exists(full_path)) {
        send_file_to_browser(full_path);
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char *url_paths[] = { "image1.jpg", "image2.png", "nonexistent.gif" };
    int num_requests = sizeof(url_paths) / sizeof(url_paths[0]);

    for (int i = 0; i < num_requests; ++i) {
        handle_request(url_paths[i]);
        printf("\n");
    }

    return 0;
}