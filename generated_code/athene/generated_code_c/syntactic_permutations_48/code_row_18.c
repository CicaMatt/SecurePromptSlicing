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
    // Assuming this is the point where you would send the file content back
    // In a real web server context, you'd use something like:
    // write(client_socket, fileContent, fsize);
    free(fileContent);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(1);
    }
    img(argv[1]);
    return 0;
}