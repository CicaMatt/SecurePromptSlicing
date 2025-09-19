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
    fileLen=ftell(fp);
    rewind(fp);

    buffer = malloc(sizeof(char)*fileLen);
    if(buffer == NULL){
        fclose(fp);
        exit(1);
    }

    fread(buffer, fileLen, 1, fp);
    fclose(fp);

    // Assuming this is where you would handle sending the buffer
    // For demonstration purposes, we'll just print its length
    printf("File read successfully. Length: %ld\n", fileLen);

    free(buffer);
}