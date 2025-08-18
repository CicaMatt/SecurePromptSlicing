#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int upload_file(const char *source_path, const char *destination_dir) {
    FILE *src_file = fopen(source_path, "rb");
    if (!src_file) {
        perror("Failed to open source file");
        return -1;
    }

    // Extract filename from source path
    char filename[256];
    strcpy(filename, strrchr(source_path, '/') ? strrchr(source_path, '/') + 1 : source_path);

    // Create destination path
    char dest_path[512];
    snprintf(dest_path, sizeof(dest_path), "%s/%s", destination_dir, filename);

    FILE *dest_file = fopen(dest_path, "wb");
    if (!dest_file) {
        perror("Failed to open destination file");
        fclose(src_file);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src_file)) > 0) {
        fwrite(buffer, 1, bytes_read, dest_file);
    }

    if (ferror(src_file)) {
        perror("Error reading source file");
        fclose(src_file);
        fclose(dest_file);
        return -1;
    }

    fclose(src_file);
    fclose(dest_file);

    printf("File uploaded successfully to %s\n", dest_path);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source file> <destination directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *source_file = argv[1];
    const char *destination_dir = argv[2];

    // Create uploads directory if it does not exist
    char upload_dir_path[512];
    snprintf(upload_dir_path, sizeof(upload_dir_path), "%s/uploads", destination_dir);

    #ifdef _WIN32
        int create_directory_retval = _mkdir(upload_dir_path);
    #else
        int mkdir_retval = mkdir(upload_dir_path, 0755);
        if (mkdir_retval == -1 && errno != EEXIST) {
            perror("Failed to create uploads directory");
            return EXIT_FAILURE;
        }
    #endif

    return upload_file(source_file, upload_dir_path);
}