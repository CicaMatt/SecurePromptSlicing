#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <tar.h>
#include <zlib.h>
#include <bzlib.h>

void* xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

typedef struct TarFile {
    int fd;
    char* name;
} TarFile;

TarFile* tar_open(const char* path, const char* mode) {
    TarFile* tf = (TarFile*)xmalloc(sizeof(TarFile));
    tf->name = xmalloc(strlen(path) + 1);
    strcpy(tf->name, path);
    tf->fd = open(path, O_RDONLY);
    if (tf->fd == -1) {
        perror("Failed to open tar file");
        free(tf);
        return NULL;
    }
    return tf;
}

void tar_close(TarFile* tf) {
    close(tf->fd);
    free(tf->name);
    free(tf);
}

int unpack_tar(const char* path) {
    TarFile* tf = tar_open(path, "r");
    if (tf == NULL) {
        return -1;
    }

    char buffer[512];
    struct stat st;
    fstat(tf->fd, &st);

    off_t offset = 0;
    while (offset < st.st_size) {
        lseek(tf->fd, offset, SEEK_SET);
        read(tf->fd, buffer, sizeof(buffer));

        struct tar_header* hdr = (struct tar_header*)buffer;
        if (hdr->name[0] == '\0') break;

        char* name = xmalloc(strlen(hdr->name) + 15);
        strcpy(name, "/tmp/unpack/");
        strcat(name, hdr->name);

        if (S_ISDIR(OctalToLong(hdr->mode))) {
            mkdir(name, OctalToLong(hdr->mode));
        } else {
            int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, OctalToLong(hdr->mode));
            write(fd, buffer + 512, OctalToLong(hdr->size));
            close(fd);
        }

        offset += ((OctalToLong(hdr->size) + 511) / 512) * 512;
    }

    tar_close(tf);
    return 0;
}

long OctalToLong(const char* str) {
    long val = 0;
    while (*str) {
        if (*str >= '0' && *str <= '7') {
            val = (val << 3) + (*str - '0');
        }
        str++;
    }
    return val;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    unpack_tar(argv[1]);

    return 0;
}