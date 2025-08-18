#include <stdio.h>
#include <stdlib.h>

void img(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';

    fclose(file);

    // Simulating sending the image data to client
    printf("HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", bytesRead);
    fwrite(buffer, 1, bytesRead, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);
    return EXIT_SUCCESS;
}