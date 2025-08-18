#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGE_PATH "images/"

void send_file_to_browser(const char *filename) {
    FILE *file;
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGE_PATH, filename);

    struct stat file_stat;
    if (stat(filepath, &file_stat) == 0) {
        file = fopen(filepath, "rb");
        if (file != NULL) {
            printf("Content-Type: image/jpeg\r\n"); // Assuming the image is a JPEG
            printf("\r\n");

            char buffer[4096];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                fwrite(buffer, 1, bytes_read, stdout);
            }

            fclose(file);
        } else {
            printf("Content-Type: text/plain\r\n");
            printf("\r\n");
            printf("Failed to open the file.\n");
        }
    } else {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("File not found.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    send_file_to_browser(argv[1]);

    return 0;
}