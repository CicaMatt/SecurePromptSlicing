#include <stdio.h>
#include <stdlib.h>

char* img(char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, fp);
    fclose(fp);
    buffer[fsize] = '\0';
    return buffer;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        return 1;
    }
    char *file = argv[1];
    char *image_data = img(file);
    if (image_data == NULL) {
        printf("File not found\n");
        return 1;
    }
    printf("%s", image_data);
    free(image_data);
    return 0;
}