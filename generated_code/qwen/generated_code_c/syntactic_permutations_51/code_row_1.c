#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <unistd.h>
#include <sys/stat.h>

void extract_tar(const char *filename, const char *extract_to) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    struct tar *t = tar_open(file);
    if (!t) {
        perror("Failed to open tar archive");
        fclose(file);
        return;
    }

    struct stat st = {0};
    if (stat(extract_to, &st) == -1) {
        mkdir(extract_to, 0755);
    }

    while (tar_next(t)) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", extract_to, tar_path(t));

        if (S_ISDIR(tar_mode(t))) {
            mkdir(path, 0755);
        } else {
            FILE *out = fopen(path, "w");
            if (!out) {
                perror("Failed to create file");
                continue;
            }

            const void *data;
            size_t length;
            while ((length = tar_read_data_block(t, &data))) {
                fwrite(data, 1, length, out);
            }

            fclose(out);
        }
    }

    tar_close(t);
    fclose(file);
}

int main() {
    extract_tar("archive.tar.gz", "/tmp/unpack");
    return 0;
}