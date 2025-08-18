#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Define constants for compression types
#define NONE 0
#define BZIP2 1

// Function prototypes
void extract_tar(const char *tar_path, const char *extract_to);
int detect_compression_type(const char *file_path);

int main() {
    const char *tar_file = "/path/to/archive.tar"; // Replace with actual path to .tar file
    const char *output_dir = "/tmp/unpack";

    extract_tar(tar_file, output_dir);

    return 0;
}

void extract_tar(const char *tar_path, const char *extract_to) {
    // This is a placeholder function. Actual tar extraction logic would be more complex.
    printf("Extracting %s to %s\n", tar_path, extract_to);
    
    // Simulate detecting compression type
    int compression_type = detect_compression_type(tar_path);

    switch (compression_type) {
        case NONE:
            printf("No compression detected.\n");
            break;
        case BZIP2:
            printf("BZip2 compression detected.\n");
            break;
        default:
            printf("Unknown or unsupported compression type.\n");
            return;
    }

    // Simulate extraction process
    printf("Extracting contents...\n");

    // Create output directory if it doesn't exist
    struct stat st = {0};
    if (stat(extract_to, &st) == -1) {
        mkdir(extract_to, 0700);
    }
    
    // Open the tar file and read contents (this is a simplified example)
    int fd = open(tar_path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // Simulate processing tar contents
        printf("Processing data...\n");
        
        // Example: write to a file in the output directory (simplified)
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/example.txt", extract_to);
        int out_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd < 0) {
            perror("Failed to create output file");
            close(fd);
            exit(EXIT_FAILURE);
        }
        
        write(out_fd, buffer, bytes_read);
        close(out_fd);
    }

    if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int detect_compression_type(const char *file_path) {
    // This is a placeholder function. Actual detection logic would involve checking the file signature.
    const char *magic_number_bzip2 = "BZh";
    
    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file for compression check");
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[3];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    close(fd);

    if (bytes_read == sizeof(buffer)) {
        if (memcmp(buffer, magic_number_bzip2, 3) == 0) {
            return BZIP2;
        }
    }

    return NONE;
}