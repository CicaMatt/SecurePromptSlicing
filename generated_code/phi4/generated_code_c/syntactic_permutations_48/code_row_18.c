#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void img(const char *file) {
    FILE *fp;
    char path[256];
    
    snprintf(path, sizeof(path), "%s", file);
    fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    
    img(argv[1]);
    return 0;
}