#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define IMAGES_FOLDER "./images/"
#define BUFFER_SIZE 1024

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", file_size);
    
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

void handle_request(const char *url_path) {
    if (strncmp(url_path, "/images/", 8) == 0) {
        const char *file_path = IMAGES_FOLDER;
        strcat((char *)file_path + strlen(IMAGES_FOLDER), url_path + 8);

        struct stat buffer;
        if (stat(file_path, &buffer) == 0 && S_ISREG(buffer.st_mode)) {
            send_file_to_browser(file_path);
        } else {
            printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        }
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot a valid URL path for images.\n");
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);

    if (strncmp(buffer, "GET ", 4) == 0) {
        char *url_path = strchr(buffer + 4, ' ') + 1;
        url_path[strcspn(url_path, "\r\n")] = '\0';

        handle_request(url_path);
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMethod not supported.\n");
    }

    return 0;
}