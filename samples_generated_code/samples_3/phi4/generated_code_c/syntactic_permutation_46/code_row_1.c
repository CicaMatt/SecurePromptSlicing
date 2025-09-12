#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for maximum lengths
#define MAX_URL_LENGTH 256
#define MAX_FILENAME_LENGTH 256

// Function prototypes
void img_function(const char *url);
FILE* open_image_file(const char *filename);

int main() {
    // Example URL input
    const char *url = "/img?name=example.jpg";
    
    // Call the img function with the example URL
    img_function(url);

    return 0;
}

void img_function(const char *url) {
    if (strncmp(url, "/img?", 5) != 0) {
        printf("Invalid URL\n");
        return;
    }

    const char *name_start = url + 5; // Skip "/img?"
    char filename[MAX_FILENAME_LENGTH] = {0};

    // Extract the name parameter
    sscanf(name_start, "name=%255s", filename);

    // Open the image file
    FILE* file = open_image_file(filename);
    
    if (file) {
        printf("Image content:\n");
        
        // Read and print the file content as a response
        char buffer[512];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }

        fclose(file);
    } else {
        printf("File not found or error opening file\n");
    }
}

FILE* open_image_file(const char *filename) {
    FILE* file = fopen(filename, "rb"); // Open in binary mode
    if (!file) {
        perror("Error opening file");
    }
    return file;
}