#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <io.h>   // For _getcwd and _chdir on Windows.
#else
#include <unistd.h>  // For chdir, getcwd
#endif

#define BUFFER_SIZE 1024

void extract_tar(const char *archive_path);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tar_archive_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *archive_path = argv[1];

#ifdef _WIN32
    char cwd[BUFFER_SIZE];
    if (_getcwd(cwd, BUFFER_SIZE) == NULL) {
        fprintf(stderr, "Error getting current directory: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
#else
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        return EXIT_FAILURE;
    }
#endif

    const char *target_dir = "/tmp/unpack";
#ifdef _WIN32
    if (_chdir(target_dir) != 0) {
#else
    if (chdir(target_dir) != 0) {
#endif
        fprintf(stderr, "Error changing directory to %s: %s\n", target_dir, strerror(errno));
        return EXIT_FAILURE;
    }

    extract_tar(archive_path);

#ifdef _WIN32
    if (_chdir(cwd) != 0) {
#else
    if (chdir(cwd) != 0) {
#endif
        fprintf(stderr, "Error returning to previous directory: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void extract_tar(const char *archive_path) {
    FILE *file = fopen(archive_path, "rb");
    if (!file) {
        perror("Failed to open archive file");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Read and process the tar header
    while ((bytes_read = fread(buffer, 1, sizeof(struct tar_header), file)) > 0) {
        struct tar_header header;
        if (bytes_read != sizeof(header)) {
            fprintf(stderr, "Error reading tar header\n");
            break;
        }
        memcpy(&header, buffer, sizeof(header));

        // Check for end of archive
        if (memcmp(header.name, "TAR\0", 4) == 0) break;

        size_t file_size = (size_t)(atol((char*)&header.size)) & 0xFFFFFF;
        char *file_name = strndup(header.name, sizeof(header.name));
        FILE *out_file = fopen(file_name, header.typeflag == '5' ? "wb" : "w");
        if (!out_file) {
            perror("Failed to open output file");
            free(file_name);
            break;
        }

        // Skip the padding
        fseek(file, (file_size + BLOCK_SIZE - 1) & ~(BLOCK_SIZE - 1), SEEK_CUR);

        fclose(out_file);
        free(file_name);
    }

    fclose(file);
}
 

Note: This code provides a basic framework for changing directories and opening files. It does not actually implement the full tar extraction logic or handle all possible edge cases, such as nested archives, error handling, or different compression types (like bz2). For real-world usage, consider using established libraries like libtar or minizip in conjunction with zlib for handling compressed tar archives.