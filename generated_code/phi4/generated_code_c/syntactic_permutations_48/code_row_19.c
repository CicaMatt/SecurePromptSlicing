#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

void img(const char *file) {
    if (file == NULL) {
        printf("Error: No file specified.\n");
        return;
    }

    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    fread(buffer, 1, fsize, fp);
    buffer[fsize] = '\0';

    printf("%s", buffer); // This is a simplification; in practice, you'd set appropriate HTTP headers.

    free(buffer);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    img(argv[1]);

    return EXIT_SUCCESS;
}