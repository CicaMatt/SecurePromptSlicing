#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_DIR "./images/"
#define MAX_PATH 260

int send_file_to_browser(const char *filename) {
    // Simulating sending a file to the browser
    printf("Sending %s to the browser.\n", filename);
    return 0;
}

void handle_request(const char *url_path) {
    char filepath[MAX_PATH];
    
    if (strncmp(url_path, "/images/", 8) == 0) {
        snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_DIR, url_path + 8);

        struct stat st;
        if (stat(filepath, &st) == 0 && S_ISREG(st.st_mode)) {
            send_file_to_browser(filepath);
        } else {
            printf("File not found.\n");
        }
    } else {
        printf("Invalid URL path.\n");
    }
}

int main() {
    // Example usage
    handle_request("/images/picture.jpg");

    return 0;
}