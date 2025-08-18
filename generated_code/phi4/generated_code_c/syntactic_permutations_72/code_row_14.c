#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Function to create a directory if it does not exist
void create_directory(const char *path) {
    struct stat st = {0};
    
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

// Function to handle file upload and save to "uploads" folder
int upload_file(const char *input_filename, const char *output_filename) {
    FILE *input_file = fopen(input_filename, "rb");
    if (input_file == NULL) {
        perror("Error opening input file");
        return -1;
    }

    create_directory("./uploads");

    // Construct the full path for the output file
    char full_output_path[256];
    snprintf(full_output_path, sizeof(full_output_path), "./uploads/%s", output_filename);

    FILE *output_file = fopen(full_output_path, "wb");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return -1;
    }

    // Copy the content from input file to output file
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        fwrite(buffer, 1, bytes_read, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    return 0; // Success
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    int result = upload_file(input_filename, output_filename);
    if (result != 0) {
        fprintf(stderr, "Failed to upload file\n");
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully\n");

    return EXIT_SUCCESS;
}