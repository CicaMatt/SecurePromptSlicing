#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256

void handle_file_upload(const char *filename, const char *file_content) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    fwrite(file_content, sizeof(char), strlen(file_content), fp);
    fclose(fp);
}

int main() {
    const char *filename = "uploaded_file.txt";
    const char *file_content = "This is the content of the uploaded file.";

    handle_file_upload(filename, file_content);

    printf("File '%s' has been saved.\n", filename);

    return 0;
}