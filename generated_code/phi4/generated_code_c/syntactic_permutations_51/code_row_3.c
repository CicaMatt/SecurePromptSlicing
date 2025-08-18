#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void extract_tar_file(const char *tar_path, const char *extract_to);

int main() {
    const char *tar_file = "example.tar.gz";
    const char *destination_folder = "/tmp/unpack";

    // Create destination folder if it doesn't exist
    struct stat st = {0};
    if (stat(destination_folder, &st) == -1) {
        mkdir(destination_folder, 0700);
    }

    extract_tar_file(tar_file, destination_folder);

    return 0;
}

void extract_tar_file(const char *tar_path, const char *extract_to) {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p %s && tar -xzf %s -C %s", 
             extract_to, tar_path, extract_to);
    
    int result = system(command);

    if (result != 0) {
        fprintf(stderr, "Failed to extract tar file\n");
        exit(EXIT_FAILURE);
    }
}