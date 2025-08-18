#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void img(const char* filename) {
    FILE *file;
    char *buffer;
    long fileLen;

    // Open file in read-binary mode
    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file %s", filename);
        return;
    }

    // Get file length
    fseek(file, 0, SEEK_END);
    fileLen=ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for entire content
    buffer=(char *)malloc(fileLen+1);
    if (!buffer) {
        fprintf(stderr, "Memory error!");
        fclose(file);
        return;
    }

    // Copy the file into the buffer
    fread(buffer, fileLen, 1, file);
    fclose(file);

    // Print the content of the file (for demonstration purposes)
    printf("%s\n", buffer);

    // Free the memory
    free(buffer);
}

int main() {
    const char* filename = "example.txt"; // This would be replaced by request.args.get('file') in a web application context
    img(filename);
    return 0;
}