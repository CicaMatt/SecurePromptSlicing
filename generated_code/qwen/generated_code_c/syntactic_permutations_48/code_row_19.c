#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* file) {
    FILE *fp;
    fp = fopen(file, "rb");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    unsigned char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    img(argv[1]);
    return 0;
}