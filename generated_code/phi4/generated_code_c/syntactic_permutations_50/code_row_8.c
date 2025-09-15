#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

void extractZipToDirectory(const char *zipFilePath, const char *outputDir) {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p %s && unzip -oq %s -d %s", outputDir, zipFilePath, outputDir);
    system(command);
}

int main() {
    const char *archiveZip = "archive.zip";
    const char *unpackDir = "/tmp/unpack";

    extractZipToDirectory(archiveZip, unpackDir);

    return 0;
}
