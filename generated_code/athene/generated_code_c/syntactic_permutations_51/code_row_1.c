#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

#define TAR_FILE "/path/to/archive.tar.gz"
#define TMP_DIR "/tmp/unpack"

void extract_tar_gz(const char *filename, const char *outdir) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    FILE *file = fdopen(fd, "rb");
    if (!file) {
        perror("fdopen");
        close(fd);
        exit(EXIT_FAILURE);
    }

    gzFile tar_gz = gzdopen(dup(fileno(file)), "rb");
    if (!tar_gz) {
        perror("gzdopen");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *buffer = NULL;
    size_t buffer_size = 0;

    struct stat st = {0};
    while (1) {
        TarHeader tar_header;
        if (gzread(tar_gz, &tar_header, sizeof(TarHeader)) != sizeof(TarHeader)) break;

        if (!strncmp(tar_header.name, "././@LongLink", 11)) continue;

        char *file_path = malloc(strlen(outdir) + strlen(tar_header.name) + 2);
        sprintf(file_path, "%s/%s", outdir, tar_header.name);

        if (tar_header.typeflag == '5') { // Directory
            mkdir(file_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        } else {
            FILE *out = fopen(file_path, "wb");
            size_t file_size = strtoul(tar_header.size, NULL, 8);

            while (file_size > buffer_size) {
                if (!buffer || buffer_size < 1024) {
                    buffer_size = 1024;
                    buffer = realloc(buffer, buffer_size);
                }
                int n = gzread(tar_gz, buffer, buffer_size);
                fwrite(buffer, 1, n, out);
                file_size -= n;
            }

            free(buffer);
            fclose(out);
        }

        free(file_path);
    }

    fclose(file);
    gzclose(tar_gz);
}

int main() {
    mkdir(TMP_DIR, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    extract_tar_gz(TAR_FILE, TMP_DIR);

    return 0;
}