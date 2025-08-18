#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_FILENAME_SIZE 256

void send_file_to_browser(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("Failed to get file stats");
        fclose(file);
        return;
    }

    printf("Content-Type: application/octet-stream\r\n");
    printf("Content-Disposition: attachment; filename=\"%s\"\r\n", filename);
    printf("Content-Length: %zu\r\n", st.st_size);
    printf("\r\n");

    char buffer[1024];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];

    struct stat st;
    if (stat(filename, &st) == -1) {
        if (errno == ENOENT) {
            printf("Content-Type: text/plain\r\n");
            printf("\r\n");
            printf("File not found.\n");
        } else {
            perror("Failed to check file existence");
        }
        return EXIT_FAILURE;
    }

    if (S_ISDIR(st.st_mode)) {
        printf("Content-Type: text/plain\r\n");
        printf("\r\n");
        printf("The specified path is a directory, not a file.\n");
        return EXIT_FAILURE;
    }

    send_file_to_browser(filename);

    return EXIT_SUCCESS;
}