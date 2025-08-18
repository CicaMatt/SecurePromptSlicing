#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_FOLDER "images/"
#define BUFFER_SIZE 256

int file_exists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char buffer[BUFFER_SIZE];
    while (file_size > 0) {
        int bytes_to_read = (file_size < BUFFER_SIZE) ? file_size : BUFFER_SIZE;
        fread(buffer, 1, bytes_to_read, file);
        fwrite(buffer, 1, bytes_to_read, stdout); // Simulating sending to browser
        file_size -= bytes_to_read;
    }

    fclose(file);
}

void handle_request(const char *url_path) {
    char filepath[BUFFER_SIZE];
    snprintf(filepath, sizeof(filepath), "%s%s", IMAGES_FOLDER, url_path + 1);

    if (file_exists(filepath)) {
        send_file_to_browser(filepath);
    } else {
        printf("File not found.\n");
    }
}

int main() {
    const char *url_path = "/example.jpg"; // Example URL path
    handle_request(url_path);
    return 0;
}