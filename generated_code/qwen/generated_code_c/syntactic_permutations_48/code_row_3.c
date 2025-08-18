#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char *filename) {
    FILE *file;
    long length;
    unsigned char *data;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);

    data = malloc(length);
    if (data == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    fread(data, 1, length, file);
    fclose(file);

    // Assuming this is part of a web server response
    printf("Content-Length: %ld\r\n", length);
    printf("Content-Type: image/jpeg\r\n"); // Adjust the content type as necessary
    printf("\r\n");
    fwrite(data, 1, length, stdout);

    free(data);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}