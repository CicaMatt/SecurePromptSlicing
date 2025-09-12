#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

// Function declarations
void create_directory(const char *path);
int upload_file(const char *source_path, const char *destination_dir, const char *file_name);

int main() {
    const char *source_path = "example.txt"; // Path of the file to be uploaded
    const char *file_name = "example.txt";   // Name of the file to be saved in uploads directory

    if (upload_file(source_path, "uploads", file_name) == 0) {
        printf("File upload successful.\n");
    } else {
        printf("File upload failed.\n");
    }

    return 0;
}

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *source_path, const char *destination_dir, const char *file_name) {
    FILE *src_file;
    FILE *dest_file;

    create_directory(destination_dir);

    src_file = fopen(source_path, "rb");
    if (src_file == NULL) {
        perror("Error opening source file");
        return -1;
    }

    char dest_path[1024];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", destination_dir, file_name);
    dest_file = fopen(dest_path, "wb");
    if (dest_file == NULL) {
        perror("Error creating destination file");
        fclose(src_file);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    if (ferror(src_file) || ferror(dest_file)) {
        perror("Error during file copy");
        fclose(src_file);
        fclose(dest_file);
        return -1;
    }

    fclose(src_file);
    fclose(dest_file);

    return 0;
}