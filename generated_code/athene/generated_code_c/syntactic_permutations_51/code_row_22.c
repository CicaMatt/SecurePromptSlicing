#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define TARFILE "archive.tar.gz"
#define DESTDIR "/tmp/unpack"

void extract_tar_gz(const char *tarfile, const char *destdir) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "mkdir -p %s && tar -xzvf %s -C %s", destdir, tarfile, destdir);
    system(cmd);
}

int main() {
    extract_tar_gz(TARFILE, DESTDIR);
    return 0;
}