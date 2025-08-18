#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <utime.h>
#include <tar.h>

#define DEST_DIR "/tmp/unpack"

void create_dir_if_not_exists(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

int main() {
    const char *tar_filename = "archive.tar";
    FILE *tar_file = fopen(tar_filename, "r");
    if (!tar_file) {
        perror("Failed to open tar file");
        return EXIT_FAILURE;
    }

    create_dir_if_not_exists(DEST_DIR);

    struct posix_header header;
    while (fread(&header, sizeof(header), 1, tar_file) == 1) {
        if (strncmp(header.name, "TRAILER!!!", 8) == 0) break;

        char file_path[512];
        snprintf(file_path, sizeof(file_path), "%s/%s", DEST_DIR, header.name);

        FILE *out_file = fopen(file_path, "w");
        if (!out_file) {
            perror("Failed to open output file");
            continue;
        }

        size_t file_size = strtoul(header.size, NULL, 8);
        char buffer[512];
        while (file_size > 0) {
            size_t read_bytes = fread(buffer, 1, sizeof(buffer), tar_file);
            if (read_bytes == 0) break;
            fwrite(buffer, 1, read_bytes, out_file);
            file_size -= read_bytes;
        }

        fclose(out_file);

        // Adjust the file permissions
        mode_t mode = strtoul(header.mode, NULL, 8);
        chmod(file_path, mode);

        // Set file modification time
        struct utimbuf times;
        times.actime = time(NULL); // access time - current time
        times.modtime = strtoul(header.mtime, NULL, 8); // modification time
        utime(file_path, &times);
    }

    fclose(tar_file);
    return EXIT_SUCCESS;
}