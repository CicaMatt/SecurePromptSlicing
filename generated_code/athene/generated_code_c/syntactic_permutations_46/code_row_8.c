#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void img(char *name) {
    char path[MAX_PATH];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\n");
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("Image not found.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char *extension = strrchr(name, '.');
    const char *contentType = (extension && !strcmp(extension, ".jpg")) ? "image/jpeg" :
                              (extension && !strcmp(extension, ".png")) ? "image/png" : 
                              "application/octet-stream";

    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: %s\r\n", contentType);
    printf("Content-Length: %ld\r\n", fileSize);
    printf("\r\n");

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
    fclose(file);
}

int main() {
    // Simulate the URL parameter
    char *name = "example.jpg"; // This would normally come from a request
    img(name);
    return 0;
}