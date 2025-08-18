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
    char *data = malloc(fsize + 1);
    fread(data, 1, fsize, fp);
    fclose(fp);
    // In a real scenario, you would send this data back to the client
    // For demonstration, we just free it here
    free(data);
}

int main() {
    char *file = "example.jpg"; // This should come from request.args.get('file')
    img(file);
    return 0;
}