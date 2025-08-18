#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy function to mimic sending a file as a response
void send_file_as_response(FILE *file) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
}

// Function to open and return the image file associated with the name parameter in the URL
FILE* img(const char *url) {
    const char *prefix = "/img?";
    size_t prefix_len = strlen(prefix);

    if (strncmp(url, prefix, prefix_len) != 0) {
        fprintf(stderr, "Invalid URL\n");
        return NULL;
    }

    // Extract filename from the URL
    const char *filename_start = url + prefix_len;
    char *filename_end = strchr(filename_start, '&');
    size_t filename_len;

    if (filename_end == NULL) {
        filename_len = strlen(filename_start);
    } else {
        filename_len = filename_end - filename_start;
    }

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "images/%.*s", (int)filename_len, filename_start);

    // Open the file and return its file pointer
    FILE *file = fopen(full_path, "r");
    if (!file) {
        perror("Failed to open file");
    }
    return file;
}

int main() {
    const char *url = "/img?name=example.jpg";
    FILE *image_file = img(url);

    if (image_file) {
        send_file_as_response(image_file);
        fclose(image_file);
    }

    return 0;
}