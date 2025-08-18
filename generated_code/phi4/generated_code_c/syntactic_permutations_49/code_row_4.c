#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tar.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int open_tar_file(const char *filename, int mode) {
    return open(filename, O_RDONLY | (mode == 0 ? 0 : O_CREAT), S_IRUSR | S_IWUSR);
}

ssize_t read_tar_header(int fd, struct tar_header *header) {
    return pread(fd, header, sizeof(struct tar_header), lseek(fd, 0, SEEK_CUR));
}

void extract_file(int tar_fd, const char *dest_path, off_t offset, size_t size) {
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd < 0)
        handle_error("Error opening destination file");

    lseek(tar_fd, offset, SEEK_SET);

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(tar_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    if (bytes_read < 0)
        handle_error("Error reading tar file");

    close(dest_fd);
}

void create_directory(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        if (mkdir(path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0)
            handle_error("Error creating directory");
    } else if (!S_ISDIR(st.st_mode))
        handle_error("Path exists and is not a directory");
}

void extract_tar(const char *tar_path, const char *output_dir) {
    int tar_fd = open_tar_file(tar_path, 1);
    if (tar_fd < 0)
        handle_error("Error opening tar file");

    struct stat st;
    fstat(tar_fd, &st);

    size_t num_entries = st.st_size / sizeof(struct tar_header);

    for (size_t i = 0; i < num_entries; ++i) {
        struct tar_header header;
        off_t offset;

        ssize_t bytes_read = read_tar_header(tar_fd, &header);
        if (bytes_read != sizeof(header)) {
            handle_error("Error reading tar header");
        }

        char name_in_header[256];
        strncpy(name_in_header, header.name, 100);
        name_in_header[100] = '\0';

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", output_dir, name_in_header);

        if (strncmp(header.typeflag, "5", 1) == 0) { // Directory
            create_directory(path);
        } else { // File or other types
            offset = strtol(header.offset, NULL, 8);
            size_t size = strtoul(header.size, NULL, 8);

            char *dir_path = dirname(path);
            if (strcmp(dir_path, ".") != 0 && strcmp(dir_path, "") != 0)
                create_directory(dir_path);

            extract_file(tar_fd, path, offset, size);
        }

        lseek(tar_fd, (tar_checksum(header) & 0xff00) >> 8, SEEK_CUR); // Skip padding
    }

    close(tar_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <tarfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *output_dir = "/tmp/unpack";
    create_directory(output_dir);

    extract_tar(argv[1], output_dir);

    return EXIT_SUCCESS;
}