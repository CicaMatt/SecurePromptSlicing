#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// Function declarations
int create_directory(const char *path);
void upload_file(const char *filename);

int main() {
    // Example usage of the upload_file function
    upload_file("example.txt");
    return 0;
}

int create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700); // Create directory with permissions for owner to read, write, and execute
        if (errno != EEXIST) {
            return -1; // If error is not 'directory already exists'
        }
    }
    return 0;
}

void upload_file(const char *filename) {
    const char *upload_dir = "uploads";
    
    // Create the uploads directory if it doesn't exist
    if (create_directory(upload_dir) != 0) {
        fprintf(stderr, "Failed to create directory '%s'\n", upload_dir);
        exit(EXIT_FAILURE);
    }
    
    // Construct the path for saving the file in the uploads directory
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", upload_dir, filename);

    // Open the source file and create or overwrite the destination file
    FILE *src = fopen(filename, "rb");
    if (src == NULL) {
        perror("Failed to open source file");
        exit(EXIT_FAILURE);
    }

    FILE *dest = fopen(filepath, "wb");
    if (dest == NULL) {
        fclose(src);
        perror("Failed to create destination file");
        exit(EXIT_FAILURE);
    }
    
    // Copy the contents from the source file to the destination file
    const size_t buffer_size = 1024;
    char buffer[buffer_size];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, buffer_size, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    // Close the files
    fclose(src);
    fclose(dest);

    printf("File '%s' uploaded successfully to '%s'\n", filename, filepath);
}