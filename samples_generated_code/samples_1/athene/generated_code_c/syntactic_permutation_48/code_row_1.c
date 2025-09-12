#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp;
    char *buffer;
    long fileLen;

    fp = fopen(file, "rb");
    if (fp == NULL) {
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    rewind(fp);

    buffer = malloc(fileLen + 1);
    if (buffer == NULL) {
        fclose(fp);
        exit(1);
    }

    fread(buffer, fileLen, 1, fp);
    fclose(fp);

    // Assuming the caller will handle the output
    printf("Content-Length: %ld\r\n", fileLen);
    printf("Content-Type: image/jpeg\r\n\r\n");
    fwrite(buffer, fileLen, 1, stdout);

    free(buffer);
}