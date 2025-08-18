#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

int main() {
    int err = 0;
    const char *archive_path = "archive.zip";
    const char *extract_dir = "/tmp/unpack";

    // Open the archive file
    zip_t *za = zip_open(archive_path, 0, &err);
    if (!za) {
        fprintf(stderr, "Failed to open '%s': %s\n", archive_path, zip_strerror(za));
        return EXIT_FAILURE;
    }

    // Get number of entries in the archive
    zip_int64_t num_entries = zip_get_num_entries(za, 0);

    for (zip_uint64_t i = 0; i < num_entries; i++) {
        const char *name = zip_get_name(za, i, 0);
        if (!name) {
            fprintf(stderr, "Error reading file name at index %llu\n", (unsigned long long)i);
            continue;
        }

        // Open the current file inside the archive
        zip_file_t *file = zip_fopen_index(za, i, 0);
        if (!file) {
            fprintf(stderr, "Failed to open file '%s' in the archive: %s\n", name, zip_strerror(za));
            continue;
        }

        // Create file path for extraction
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", extract_dir, name);

        // Create directories if necessary
        char *dir = strdup(full_path);
        char *last_slash = strrchr(dir, '/');
        if (last_slash) {
            *last_slash = '\0';
            mkdir(dir, 0755);
            *last_slash = '/';
        }

        free(dir);

        // Create and open the output file
        FILE *out = fopen(full_path, "wb");
        if (!out) {
            fprintf(stderr, "Failed to create '%s': %s\n", full_path, strerror(errno));
            zip_fclose(file);
            continue;
        }

        // Read from the archive and write to the file
        const int buf_size = 4096;
        char *buffer = malloc(buf_size);
        if (!buffer) {
            fprintf(stderr, "Memory allocation failed for buffer\n");
            fclose(out);
            zip_fclose(file);
            continue;
        }
        
        while (1) {
            int bytes_read = zip_fread(file, buffer, buf_size);
            if (bytes_read < 0) {
                fprintf(stderr, "Error reading file '%s' in the archive: %s\n", name, zip_file_strerror(file));
                break;
            }
            if (fwrite(buffer, 1, bytes_read, out) != bytes_read) {
                fprintf(stderr, "Failed to write data to '%s'\n", full_path);
                break;
            }
            if (bytes_read < buf_size)
                break;
        }

        // Cleanup
        free(buffer);
        fclose(out);
        zip_fclose(file);
    }

    // Close the archive
    zip_close(za);

    return EXIT_SUCCESS;
}