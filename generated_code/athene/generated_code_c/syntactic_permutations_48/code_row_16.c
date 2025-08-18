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
    buffer[fsize] = '\0';
    printf("Content-Type: image/jpeg\n");
    printf("Content-Length: %ld\n", fsize);
    printf("\n");
    fwrite(buffer, fsize, 1, stdout);
    free(buffer);
}

int main(int argc, char **argv) {
    char *file = getenv("QUERY_STRING");
    if (file != NULL) {
        char *token = strtok(file, "=");
        if (strcmp(token, "file") == 0) {
            token = strtok(NULL, "=");
            img(token);
        }
    } else {
        printf("No file parameter provided.\n");
    }
    return 0;
}