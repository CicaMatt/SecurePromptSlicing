#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

// Function declarations
void create_directory(const char *path);
int upload_file(const char *filename);

int main() {
    const char *filename = "example.txt"; // Replace with your file name

    if (upload_file(filename) == 0) {
        printf("File uploaded successfully.\n");
    } else {
        printf("Failed to upload the file.\n");
    }

    return 0;
}

void create_directory(const char *path) {
    struct stat st = {0};

    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int upload_file(const char *filename) {
    const char *upload_dir = "./uploads";
    char full_path[256];

    // Create uploads directory
    create_directory(upload_dir);

    // Construct the path to save the file in the uploads folder
    snprintf(full_path, sizeof(full_path), "%s/%s", upload_dir, filename);

    FILE *src_file = fopen(filename, "rb");
    if (src_file == NULL) {
        perror("Failed to open source file");
        return -1;
    }

    FILE *dest_file = fopen(full_path, "wb");
    if (dest_file == NULL) {
        perror("Failed to create destination file");
        fclose(src_file);
        return -1;
    }

    // Copy the content of the source file to the destination file
    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    return 0;
}