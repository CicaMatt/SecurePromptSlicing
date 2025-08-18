#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void create_directory(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(char *filename, FILE *in) {
    create_directory(UPLOAD_DIR);
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *out = fopen(path, "wb");
    if (out == NULL) return 1;

    char buffer[BUFFER_SIZE];
    size_t nread;
    while ((nread = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        fwrite(buffer, 1, nread, out);
    }

    fclose(out);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (in == NULL) {
        perror("Error opening file");
        return 1;
    }

    int result = upload_file(argv[1], in);
    fclose(in);

    if (result == 0) {
        printf("File uploaded successfully to %s\n", UPLOAD_DIR);
    } else {
        fprintf(stderr, "Failed to upload file\n");
    }

    return result;
}