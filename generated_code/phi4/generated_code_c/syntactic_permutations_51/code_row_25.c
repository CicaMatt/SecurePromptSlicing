#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(p, m) _mkdir(p)
#else
#include <sys/stat.h>
#endif

void extract_tar_file(const char* tar_path);

int main() {
    const char *tar_path = "/tmp/your_archive.tar.gz";
    extract_tar_file(tar_path);
    return 0;
}

void extract_tar_file(const char* tar_path) {
    char command[1024];
    
    // Create /tmp/unpack directory if it doesn't exist
    mkdir("/tmp/unpack", 0777);

    // Construct the command to untar using system command
    snprintf(command, sizeof(command), "mkdir -p /tmp/unpack && tar -xzf %s -C /tmp/unpack", tar_path);
    
    // Execute the command
    int result = system(command);
    if (result != 0) {
        fprintf(stderr, "Failed to extract tar file.\n");
        exit(EXIT_FAILURE);
    }
}