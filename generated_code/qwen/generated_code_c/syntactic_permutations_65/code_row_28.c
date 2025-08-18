#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    FILE *fp;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    fp = fopen("uploaded_file.pdf", "wb");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
        fwrite(buffer, 1, bytes_read, fp);
    }

    fclose(fp);

    char command[256];
    snprintf(command, sizeof(command), "mv uploaded_file.pdf %s/", UPLOAD_DIR);
    system(command);

    return 0;
}