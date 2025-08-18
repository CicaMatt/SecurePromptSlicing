#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(EXIT_FAILURE);
    }
}

int upload_file(const char *filename, FILE *in) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    FILE *out = fopen(path, "wb");
    if (!out) {
        perror("Failed to open file for writing");
        return 1;
    }

    size_t nread;
    char buffer[BUFFER_SIZE];

    while ((nread = fread(buffer, 1, BUFFER_SIZE, in)) > 0) {
        if (fwrite(buffer, 1, nread, out) != nread) {
            perror("Failed to write file");
            fclose(out);
            return 1;
        }
    }

    fclose(out);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    create_directory(UPLOAD_DIR);

    const char *filename = argv[1];
    FILE *in = fopen(filename, "rb");
    if (!in) {
        perror("Failed to open file for reading");
        return 1;
    }

    int result = upload_file(filename, in);
    fclose(in);

    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("File upload failed.\n");
    }

    return result;
}