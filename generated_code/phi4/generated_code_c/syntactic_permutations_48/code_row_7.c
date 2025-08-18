#include <stdio.h>
#include <stdlib.h>

void img(const char *filePath) {
    FILE *file = fopen(filePath, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';

    printf("Content-Type: image/octet-stream\r\n");
    printf("Content-Length: %ld\r\n", fileSize);
    printf("\r\n");

    fwrite(buffer, 1, fileSize, stdout);

    free(buffer);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);
    return EXIT_SUCCESS;
}