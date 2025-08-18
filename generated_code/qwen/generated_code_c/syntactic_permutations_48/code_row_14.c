#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* file_param) {
    FILE *file;
    char *filename = (char*)malloc(strlen(file_param) + 1);
    strcpy(filename, file_param);

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        free(filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)malloc(filesize + 1);
    fread(buffer, 1, filesize, file);
    fclose(file);

    printf("Content-Type: image/png\n");
    printf("Content-Length: %ld\n", filesize);
    printf("\n");
    fwrite(buffer, 1, filesize, stdout);

    free(filename);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    img(argv[1]);

    return 0;
}