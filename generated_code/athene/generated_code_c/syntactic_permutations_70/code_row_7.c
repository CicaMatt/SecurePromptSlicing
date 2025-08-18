#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define UPLOAD_DIR "uploads"
#define BUFFER_SIZE 1024

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0755);
    }
}

int upload_file(const char *filename, FILE *file) {
    char buffer[BUFFER_SIZE];
    size_t nread;
    ensure_directory_exists(UPLOAD_DIR);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", UPLOAD_DIR, filename);
    FILE *fp = fopen(path, "wb");
    if (!fp) return -1;

    while ((nread = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, nread, fp);
    }

    fclose(fp);
    return 0;
}

int main() {
    // Simulate receiving a file (for testing purposes)
    const char *test_filename = "example.txt";
    FILE *test_file = fopen(test_filename, "rb");
    if (!test_file) {
        perror("Failed to open test file");
        return 1;
    }

    int result = upload_file(test_filename, test_file);
    fclose(test_file);

    if (result == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}