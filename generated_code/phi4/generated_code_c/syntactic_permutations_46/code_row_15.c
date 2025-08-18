#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void sendResponse(FILE *file, const char *contentType) {
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n\r\n");
        printf("File not found.\r\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: %s\r\n", contentType);
    printf("Content-Length: %ld\r\n\r\n", fileSize);

    char buffer[BUFFER_SIZE];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
}

int main() {
    char method[10], path[256], version[10];
    fgets(method, sizeof(method), stdin);
    fgets(path, sizeof(path), stdin);
    fgets(version, sizeof(version), stdin);

    if (strncmp(method, "GET", 3) == 0 && strncmp(path + 1, "/img/", 5) == 0) {
        char *name = path + strlen("/img/");
        
        FILE *file = fopen(name, "rb");
        if (file != NULL) {
            sendResponse(file, "image/jpeg"); // Assume JPEG for demonstration
            fclose(file);
        } else {
            printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\r\n");
        }
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/plain\r\n\r\nMethod not allowed.\r\n");
    }

    return 0;
}