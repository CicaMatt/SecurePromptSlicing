#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *buffer;
    long fileLen;

    // Open the file in binary mode
    file = fopen("example.txt", "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file example.txt!");
        return 1;
    }

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    buffer=(char *)malloc(fileLen+1);
    if (!buffer) {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return 2;
    }

    // Read the file into the buffer
    fread(buffer, fileLen, 1, file);

    // Null-terminate the buffer for string operations
    buffer[fileLen] = '\0';

    // Close the file
    fclose(file);

    // Example calculation: print the length of the file content
    printf("The file is %ld bytes long.\n", fileLen);

    // Free memory
    free(buffer);

    return 0;
}