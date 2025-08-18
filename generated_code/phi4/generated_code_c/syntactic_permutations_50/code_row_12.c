#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>  // For mkdir on Windows
#define MKDIR(a) _mkdir((a))
#else
#include <sys/stat.h>  // For mkdir on Unix-like systems
#define MKDIR(a) mkdir((a), 0777)
#endif

void extract(const char *filename, const char *output_dir);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <archive.zip> <output directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *zip_filename = argv[1];
    const char *output_directory = argv[2];

    extract(zip_filename, output_directory);

    return EXIT_SUCCESS;
}

void extract(const char *filename, const char *output_dir) {
    FILE *zip_file = fopen(filename, "rb");
    if (!zip_file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the central directory record signature (0x06054b50)
    unsigned long long signature;
    fread(&signature, 4, 1, zip_file);
    
    fseek(zip_file, -22, SEEK_END);  // Move to start of last central directory file header

    int i = 0;
    while (1) {
        unsigned long long local_header_signature;
        fread(&local_header_signature, 4, 1, zip_file);

        if (local_header_signature == 0x04034b50 || local_header_signature == 0x02014b50) { // Local file header signatures
            unsigned short version_needed_to_extract;
            unsigned short general_purpose_bit_flag;
            unsigned short compression_method;
            unsigned short last_mod_time;
            unsigned short last_mod_date;
            unsigned int crc32;
            unsigned int compressed_size;
            unsigned int uncompressed_size;

            fread(&version_needed_to_extract, 2, 1, zip_file);
            fread(&general_purpose_bit_flag, 2, 1, zip_file);
            fread(&compression_method, 2, 1, zip_file);

            fread(&last_mod_time, 2, 1, zip_file);
            fread(&last_mod_date, 2, 1, zip_file);

            fread(&crc32, 4, 1, zip_file);
            fread(&compressed_size, 4, 1, zip_file);
            fread(&uncompressed_size, 4, 1, zip_file);

            unsigned short file_name_length;
            unsigned short extra_field_length;

            fread(&file_name_length, 2, 1, zip_file);
            fread(&extra_field_length, 2, 1, zip_file);

            char *file_name = malloc(file_name_length + 1);
            fread(file_name, file_name_length, 1, zip_file);
            file_name[file_name_length] = '\0';

            // Skip extra field
            fseek(zip_file, extra_field_length, SEEK_CUR);

            unsigned short file_comment_length;
            if (version_needed_to_extract >= 45) {  // Version with file comment support
                fread(&file_comment_length, 2, 1, zip_file);
            }

            // Seek to the start of compressed data
            fseek(zip_file, -(compressed_size + file_name_length + extra_field_length + file_comment_length + 30), SEEK_CUR);

            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", output_dir, file_name);

            // Create directory if needed
            char *dir = strtok(full_path, "/");
            char dir_path[1024] = "";
            while (dir != NULL) {
                strcat(dir_path, dir);
                strcat(dir_path, "/");

                DIR* d = opendir(dir_path);
                if (!d) {
                    MKDIR(dir_path);
                }
                closedir(d);

                dir = strtok(NULL, "/");
            }

            FILE *out_file = fopen(full_path, "wb");
            if (out_file == NULL) {
                perror("Error opening output file");
                free(file_name);
                fclose(zip_file);
                exit(EXIT_FAILURE);
            }

            char buffer[4096];
            unsigned int bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), zip_file)) > 0) {
                fwrite(buffer, 1, bytes_read, out_file);
            }

            fclose(out_file);
            free(file_name);

            i++;
        } else if (local_header_signature == 0x06054b50) { // End of central directory signature
            break;
        } else {
            fseek(zip_file, -4, SEEK_CUR); // Not a valid header, rewind and try again
        }
    }

    fclose(zip_file);
}