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
    char *fileContent = malloc(fsize + 1);
    fread(fileContent, 1, fsize, fp);
    fclose(fp);
    // Normally you would send the fileContent back to the client here
    free(fileContent);
}

int main() {
    char *file = "example.jpg"; // This should be replaced with request.args.get('file')
    img(file);
    return 0;
}