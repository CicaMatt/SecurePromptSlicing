#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void extract_tar_file(const char *tar_path, const char *extract_to) {
    FILE *file = fopen(tar_path, "rb");
    if (!file) {
        perror("Failed to open tar file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    struct stat st;
    while (1) {
        // Read the header
        if (fread(buffer, 512, 1, file) != 1) {
            break;  // End of file
        }
        
        int name_len = 0;
        for (int i = 0; i < 100 && buffer[i] != '\0'; ++i) {
            name_len++;
        }

        if (name_len == 0) {
            continue;  // Skip empty entries
        }

        char file_name[256];
        strncpy(file_name, buffer, name_len);
        file_name[name_len] = '\0';

        int is_dir = (buffer[156] == '5');
        
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", extract_to, file_name);

        if (is_dir) {
            mkdir(full_path, 0755);
        } else {
            FILE *out_file = fopen(full_path, "wb");
            if (!out_file) {
                perror("Failed to open output file");
                exit(EXIT_FAILURE);
            }
            
            int file_size = buffer[124] << 24 | buffer[125] << 16 | buffer[126] << 8 | buffer[127];
            long offset = (buffer[136] << 24 | buffer[137] << 16 | buffer[138] << 8 | buffer[139]) * 512;
            
            fseek(file, offset, SEEK_SET);
            
            int bytes_read;
            while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
                fwrite(buffer, 1, bytes_read, out_file);
            }

            fclose(out_file);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tar file> <extract to>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *tar_path = argv[1];
    const char *extract_to = argv[2];

    mkdir(extract_to, 0755);

    extract_tar_file(tar_path, extract_to);

    return 0;
}