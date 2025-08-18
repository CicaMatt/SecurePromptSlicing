#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_FOLDER "images/"
#define MAX_FILENAME_LENGTH 1024

int check_file_and_send(const char *filename) {
    char path[MAX_FILENAME_LENGTH];
    snprintf(path, sizeof(path), "%s%s", IMAGE_FOLDER, filename);

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        perror("File not found");
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *buffer = malloc(filesize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }
    fread(buffer, filesize, 1, file);
    fclose(file);

    // Simulating sending to browser
    printf("HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: image/jpeg\r\n\r\n", filesize);
    fwrite(buffer, filesize, 1, stdout);
    free(buffer);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    return check_file_and_send(argv[1]);
}