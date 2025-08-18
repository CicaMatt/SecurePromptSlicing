#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_SIZE 1048576 // 1MB
#define UPLOADS_DIR "uploads"

int main() {
    char buffer[MAX_FILE_SIZE];
    FILE *file;
    size_t bytes_read;

    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }

    file = fopen("uploaded_file.pdf", "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return EXIT_FAILURE;
    }

    bytes_read = fread(buffer, 1, sizeof(buffer), stdin);
    if (bytes_read == 0 && ferror(stdin)) {
        perror("Error reading from standard input");
        fclose(file);
        remove("uploaded_file.pdf");
        return EXIT_FAILURE;
    }

    fwrite(buffer, 1, bytes_read, file);
    fclose(file);

    if (rename("uploaded_file.pdf", UPLOADS_DIR "/uploaded_file.pdf") != 0) {
        perror("Failed to move file to uploads directory");
        remove("uploaded_file.pdf");
        return EXIT_FAILURE;
    }

    printf("Content-type: text/plain\r\n\r\nFile uploaded successfully.\n");

    return EXIT_SUCCESS;
}