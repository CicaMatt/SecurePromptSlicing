#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
int check_and_send_file(const char* filename);

#define IMAGES_FOLDER "images/"
#define MAX_PATH_LENGTH 256

void handle_request(const char *url) {
    // Extract the file name from the URL (assuming it's a simple path)
    char filepath[MAX_PATH_LENGTH];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, url + 7); // Assuming URL starts with "/images/"

    if (check_and_send_file(filepath)) {
        printf("File sent to browser.\n");
    } else {
        printf("Error: File not found or could not be opened.\n");
    }
}

int check_and_send_file(const char* filepath) {
    FILE *file = fopen(filepath, "rb");

    if (file == NULL) {
        return 0; // File does not exist
    }

    // Simulate sending the file to the browser
    printf("Sending file: %s\n", filepath);

    // Close the file after reading
    fclose(file);
    return 1;
}

int main() {
    const char *url = "/images/example.jpg";
    handle_request(url);
    
    return 0;
}