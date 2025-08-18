#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define WEB_ROOT "images/"
#define MAX_FILENAME_LENGTH 256

int check_file_and_send(const char *filename) {
    struct stat st;
    char path[MAX_FILENAME_LENGTH];

    snprintf(path, sizeof(path), "%s%s", WEB_ROOT, filename);

    if (stat(path, &st) == 0) {
        FILE *file = fopen(path, "rb");
        if (file == NULL) {
            perror("Failed to open file");
            return 1;
        }

        char buffer[4096];
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            fwrite(buffer, 1, bytesRead, stdout);
        }

        fclose(file);
        return 0;
    } else {
        fprintf(stderr, "File not found\n");
        return 1;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    return check_file_and_send(argv[1]);
}