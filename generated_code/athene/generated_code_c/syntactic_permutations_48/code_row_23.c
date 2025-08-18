#include <stdio.h>
#include <stdlib.h>

char* img(char* file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) return NULL;
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *file_content = malloc(fsize + 1);
    fread(file_content, fsize, 1, fp);
    fclose(fp);
    file_content[fsize] = '\0';
    return file_content;
}