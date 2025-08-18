#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

void sendResponse(FILE *file, const char *contentType) {
    printf("HTTP/1.1 200 OK\r\n");
    printf("Content-Type: %s\r\n", contentType);
    printf("\r\n");

    if (file != NULL) {
        char buffer[1024];
        size_t bytesRead;
        
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytesRead, stdout);
        }
        fclose(file);
    } else {
        printf("File not found.\r\n");
    }
}

void img(const char *name) {
    FILE *file = fopen(name, "rb");
    if (file == NULL) {
        sendResponse(NULL, "text/plain");
    } else {
        sendResponse(file, "image/jpeg"); // Assuming JPEG images
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_name>\r\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}