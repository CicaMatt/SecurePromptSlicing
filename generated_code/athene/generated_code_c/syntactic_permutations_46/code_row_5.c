#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(char *name) {
    char path[1024];
    snprintf(path, sizeof(path), "images/%s", name);
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        printf("HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);
    
    char *content = malloc(fsize + 1);
    fread(content, 1, fsize, file);
    fclose(file);

    printf("HTTP/1.1 200 OK\r\nContent-Type: image/*\r\nContent-Length: %ld\r\n\r\n", fsize);
    fwrite(content, 1, fsize, stdout);
    free(content);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nMissing name parameter");
        return 1;
    }
    img(argv[1]);
    return 0;
}