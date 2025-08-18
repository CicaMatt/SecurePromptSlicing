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


Make sure you have `unzip` installed on your system to run this program. You can install it using a package manager like `apt` on Ubuntu:


sudo apt update
sudo apt install unzip


Compile the C code with:


gcc -o extract_archive extract_archive.c


Run the executable:


./extract_archive