#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define UPLOAD_DIR "uploads/"
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat st = {0};
    if (stat(UPLOAD_DIR, &st) == -1) {
        mkdir(UPLOAD_DIR, 0755);
    }

    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    char output_path[BUFFER_SIZE];
    snprintf(output_path, sizeof(output_path), "%s%s", UPLOAD_DIR, argv[2]);

    FILE *dest = fopen(output_path, "wb");
    if (!dest) {
        perror("Failed to create output file");
        fclose(src);
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    if (ferror(src)) {
        perror("Error reading from input file");
        fclose(src);
        fclose(dest);
        remove(output_path);
        return EXIT_FAILURE;
    }

    if (fclose(src) != 0 || fclose(dest) != 0) {
        perror("Failed to close files");
        remove(output_path);
        return EXIT_FAILURE;
    }

    printf("File uploaded successfully as %s\n", output_path);

    return EXIT_SUCCESS;
}