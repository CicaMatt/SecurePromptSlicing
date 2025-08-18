#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found");
        return;
    }
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");
    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }
    fclose(file);
}

void img(const char *name) {
    char file_path[MAX_PATH];
    snprintf(file_path, MAX_PATH, "images/%s", name);
    send_file_to_browser(file_path);
}

int main() {
    const char *url = "/img?name=example.jpg";
    const char *name;
    if (strstr(url, "?name=")) {
        name = url + 6; // Skip "/img?"
    } else {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
        return 1;
    }
    img(name);
    return 0;
}