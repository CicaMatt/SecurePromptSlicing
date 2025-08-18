#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define IMAGES_FOLDER "images/"

int send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("File not found.\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return 0;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming JPEG for simplicity
    printf("Content-Length: %ld\r\n", file_size);
    printf("\r\n");

    fwrite(buffer, 1, file_size, stdout);

    free(buffer);
    fclose(file);
    return 1;
}

int check_file_exists(const char *url) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", IMAGES_FOLDER, url);

    struct stat path_stat;
    if (stat(full_path, &path_stat) == 0 && S_ISREG(path_stat.st_mode)) {
        send_file_to_browser(full_path);
        return 1;
    }

    printf("HTTP/1.1 404 Not Found\r\n");
    printf("\r\n");
    printf("File not found.\n");

    return 0;
}

void handle_request() {
    char url[256];
    printf("Enter the URL path: ");
    if (fgets(url, sizeof(url), stdin)) {
        size_t len = strlen(url);
        if (len > 1 && url[len - 1] == '\n') {
            url[--len] = '\0';
        }
        check_file_exists(url);
    }
}

int main() {
    handle_request();
    return 0;
}