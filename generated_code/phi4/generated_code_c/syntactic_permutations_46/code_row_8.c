#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *filename;
} FileObject;

FileObject open(const char *path) {
    FileObject file;
    file.filename = strdup(path);
    return file;
}

void img(const char *name) {
    char path[256];
    snprintf(path, sizeof(path), "images/%s", name);

    FileObject file = open(path);

    printf("HTTP/1.0 200 OK\r\n");
    printf("Content-Type: image/jpeg\r\n"); // Assuming the images are JPEG
    printf("\r\n");

    FILE *fp = fopen(file.filename, "rb");
    if (fp) {
        char buffer[1024];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
            fwrite(buffer, 1, bytesRead, stdout);
        }
        fclose(fp);
    } else {
        printf("HTTP/1.0 404 Not Found\r\n");
        printf("\r\n");
        printf("File not found.\n");
    }

    free((void *)file.filename);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *name = argv[1];
    img(name);

    return EXIT_SUCCESS;
}