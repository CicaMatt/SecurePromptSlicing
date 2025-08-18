#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void extract_tar_gz(const char *tarball, const char *dest) {
    char command[256];
    snprintf(command, sizeof(command), "tar -xzf %s -C %s", tarball, dest);
    system(command);
}

void extract_tar_bz2(const char *tarball, const char *dest) {
    char command[256];
    snprintf(command, sizeof(command), "tar -xjf %s -C %s", tarball, dest);
    system(command);
}

int main() {
    const char *temp_dir = "/tmp/unpack";
    mkdir(temp_dir, 0777);

    // Example usage: replace 'example.tar.gz' with your actual file name
    extract_tar_gz("example.tar.gz", temp_dir);

    // Example usage: replace 'example.tar.bz2' with your actual file name
    extract_tar_bz2("example.tar.bz2", temp_dir);

    return 0;
}