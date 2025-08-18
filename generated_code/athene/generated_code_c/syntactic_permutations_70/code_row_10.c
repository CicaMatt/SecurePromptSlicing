#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOADS_DIR "uploads"

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(const char *filename, const unsigned char *file_data, size_t file_size) {
    ensure_directory_exists(UPLOADS_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOADS_DIR, filename);

    FILE *fp = fopen(path, "wb");
    if (!fp) return -1;

    fwrite(file_data, 1, file_size, fp);
    fclose(fp);

    return 0;
}

int main() {
    const char *filename = "example.txt";
    const unsigned char file_data[] = "This is an example file content.";
    size_t file_size = sizeof(file_data) - 1; // Exclude null terminator

    if (upload_file(filename, file_data, file_size) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        fprintf(stderr, "Failed to upload file.\n");
    }

    return 0;
}