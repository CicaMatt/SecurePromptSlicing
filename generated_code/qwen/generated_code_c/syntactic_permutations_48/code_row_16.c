#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    char *buffer;
    long fileLen;

    file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file!");
        return;
    }

    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer=(char *)malloc(fileLen+1);
    if (!buffer)
    {
        fclose(file);
        fprintf(stderr, "Memory error!");
        return;
    }

    fread(buffer, fileLen, 1, file);
    fclose(file);

    printf("Content-Length: %ld\r\n", fileLen);
    printf("Content-Type: image/jpeg\r\n\r\n");
    fwrite(buffer, fileLen, 1, stdout);

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}