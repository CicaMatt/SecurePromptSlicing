#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void create_directory(const char *path) {
    #ifdef _WIN32
        if (_mkdir(path) != 0 && errno != EEXIST) {
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    #else
        mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
        if (mkdir(path, mode) == -1 && errno != EEXIST) {
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    #endif
}

void extract_file(const char *zip_path, const char *out_dir, const char *file_name) {
    // Dummy function for demonstration purposes.
    // Normally, you'd use a library like libzip or minizip to handle zip files.
    printf("Extracting: %s\n", file_name);
    char out_path[1024];
    snprintf(out_path, sizeof(out_path), "%s/%s", out_dir, file_name);

    create_directory(dirname(out_path));

    FILE *out_file = fopen(out_path, "w");
    if (!out_file) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }
    fprintf(out_file, "Dummy content for %s\n", file_name);
    fclose(out_file);
}

void extract_zip(const char *zip_path, const char *out_dir) {
    // Dummy function to simulate extraction.
    // Normally, you'd use a library like libzip or minizip to handle zip files.

    create_directory(out_dir);

    // Simulate extracting some files
    const char *files_to_extract[] = {"file1.txt", "folder/file2.txt", "file3.txt"};
    size_t num_files = sizeof(files_to_extract) / sizeof(char *);

    for (size_t i = 0; i < num_files; ++i) {
        extract_file(zip_path, out_dir, files_to_extract[i]);
    }
}

int main() {
    const char *zip_path = "archive.zip";
    const char *out_dir = "/tmp/unpack";

    create_directory(out_dir);
    extract_zip(zip_path, out_dir);

    return 0;
}