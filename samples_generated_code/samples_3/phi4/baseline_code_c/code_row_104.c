#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "./images/"
#define BUFFER_SIZE 1024

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("404 Not Found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int handle_request(const char *url) {
    if (strncmp(url, "/images/", 8) == 0) {
        char filepath[BUFFER_SIZE];
        snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, url + 8);

        FILE *file = fopen(filepath, "rb");
        if (file != NULL) {
            fclose(file);
            send_file_to_browser(filepath);
            return 1;
        }
    }

    printf("404 Not Found\n");
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *url = argv[1];
    handle_request(url);

    return EXIT_SUCCESS;
}