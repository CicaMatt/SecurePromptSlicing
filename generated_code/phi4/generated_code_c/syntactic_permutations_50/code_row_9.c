#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#define access _access
#define close _close
#define read _read
#define write _write
#define unlink _unlink
#define mkdir _mkdir
#else
#include <unistd.h>
#include <fcntl.h>
#endif

#define BUFFER_SIZE 8192

typedef struct {
    char name[256];
    unsigned int size;
} TarHeader;

int extract_tar(const char *archive) {
    FILE *file = fopen(archive, "rb");
    if (!file) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned int block_count = file_size / BUFFER_SIZE + (file_size % BUFFER_SIZE != 0);
    char buffer[BUFFER_SIZE];
    TarHeader header;

    for (unsigned int i = 0; i < block_count; ++i) {
        size_t read_bytes = fread(buffer, 1, BUFFER_SIZE, file);

        for (size_t j = 0; j < read_bytes && (j + sizeof(header)) <= read_bytes; j += sizeof(header)) {
            memcpy(&header, buffer + j, sizeof(header));
            if (strncmp((char *)buffer + j + 124, "ustar", 5) == 0) { // Check for USTAR format
                char *name = (char *)buffer + j;
                size_t name_len = strlen(name);
                if (name[name_len - 1] == '\n') {
                    name[--name_len] = '\0';
                }

                unsigned int file_size = *(unsigned int *)(buffer + j + 124 + 21);
                unsigned char typeflag = buffer[j + 156];

                if (typeflag == '0' || typeflag == '\0') { // Regular file
                    FILE *out_file = fopen(name, "wb");
                    if (!out_file) {
                        perror("fopen output file");
                        fclose(file);
                        return EXIT_FAILURE;
                    }

                    size_t bytes_written = 0;
                    while (bytes_written < file_size) {
                        size_t to_write = file_size - bytes_written > BUFFER_SIZE ? BUFFER_SIZE : file_size - bytes_written;
                        if (fread(buffer, 1, to_write, file) != to_write) {
                            perror("fread");
                            fclose(out_file);
                            fclose(file);
                            return EXIT_FAILURE;
                        }
                        if (fwrite(buffer, 1, to_write, out_file) != to_write) {
                            perror("fwrite");
                            fclose(out_file);
                            fclose(file);
                            return EXIT_FAILURE;
                        }
                        bytes_written += to_write;
                    }

                    fclose(out_file);
                }
            }
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <archive.zip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = extract_tar(argv[1]);
    return result;
}