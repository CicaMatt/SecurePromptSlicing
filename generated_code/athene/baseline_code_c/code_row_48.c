#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = malloc(fsize + 1);
    fread(buffer, fsize, 1, fp);
    fclose(fp);
    printf("Content-Type: image/jpeg\n");
    printf("Content-Length: %ld\n", fsize);
    printf("\n");
    fwrite(buffer, fsize, 1, stdout);
    free(buffer);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        exit(1);
    }
    img(argv[1]);
    return 0;
}