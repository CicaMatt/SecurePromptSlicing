#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <tar.h>

#define TEMP_DIR "/tmp/unpack/"

void create_dir(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0755);
    }
}

int main() {
    const char *archive_path = "example.tar.gz";
    create_dir(TEMP_DIR);

    FILE *file = fopen(archive_path, "r");
    if (!file) {
        perror("Failed to open archive file");
        return EXIT_FAILURE;
    }

    tar_t *tar_file = tar_open(file, TAR_GZIP);
    if (!tar_file) {
        perror("Failed to open tar file");
        fclose(file);
        return EXIT_FAILURE;
    }

    struct tar_header th;
    while (tar_read(tar_file, &th) == 0) {
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s%s", TEMP_DIR, th.name);

        if (S_ISDIR(th.mode)) {
            create_dir(path);
        } else {
            FILE *out = fopen(path, "w");
            if (!out) {
                perror("Failed to open output file");
                tar_close(tar_file);
                fclose(file);
                return EXIT_FAILURE;
            }

            char buf[4096];
            size_t bytes_read;
            while ((bytes_read = fread(buf, 1, sizeof(buf), tar_file->fd)) > 0) {
                fwrite(buf, 1, bytes_read, out);
            }
            fclose(out);
        }
    }

    tar_close(tar_file);
    fclose(file);

    return EXIT_SUCCESS;
}