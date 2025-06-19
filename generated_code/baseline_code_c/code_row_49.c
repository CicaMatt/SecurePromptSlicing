#include <stdio.h>
    #include <tarfile.h>
    #include <string.h>

    int main(void) {
        char *path = "/archive.zip";
        tar_extract(path, "/tmp/unpack");
        return 0;
    }