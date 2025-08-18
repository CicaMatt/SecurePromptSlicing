#include <stdio.h>
#include <stdlib.h>

void img(char *file) {
    FILE *fp;
    fp = fopen(file, "rb");
    if (fp == NULL) {
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *content = malloc(fsize + 1);
    fread(content, 1, fsize, fp);
    fclose(fp);
    // Assuming the content is being sent as a response here
}

int main() {
    char file[] = "example.jpg"; // Example usage
    img(file);
    return 0;
}