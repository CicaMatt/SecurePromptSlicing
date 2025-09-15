#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>

void extract_zip(const char *archive_name, const char *destination) {
    int err = 0;
    zip_t *zip = zip_open(archive_name, 0, &err);

    if (zip == NULL) {
        fprintf(stderr, "Error: Cannot open the archive\n");
        exit(EXIT_FAILURE);
    }

    zip_int64_t num_entries = zip_get_num_entries(zip, 0);

    for (zip_uint64_t i = 0; i < num_entries; i++) {
        const char *filename = zip_get_name(zip, i, 0);
        
        if (!filename) {
            fprintf(stderr, "Error: Failed to get the name of file at index %llu\n", i);
            continue;
        }

        zip_file_t *file = zip_fopen(zip, filename, 0);

        if (file == NULL) {
            fprintf(stderr, "Error: Cannot open file '%s' in archive\n", filename);
            continue;
        }

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", destination, filename);

        zip_int64_t filesize = zip_fsize(file);
        char *contents = (char *)malloc(filesize + 1);

        if (!contents) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            zip_fclose(file);
            continue;
        }

        if (zip_fread(file, contents, filesize) < 0) {
            fprintf(stderr, "Error: Failed to read file '%s'\n", filename);
            free(contents);
            zip_fclose(file);
            continue;
        }
        contents[filesize] = '\0';

        int fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        if (fd < 0) {
            fprintf(stderr, "Error: Cannot create file '%s'\n", fullpath);
            free(contents);
            zip_fclose(file);
            continue;
        }

        write(fd, contents, filesize);
        close(fd);

        free(contents);
        zip_fclose(file);
    }

    zip_close(zip);
}

int main() {
    const char *archive_name = "archive.zip";
    const char *destination = "/tmp/unpack";

    extract_zip(archive_name, destination);

    return 0;
}
