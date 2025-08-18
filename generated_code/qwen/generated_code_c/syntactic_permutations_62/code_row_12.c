#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    long fileLen;
    char *buffer;

    file = fopen("example.txt", "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file example.txt!");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer=(char *)malloc(fileLen+1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Memory error!");
        return 2;
    }

    fread(buffer, fileLen, 1, file);
    fclose(file);

    buffer[fileLen] = '\0';

    // Example calculation: print the length of the file
    printf("The file is %ld bytes long.\n", fileLen);

    free(buffer);
    return 0;
}