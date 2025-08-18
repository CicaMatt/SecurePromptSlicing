#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
    #include <direct.h>  // For mkdir on Windows
#else
    #include <unistd.h>  // For mkdir on Unix/Linux
#endif

#define TAR_MAGIC_NUMBER "\x1f\x8b\x08"
#define BUFFER_SIZE 1024 * 256  // Adjust buffer size as needed
#define TMP_DIR "/tmp/unpack"

void create_directory(const char *path) {
    #ifdef _WIN32
        if (_mkdir(path) != 0 && errno != EEXIST) {
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    #else
        if (mkdir(path, 0777) != 0 && errno != EEXIST) {
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    #endif
}

void extract_gzip(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Check the gzip magic number
    bytes_read = fread(buffer, 1, sizeof(TAR_MAGIC_NUMBER), file);
    if (bytes_read != sizeof(TAR_MAGIC_NUMBER) || memcmp(buffer, TAR_MAGIC_NUMBER, sizeof(TAR_MAGIC_NUMBER)) != 0) {
        fprintf(stderr, "Not a valid gzip file\n");
        fclose(file);
        return;
    }

    // Skip the rest of the header
    fseek(file, 8, SEEK_CUR);

    FILE *out_file = NULL;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        char name[100];
        unsigned long int size;
        long int offset;

        // Read metadata block
        if (fread(name, 1, 100, file) != 100 || fread(&size, 1, sizeof(size), file) != sizeof(size)) {
            fprintf(stderr, "Error reading metadata\n");
            fclose(file);
            return;
        }
        fseek(file, 8, SEEK_CUR); // Skip unused fields

        if (name[0] == '\0') break; // End of archive

        offset = ftell(file);

        // Find the next header
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            unsigned long int new_size;
            if (fread(&new_size, 1, sizeof(new_size), file) != sizeof(new_size)) break;
            fseek(file, 8 + size % 2, SEEK_CUR); // Skip unused fields and padding
            size = new_size;

            if (size == 0) {
                fseek(file, offset + 512, SEEK_SET);
                break;
            }
        }

        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", TMP_DIR, name);

        // Create directories as needed
        char *last_slash = strrchr(filepath, '/');
        if (last_slash) {
            *last_slash = '\0';
            create_directory(filepath);
            *last_slash = '/';
        }

        out_file = fopen(filepath, "wb");
        if (!out_file) {
            perror("Failed to open output file");
            continue;
        }

        fseek(file, offset + 512, SEEK_SET);

        size_t bytes_written = 0;
        while (bytes_written < size) {
            size_t chunk_size = BUFFER_SIZE > (size - bytes_written) ? size - bytes_written : BUFFER_SIZE;
            if (fread(buffer, 1, chunk_size, file) != chunk_size) {
                fprintf(stderr, "Error reading compressed data\n");
                break;
            }
            if (fwrite(buffer, 1, chunk_size, out_file) != chunk_size) {
                fprintf(stderr, "Error writing decompressed data\n");
                break;
            }
            bytes_written += chunk_size;
        }

        fclose(out_file);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <tar.gz file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    create_directory(TMP_DIR);

    extract_gzip(argv[1]);

    return EXIT_SUCCESS;
}