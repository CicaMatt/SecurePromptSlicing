#include <stdio.h>
#include <string.h>
#include <dirent.h>

void create_directory(const char *path) {
    mkdir(path, 0755);
}

int upload_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) return -1;

    const char *upload_dir = "uploads";
    create_directory(upload_dir);

    char dest_path[256];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", upload_dir, filename);

    FILE *dest_file = fopen(dest_path, "wb");
    if (dest_file == NULL) {
        fclose(file);
        return -1;
    }

    const int buffer_size = 4096;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(file);
    fclose(dest_file);

    return 0;
}

int main() {
    const char *filename = "example.txt";
    if (upload_file(filename) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }
    return 0;
}