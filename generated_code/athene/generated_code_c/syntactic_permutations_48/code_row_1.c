#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp = fopen(file, "rb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *buffer = malloc(fsize + 1);
    fread(buffer, 1, fsize, fp);
    fclose(fp);
    // In a real application, you would send buffer as the response
    free(buffer);
}

int main() {
    // Simulating request.args.get('file') with command line argument
    if (argc > 1) {
        img(argv[1]);
    }
    return 0;
}