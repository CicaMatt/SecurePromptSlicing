#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#include <direct.h>
#define PATH_SEP '\\'
#else
#include <unistd.h>
#define PATH_SEP '/'
#endif

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int mkdir_recursive(const char *path) {
    size_t len = strlen(path);
    if (len == 0 || path[len - 1] == '/') {
        return 0;
    }

    char temp_path[PATH_MAX];
    strcpy(temp_path, path);

    for (size_t i = 0; i < len; ++i) {
        if (temp_path[i] == PATH_SEP) {
            temp_path[i] = '\0';
            if (mkdir(temp_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0 && errno != EEXIST) {
                return -1;
            }
            temp_path[i] = PATH_SEP;
        }
    }

    return mkdir(temp_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
}

void extract_tar(const char *tar_name, const char *extract_to) {
    if (mkdir_recursive(extract_to) != 0) {
        handle_error("Failed to create directories");
    }

    // This is a placeholder for actual tar extraction logic
    // In C, you would typically use libarchive or similar library to handle tar files.
    printf("Extracting %s to %s\n", tar_name, extract_to);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <tarfile> <extract_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *tar_file = argv[1];
    const char *destination = argv[2];

    extract_tar(tar_file, destination);

    return EXIT_SUCCESS;
}
