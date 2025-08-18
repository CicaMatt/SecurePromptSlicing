#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPLOAD_DIR "uploads"

void create_directory(const char *dir) {
    if (mkdir(dir, 0755) != 0 && errno != EEXIST) {
        perror("Failed to create directory");
        exit(1);
    }
}

void upload_file(const char *filename) {
    FILE *source = fopen(filename, "rb");
    if (!source) {
        perror("Failed to open source file");
        return;
    }

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);

    create_directory(UPLOAD_DIR);

    FILE *destination = fopen(path, "wb");
    if (!destination) {
        perror("Failed to open destination file");
        fclose(source);
        return;
    }

    const int buffer_size = 1024;
    unsigned char buffer[buffer_size];
    size_t nread;

    while ((nread = fread(buffer, 1, buffer_size, source)) > 0) {
        if (fwrite(buffer, 1, nread, destination) != nread) {
            perror("Failed to write file");
            fclose(source);
            fclose(destination);
            return;
        }
    }

    fclose(source);
    fclose(destination);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    upload_file(argv[1]);

    printf("File uploaded successfully.\n");
    return 0;
}