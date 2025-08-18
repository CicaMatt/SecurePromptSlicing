#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void img(const char *name) {
    FILE *file;
    char filepath[1024];
    
    snprintf(filepath, sizeof(filepath), "images/%s", name);
    file = fopen(filepath, "rb");
    
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nFile not found.");
        return;
    }
    
    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Adjust the Content-Type as needed
    printf("Content-Length: %ld\r\n", filesize);
    printf("Connection: close\r\n\r\n");
    
    char *buffer = (char *)malloc(filesize);
    if (!buffer) {
        fclose(file);
        printf("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nMemory allocation failed.");
        return;
    }
    
    fread(buffer, 1, filesize, file);
    fwrite(buffer, 1, filesize, stdout);
    
    free(buffer);
    fclose(file);
}

int main() {
    // Simulating the call to img function with a parameter
    img("example.jpg");
    return 0;
}