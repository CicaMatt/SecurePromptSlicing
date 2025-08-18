#include <stdio.h>
#include <stdlib.h>

void img(char* file) {
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
    // Assuming this is the point where you would handle sending the buffer
    // In a web server context, you'd send it as a response with appropriate headers.
    free(buffer);
}

int main() {
    char *file = "example.jpg"; // This should come from request.args.get('file') in your actual application
    img(file);
    return 0;
}