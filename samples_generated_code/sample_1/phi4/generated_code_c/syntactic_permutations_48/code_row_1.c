#include <stdio.h>
#include <stdlib.h>

void img(const char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file);
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(fp);
        return;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, fp);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file: %s\n", file);
        free(buffer);
        fclose(fp);
        return;
    }
    
    buffer[bytesRead] = '\0';

    printf("Content-Type: image/png\n");
    printf("\n");
    fwrite(buffer, 1, bytesRead, stdout);

    free(buffer);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}