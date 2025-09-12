#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGES_FOLDER "images/"

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(IMAGES_FOLDER filename, "rb");
    if (file == NULL) {
        printf("404 Not Found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(filesize + 1);
    fread(buffer, 1, filesize, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\n");
    printf("Content-Type: image/jpeg\n"); // Assuming JPEG for simplicity
    printf("Content-Length: %ld\n\n", filesize);
    fwrite(buffer, 1, filesize, stdout);
    
    free(buffer);
}

void handle_request(const char *url) {
    if (strncmp(url, "/images/", 8) == 0) {
        const char *filename = url + 8;
        send_file_to_browser(filename);
    } else {
        printf("404 Not Found\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <url>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1]);

    return EXIT_SUCCESS;
}