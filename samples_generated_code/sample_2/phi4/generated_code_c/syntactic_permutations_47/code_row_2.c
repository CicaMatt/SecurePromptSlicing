#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_DIR "./images/"
#define MAX_PATH_LENGTH 256

int send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("File not found.\n");
        return 0;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Print content to simulate sending (for demonstration purposes)
    char buffer[1024];
    printf("Sending file: %s\n", file_path);
    while ((size_t)file_size > 0 && !feof(file)) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);
        if (bytes_read == 0) break;
        fwrite(buffer, 1, bytes_read, stdout); // Simulate sending the file
        file_size -= bytes_read;
    }

    fclose(file);
    return 1;
}

int check_image_exists(const char *image_name) {
    char path[MAX_PATH_LENGTH];
    snprintf(path, sizeof(path), "%s%s", IMAGES_DIR, image_name);

    FILE *file = fopen(path, "rb");
    if (file) {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File does not exist
}

int main() {
    const char *image_name = "example.jpg"; // Example image name

    if (check_image_exists(image_name)) {
        send_file_to_browser(IMAGES_DIR);
    } else {
        printf("Image file does not exist.\n");
    }

    return 0;
}