#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

void* open_tar_file(const char *path, const char *mode) {
    void *result;
    if (strstr(mode, "gz")) {
        result = gzopen(path, mode);
    } else if (strstr(mode, "bz2")) {
        FILE *file = fopen(path, "r");
        BZFILE *bzf = BZ2_bzReadOpen(&result, file, 0, 0, NULL, 0);
        fclose(file);
    } else {
        result = fopen(path, mode);
    }
    return result;
}

void close_tar_file(void *file, const char *mode) {
    if (strstr(mode, "gz")) {
        gzclose((gzFile)file);
    } else if (strstr(mode, "bz2")) {
        BZ2_bzReadClose(&file);
    } else {
        fclose((FILE *)file);
    }
}

void extract_tar_to_tmp(void *tar_file, const char *mode) {
    char buffer[1024];
    struct tar_header *header = (struct tar_header *)buffer;
    int fd, n;

    while ((n = (mode[0] == 'r' && mode[3] == 'b') ? BZ2_bzRead(0, tar_file, buffer, sizeof(buffer)) : 
           (mode[0] == 'r' && mode[3] == 'z') ? gzread((gzFile)tar_file, buffer, sizeof(buffer)) :
           fread(buffer, 1, sizeof(buffer), (FILE *)tar_file))) > 0 {
        if (n < sizeof(struct tar_header) || header->name[0] == '\0') break;

        char path[256];
        snprintf(path, sizeof(path), "/tmp/unpack/%s", header->name);
        mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        if (header->typeflag == '0') {
            fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            while ((n = (mode[0] == 'r' && mode[3] == 'b') ? BZ2_bzRead(0, tar_file, buffer, sizeof(buffer)) : 
                   (mode[0] == 'r' && mode[3] == 'z') ? gzread((gzFile)tar_file, buffer, sizeof(buffer)) :
                   fread(buffer, 1, sizeof(buffer), (FILE *)tar_file)) > 0) {
                write(fd, buffer, n);
            }
            close(fd);
        }

        lseek(tar_file, header->size & 511, SEEK_CUR); // Align to next 512 byte boundary
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    const char *mode = strstr(argv[1], ".tar.gz") ? "rb" : 
                       strstr(argv[1], ".tar.bz2") ? "r" :
                       "r";

    void *tar_file = open_tar_file(argv[1], mode);
    if (!tar_file) return 1;

    extract_tar_to_tmp(tar_file, mode);

    close_tar_file(tar_file, mode);

    return 0;
}