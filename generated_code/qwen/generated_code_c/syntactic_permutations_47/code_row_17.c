#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_FOLDER "images/"
#define MAX_FILENAME_LENGTH 1024

int check_file_exists(const char* filename) {
    char path[MAX_FILENAME_LENGTH];
    snprintf(path, sizeof(path), "%s%s", IMAGE_FOLDER, filename);

    FILE *file = fopen(path, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void handle_request(const char* filename) {
    if (check_file_exists(filename)) {
        printf("File '%s' exists in the images folder.\n", filename);
        // Additional logic can be added here to serve the file
    } else {
        printf("File '%s' does not exist in the images folder.\n", filename);
    }
}

int main() {
    const char* url = "/image.jpg"; // Simulating a URL request for an image
    const char* filename = url + 1; // Removing leading slash

    handle_request(filename);

    return 0;
}