#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

void unzip(const char *zip_filename, const char *extract_dir) {
    char cmd[1024];

#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), "tar -xf \"%s\" -C \"%s\"", zip_filename, extract_dir);
#else
    snprintf(cmd, sizeof(cmd), "tar -xf %s -C %s", zip_filename, extract_dir);
#endif

    int result = system(cmd);

    if (result != 0) {
        fprintf(stderr, "Error extracting the ZIP file.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <zip_file> <extract_dir>\n", basename(argv[0]));
        return EXIT_FAILURE;
    }

    const char *zip_filename = argv[1];
    const char *extract_dir = argv[2];

#ifdef _WIN32
    if (_mkdir(extract_dir) != 0 && errno != EEXIST) {
#else
    struct stat st = {0};
    if (stat(extract_dir, &st) == -1) {
        mkdir(extract_dir, 0700);
#endif
        fprintf(stderr, "Could not create directory %s\n", extract_dir);
        return EXIT_FAILURE;
    }

    unzip(zip_filename, extract_dir);

    return EXIT_SUCCESS;
}