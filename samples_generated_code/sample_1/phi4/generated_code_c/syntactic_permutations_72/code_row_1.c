#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *source_path, const char *upload_dir, const char *filename) {
    FILE *src_file;
    FILE *dest_file;

    create_directory(upload_dir);

    char full_dest_path[1024];
    snprintf(full_dest_path, sizeof(full_dest_path), "%s/%s", upload_dir, filename);

    src_file = fopen(source_path, "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Error opening source file.\n");
        return -1;
    }

    dest_file = fopen(full_dest_path, "wb");
    if (dest_file == NULL) {
        fprintf(stderr, "Error creating destination file.\n");
        fclose(src_file);
        return -1;
    }

    char buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    return 0;
}

int main() {
    const char *source_path = "example.txt"; // Replace with your source file path
    const char *upload_dir = "./uploads";
    const char *filename = "uploaded_example.txt"; // Desired filename in the uploads folder

    if (upload_file(source_path, upload_dir, filename) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload file.\n");
    }

    return 0;
}