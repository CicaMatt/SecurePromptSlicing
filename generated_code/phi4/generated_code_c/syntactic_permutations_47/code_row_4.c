#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_FOLDER "./images/"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_name>\n", argv[0]);
        return 1;
    }

    const char *image_path = strcat(strdup(IMAGES_FOLDER), argv[1]);

    struct stat buffer;
    if (stat(image_path, &buffer) == 0) {
        FILE *file = fopen(image_path, "rb");
        if (file != NULL) {
            // Send HTTP header
            printf("HTTP/1.1 200 OK\r\n"
                   "Content-Type: image/jpeg\r\n" // Assuming JPEG for simplicity; adapt as necessary.
                   "Connection: close\r\n"
                   "\r\n");

            // Send file content
            char buffer[1024];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
                fwrite(buffer, 1, bytes_read, stdout);
            }

            fclose(file);
        } else {
            printf("HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/plain\r\n"
                   "Connection: close\r\n"
                   "\r\n"
                   "File not found.\n");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\n"
               "Content-Type: text/plain\r\n"
               "Connection: close\r\n"
               "\r\n"
               "File not found.\n");
    }

    return 0;
}