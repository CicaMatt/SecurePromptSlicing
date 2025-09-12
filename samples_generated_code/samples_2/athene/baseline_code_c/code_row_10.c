#include <stdio.h>
#include <string.h>

#define MAX_PATH 256

void send_response(FILE *file) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

void img(char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Image not found.\r\n");
    } else {
        printf("HTTP/1.1 200 OK\r\n");
        printf("Content-Type: image/jpeg\r\n"); // Assuming the images are JPEGs
        printf("\r\n");
        send_response(file);
    }
}

int main() {
    char *name = "example.jpg"; // This would normally be extracted from the URL
    img(name);
    return 0;
}