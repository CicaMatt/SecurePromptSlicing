#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>  // For mkdir on Windows
#define mkdir_p(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#define mkdir_p(path, mode) mkdir(path, mode | (mode & S_IRGRP ? S_IRWXG : 0) | (mode & S_IROTH ? S_IXOTH : 0))
#endif

#include "archive.h"

void extract(const char *filename, const char *output_directory);

int main() {
    const char *zip_filename = "archive.zip";
    const char *output_directory = "/tmp/unpack";

    // Create output directory if it doesn't exist
    mkdir_p(output_directory, 0755);

    extract(zip_filename, output_directory);
    
    return 0;
}

void extract(const char *filename, const char *output_directory) {
    struct archive *a;
    struct archive_entry *entry;
    int r;

    a = archive_read_new();
    archive_read_support_format_all(a);
    archive_read_support_compression_all(a);

    if ((r = archive_read_open_filename(a, filename, 10240))) {
        fprintf(stderr, "Could not open %s: %s\n", filename, archive_error_string(a));
        exit(1);
    }

    while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
        const char *current_path = archive_entry_pathname(entry);
        
        char full_output_path[1024];
        snprintf(full_output_path, sizeof(full_output_path), "%s/%s", output_directory, current_path);

        // Create directories if necessary
        size_t len = strlen(full_output_path);
        for (size_t i = 0; i < len; ++i) {
            if (full_output_path[i] == '/' || full_output_path[i] == '\\') {
                char dir[1024];
                strncpy(dir, full_output_path, i + 1);
                dir[i + 1] = '\0';
                
                mkdir_p(dir, 0755); // Ensure directory exists
            }
        }

        FILE *out = fopen(full_output_path, "wb");
        if (!out) {
            fprintf(stderr, "Could not open %s for writing: %s\n", full_output_path, strerror(errno));
            exit(1);
        }

        char buffer[8192];
        size_t bytes;
        
        while ((bytes = archive_read_data(a, buffer, sizeof(buffer))) > 0) {
            fwrite(buffer, 1, bytes, out);
        }
        
        fclose(out);

        archive_entry_set_pathname(entry, full_output_path); // Update entry with the new path
    }

    archive_read_close(a);
    archive_read_free(a);
}


**Note:** This code uses the `libarchive` library. Ensure you have it installed and properly linked during compilation:


gcc -o extract_program program.c -larchive


For Windows, ensure to include the appropriate headers for directory creation if needed, or adjust paths accordingly.