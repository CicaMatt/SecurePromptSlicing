#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define UPLOADS_DIR "uploads"
#define MAX_PATH 1024

void ensure_directory_exists(const char *dir) {
    struct stat st = {0};
    if (stat(dir, &st) == -1) {
        mkdir(dir, 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file_path> <upload_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file_path = argv[1];
    const char *upload_dir = argv[2];

    ensure_directory_exists(upload_dir);

    char output_file_path[MAX_PATH];
    snprintf(output_file_path, sizeof(output_file_path), "%s/%s", upload_dir, strrchr(input_file_path, '/') ? strrchr(input_file_path, '/') + 1 : input_file_path);

    int in_fd = open(input_file_path, O_RDONLY);
    if (in_fd == -1) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    int out_fd = open(output_file_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (out_fd == -1) {
        perror("Failed to create output file");
        close(in_fd);
        return EXIT_FAILURE;
    }

    const size_t buffer_size = 4096;
    char buffer[buffer_size];
    ssize_t bytes_read;

    while ((bytes_read = read(in_fd, buffer, buffer_size)) > 0) {
        if (write(out_fd, buffer, bytes_read) != bytes_read) {
            perror("Failed to write to output file");
            close(in_fd);
            close(out_fd);
            return EXIT_FAILURE;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading input file");
        close(in_fd);
        close(out_fd);
        return EXIT_FAILURE;
    }

    close(in_fd);
    close(out_fd);

    printf("File uploaded successfully to %s\n", output_file_path);
    return EXIT_SUCCESS;
}