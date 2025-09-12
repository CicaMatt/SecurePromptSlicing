#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 100
#define IMAGE_PATH "images/"

void img(const char *name) {
    char full_path[MAX_NAME_LENGTH + strlen(IMAGE_PATH)];
    snprintf(full_path, sizeof(full_path), "%s%s", IMAGE_PATH, name);

    FILE *file = fopen(full_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[length];
    fread(buffer, 1, length, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", length);
    if (strstr(full_path, ".jpg") || strstr(full_path, ".jpeg")) {
        printf("Content-Type: image/jpeg\r\n");
    } else if (strstr(full_path, ".png")) {
        printf("Content-Type: image/png\r\n");
    } else if (strstr(full_path, ".gif")) {
        printf("Content-Type: image/gif\r\n");
    }
    printf("\r\n");

    fwrite(buffer, 1, length, stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s name\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}