#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

void send_file_to_browser(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>File not found</h1>");
        return;
    }
    char buffer[1024];
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n\r\n");
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

void img(const char *name) {
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "images/%s", name);
    send_file_to_browser(path);
}

int main() {
    const char *url = "/img?name=example.jpg";
    char name[100];
    sscanf(url, "/img?name=%99[^\n]", name);
    img(name);
    return 0;
}