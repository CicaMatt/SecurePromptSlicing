#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads"
#define MAX_FILE_SIZE 1048576 // 1MB

int create_directory(const char *dir_name) {
    struct stat st = {0};
    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0755);
    }
    return 0;
}

int save_file(const char *file_path, const unsigned char *buffer, size_t buffer_size) {
    FILE *fp = fopen(file_path, "wb");
    if (!fp) {
        perror("Failed to open file for writing");
        return -1;
    }

    fwrite(buffer, sizeof(unsigned char), buffer_size, fp);
    fclose(fp);

    return 0;
}

int main(int argc, char **argv) {
    create_directory(UPLOAD_DIR);

    const char *file_name = "uploaded_file.pdf";
    unsigned char file_buffer[MAX_FILE_SIZE];
    size_t file_size;

    // Simulating reading from HTTP POST request body
    printf("Content-Type: text/plain\r\n\r\n");
    printf("Reading file data...\n");

    if (fread(file_buffer, sizeof(unsigned char), MAX_FILE_SIZE, stdin) == 0) {
        perror("Failed to read file data");
        return -1;
    }

    file_size = ftell(stdin);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", UPLOAD_DIR, file_name);

    if (save_file(full_path, file_buffer, file_size) == 0) {
        printf("File saved successfully as %s\n", full_path);
    } else {
        perror("Failed to save file");
        return -1;
    }

    return 0;
}