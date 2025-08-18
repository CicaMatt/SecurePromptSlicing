#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define UPLOADS_DIR "./uploads/"
#define MAX_FILE_SIZE 1024 * 1024 // 1 MB

void upload_file(const char* file_content, size_t content_length) {
    struct stat st = {0};
    if (stat(UPLOADS_DIR, &st) == -1) {
        mkdir(UPLOADS_DIR, 0755);
    }

    FILE *fp;
    char filename[64];
    snprintf(filename, sizeof(filename), "%s/uploaded_file", UPLOADS_DIR);

    fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file for writing");
        return;
    }

    size_t bytes_written = fwrite(file_content, 1, content_length, fp);
    fclose(fp);

    if (bytes_written != content_length) {
        fprintf(stderr, "Error writing to file\n");
        remove(filename);
        return;
    }
}

int main() {
    const char* fake_file_content = "This is a test file content.";
    size_t fake_content_length = strlen(fake_file_content);

    upload_file(fake_file_content, fake_content_length);

    printf("File uploaded successfully.\n");

    return 0;
}