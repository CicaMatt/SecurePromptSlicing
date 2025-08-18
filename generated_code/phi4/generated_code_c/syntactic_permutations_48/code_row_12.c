#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void img(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';

    printf("%s\n", buffer); // Simulating sending the binary data as a response

    free(buffer);
    fclose(file);
}

int main() {
    const char* filename = "example.jpg"; // Replace with your actual file path
    img(filename);
    return 0;
}