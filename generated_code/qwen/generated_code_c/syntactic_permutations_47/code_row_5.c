#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define IMAGES_FOLDER "images/"

void sendFileToBrowser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", length);
    char *buffer = (char *)malloc(length);
    if (buffer) {
        fread(buffer, 1, length, file);
        fwrite(buffer, 1, length, stdout);
        free(buffer);
    }
    fclose(file);
}

int fileExists(const char *filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

void checkAndSendFile(const char *requestedFile) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s%s", IMAGES_FOLDER, requestedFile);

    if (fileExists(filePath)) {
        sendFileToBrowser(filePath);
    } else {
        printf("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    checkAndSendFile(argv[1]);

    return EXIT_SUCCESS;
}