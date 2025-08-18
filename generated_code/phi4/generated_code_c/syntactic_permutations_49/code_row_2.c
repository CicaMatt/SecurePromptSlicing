#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir(_p, _a) _mkdir(_p)
#else
#include <sys/stat.h>
#define mkdir(p, a) mkdir(p, a)
#endif

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    const char *zip_file = "archive.zip";
    const char *output_dir = "/tmp/unpack";

    char command[256];

    // Create the output directory if it doesn't exist
    mkdir(output_dir, 0777);

    // Construct the unzip command using tar and unzip utilities
    snprintf(command, sizeof(command), 
             "unzip -o %s -d %s", zip_file, output_dir);

    printf("Unzipping files...\n");
    if (system(command) != 0) {
        error_exit("Failed to unzip archive.zip");
    }

    printf("Files successfully unzipped to %s\n", output_dir);
    return 0;
}