#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#define CHUNK_SIZE 16384

// Function prototypes
void extract_gzip(const char *tar_path, const char *out_dir);
void read_file(const char *filename, void (*process_chunk)(const unsigned char *, size_t));

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <gzip_tar_file> <output_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tar_path = argv[1];
    const char *out_dir = argv[2];

    extract_gzip(tar_path, out_dir);

    return EXIT_SUCCESS;
}

void extract_gzip(const char *tar_path, const char *out_dir) {
    gzFile file = gzopen(tar_path, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open gzip file: %s\n", tar_path);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[CHUNK_SIZE];
    int status;

    while ((status = gzread(file, buffer, CHUNK_SIZE)) > 0) {
        read_file(tar_path, process_chunk);
    }

    if (status < 0) {
        fprintf(stderr, "Error reading gzip file: %s\n", gzerror(file, &status));
    }

    gzclose(file);
}

void read_file(const char *filename, void (*process_chunk)(const unsigned char *, size_t)) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[CHUNK_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, file)) > 0) {
        process_chunk(buffer, bytes_read);
    }

    if (ferror(file)) {
        fprintf(stderr, "Error reading file: %s\n", filename);
    }

    fclose(file);
}

void process_chunk(const unsigned char *chunk, size_t size) {
    // Process each chunk of data here
    fwrite(chunk, 1, size, stdout);  // Example: write to standard output
}