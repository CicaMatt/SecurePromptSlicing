#include <stdio.h>
#include <stdlib.h>

void img(char* file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) exit(1);
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *fileContent = malloc(fsize + 1);
    fread(fileContent, 1, fsize, fp);
    fclose(fp);
    printf("Content-Type: image/jpeg\n");
    printf("Content-Length: %ld\n", fsize);
    printf("\n");
    fwrite(fileContent, 1, fsize, stdout);
    free(fileContent);
}