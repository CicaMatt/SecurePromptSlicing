#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* name) {
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "images/%s", name);

    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found.\n");
        return;
    }

    // Determine content type based on file extension
    const char* ext = strrchr(name, '.');
    const char* contentType = "application/octet-stream";
    if (ext != NULL) {
        if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
            contentType = "image/jpeg";
        } else if (strcmp(ext, ".png") == 0) {
            contentType = "image/png";
        } else if (strcmp(ext, ".gif") == 0) {
            contentType = "image/gif";
        }
    }

    printf("HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", contentType);

    // Send the file to the browser
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}