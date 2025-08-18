#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h> // For mkdir on Windows
#define PATH_SEP '\\'
#else
#include <sys/stat.h>
#include <unistd.h>
#define PATH_SEP '/'
#endif

void create_dir(const char *path) {
    const size_t len = strlen(path);
    if (len > 0 && path[len - 1] == '\n') path[--len] = '\0';

#ifdef _WIN32
    _mkdir(path);
#else
    mkdir(path, 0777); // Create directory with read/write/execute permissions for everyone
#endif
}

void extract_tar(const char *tar_path) {
    char command[1024];
    snprintf(command, sizeof(command), "tar -xzf %s -C /tmp/unpack", tar_path);

    int status = system(command);
    if (status != 0) {
        fprintf(stderr, "Failed to execute tar extraction\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    const char *tar_file = "/path/to/your/archive.tar.gz"; // Specify the path to your .tar.gz file
    const char *extract_path = "/tmp/unpack";

    create_dir(extract_path);

    extract_tar(tar_file);

    return 0;
}