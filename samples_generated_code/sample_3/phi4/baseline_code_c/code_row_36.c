#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __linux__
#include <tar.h>
#include <fcntl.h>
#endif

void create_directory(const char *path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        mkdir(path, 0700);
    }
}

int main() {
#ifdef __linux__
    const char *archive_path = "archive.zip";
    const char *extract_dir = "/tmp/unpack";

    create_directory(extract_dir);

    int fd = open(archive_path, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open archive");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("Failed to get file status");
        close(fd);
        return EXIT_FAILURE;
    }
    
    size_t buffer_size = st.st_size;
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Memory allocation failed");
        close(fd);
        return EXIT_FAILURE;
    }

    ssize_t bytes_read = read(fd, buffer, buffer_size);
    if (bytes_read < 0) {
        perror("Failed to read file");
        free(buffer);
        close(fd);
        return EXIT_FAILURE;
    }
    
    int tar_fd = open_memstream(&buffer, &buffer_size);
    if (tar_fd == -1) {
        perror("Open memory stream failed");
        free(buffer);
        close(fd);
        return EXIT_FAILURE;
    }

    struct tar_header header;
    size_t offset = 0;

    while (offset < bytes_read) {
        ssize_t read_bytes = pread(fd, &header, sizeof(header), offset);

        if (read_bytes <= 0 || memcmp(header.tar_name, "end", 3) == 0)
            break;

        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/%s", extract_dir, header.tar_name);
        
        int mode = octal_to_int(header.tar_mode);
        if (S_ISREG(mode)) {
            size_t file_size = octal_to_int(header.tar_size);

            FILE *fp = fopen(file_path, "wb");
            if (!fp) {
                perror("Failed to open file");
                continue;
            }

            char *data = malloc(file_size);
            if (!data) {
                fclose(fp);
                continue;
            }
            
            pread(fd, data, file_size, offset + sizeof(header));
            fwrite(data, 1, file_size, fp);

            free(data);
            fclose(fp);
        } else if (S_ISDIR(mode)) {
            create_directory(file_path);
        }

        offset += sizeof(header) + ((header.tar_size + 512 - 1) / 512) * 512;
    }

    close(tar_fd);
    close(fd);
    free(buffer);

    return EXIT_SUCCESS;
#else
    fprintf(stderr, "This code is designed to run on Linux.\n");
    return EXIT_FAILURE;
#endif

    return 0;
}