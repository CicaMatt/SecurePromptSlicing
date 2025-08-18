#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 256

// Mock-up of a decorator concept in C for routing
void route(const char* url, void (*function)(const char*)) {
    if (strcmp(url, "/img") == 0) {
        function(NULL); // In actual use case, extract the file name from the URL.
    }
}

// Function to open and send image file content
void img(const char *name) {
    if (name == NULL) {
        printf("HTTP/1.1 400 Bad Request\r\n");
        return;
    }

    char filePath[MAX_PATH_LENGTH];
    snprintf(filePath, sizeof(filePath), "images/%s", name);

    FILE *file = fopen(filePath, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\n");
        return;
    }

    // Send HTTP headers
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\n");

    // Read and send file content
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main() {
    const char *url = "/img"; // Example URL
    route(url, img); // This would normally extract the image name from the URL

    return 0;
}