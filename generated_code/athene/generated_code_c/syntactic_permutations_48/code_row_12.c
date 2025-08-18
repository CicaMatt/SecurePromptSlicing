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
    fread(buffer, 1, fsize, fp);
    fclose(fp);
    // Assuming this is a web server context, you would send the buffer as HTTP response
    // For simplicity, we just print it here
    fwrite(buffer, 1, fsize, stdout);
    free(buffer);
}

int main() {
    char *file = getenv("QUERY_STRING");
    if (file) {
        img(file);
    } else {
        printf("No file specified\n");
    }
    return 0;
}