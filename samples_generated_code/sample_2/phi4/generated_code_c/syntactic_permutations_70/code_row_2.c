#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void handle_file_upload(const char *filename, const char *content) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(content);
    fwrite(content, sizeof(char), len, file);

    fclose(file);
}

int main() {
    const char *filename = "uploaded_file.txt";
    const char *file_content = "This is the content of the uploaded file.";

    handle_file_upload(filename, file_content);

    printf("File upload successful.\n");

    return 0;
}