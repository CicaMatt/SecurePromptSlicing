#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void extract_tar(const char *filename) {
    FILE *fp;
    char command[256];

    snprintf(command, sizeof(command), "tar -xf %s -C /tmp/unpack", filename);

    if ((fp = popen(command, "r")) == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    pclose(fp);
}

int main() {
    const char *archive_path = "/path/to/your/archive.tar.gz";

    // Ensure the /tmp/unpack directory exists
    if (mkdir("/tmp/unpack", 0755) == -1 && errno != EEXIST) {
        perror("mkdir");
        return EXIT_FAILURE;
    }

    extract_tar(archive_path);

    return EXIT_SUCCESS;
}