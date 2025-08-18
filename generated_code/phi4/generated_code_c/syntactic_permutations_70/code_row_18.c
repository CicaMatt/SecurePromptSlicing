#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOADS_DIR "uploads/"
#define BUFFER_SIZE 1024

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int upload_file(const char *filename, const char *content) {
    FILE *file;
    int len = strlen(content);

    // Ensure uploads directory exists
    mkdir(UPLOADS_DIR, 0777);

    file = fopen(strcat(strdup(UPLOADS_DIR), filename), "w");
    if (file == NULL) {
        handle_error("Error opening file for writing.");
    }

    if (fwrite(content, sizeof(char), len, file) != len) {
        fclose(file);
        handle_error("Error writing content to file.");
    }

    fclose(file);

    printf("File '%s' uploaded successfully.\n", filename);
    return 0;
}

int main() {
    char *filename = "test.txt";
    char content[BUFFER_SIZE] = "Hello, World! This is a test upload.";

    upload_file(filename, content);

    return EXIT_SUCCESS;
}